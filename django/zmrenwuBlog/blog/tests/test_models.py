from datetime import timedelta

from django.utils import timezone

from django.apps import apps
from django.contrib.auth.models import User
from django.test import TestCase
from django.urls import reverse

from blog.models import Category, Post, Tag


class BlogDataTestCase(TestCase):
    def setUp(self):
        # apps.get_app_config('haystack').signal_processor.teardown()
        # User
        self.user = User.objects.create_superuser(
            username='admin',
            email='admin@hellogithub.com',
            password='admin'
        )
        # 分类
        self.cate1 = Category.objects.create(name='测试分类一')
        self.cate2 = Category.objects.create(name='测试分类二')

        # 标签
        self.tag1 = Tag.objects.create(name='测试标签一')
        self.tag2 = Tag.objects.create(name='测试标签二')
        # 文章
        self.post1 = Post.objects.create(
            title='测试标题一',
            body='测试内容一',
            category=self.cate1,
            author=self.user,
        )
        self.post1.tags.add(self.tag1)
        self.post1.save()

        self.post2 = Post.objects.create(
            title='测试标题二',
            body='测试内容二',
            category=self.cate2,
            author=self.user,
            created_time=timezone.now() - timedelta(days=100)
        )


class PostDetailViewTestCase(BlogDataTestCase):
    def setUp(self):
        super().setUp()
        self.md_post = Post.objects.create(
            title='Markdown 测试标题',
            body='# 标题',
            category=self.cate1,
            author=self.user,
        )
        self.url = reverse('blog:detail', kwargs={'pk': self.md_post.pk})

    def test_good_view(self):
        response = self.client.get(self.url)
        self.assertEqual(response.status_code, 200)
        self.assertTemplateUsed('blog/detail.html')
        self.assertContains(response, self.md_post.title)
        self.assertIn('post', response.context)

    def test_visit_a_nonexistent_post(self):
        url = reverse('blog:detail', kwargs={'pk': 100})
        response = self.client.get(url)
        self.assertEqual(response.status_code, 404)

    def test_increase_views(self):
        self.client.get(self.url)
        self.md_post.refresh_from_db()
        self.assertEqual(self.md_post.views, 1)
        self.client.get(self.url)
        self.md_post.refresh_from_db()
        self.assertEqual(self.md_post.views, 2)

    def test_markdownify_post_body_and_set_toc(self):
        response = self.client.get(self.url)
        self.assertContains(response, '文章目录')
        self.assertContains(response, self.md_post.title)

        post_template_var = response.context['post']
        # self.assertHTMLEqual(post_template_var.body_html, "<hh1 id='标题'>标题</h1>")
        self.assertHTMLEqual(post_template_var.toc, '<li><a href="#标题">标题</li>')


class CategoryViewTestCase(BlogDataTestCase):
    def setUp(self):
        super().setUp()
        self.url = reverse('blog:category', kwargs={'pk': self.cate1.pk})
        self.url2 = reverse('blog:category', kwargs={'pk': self.cate2.pk})

    def test_visit_a_nonexistent_category(self):
        url = reverse('blog:category', kwargs={'pk': 100})
        response = self.client.get(url)
        self.assertEqual(response.status_code, 404)

    def test_without_any_post(self):
        Post.objects.all().delete()
        response = self.client.get(self.url2)
        self.assertEqual(response.status_code, 200)
        self.assertTemplateUsed('blog/index.html')
        self.assertContains(response, '暂时还没有文章发布！')

    def test_with_posts(self):
        response = self.client.get(self.url)
        self.assertEqual(response.status_code, 200)
        self.assertTemplateUsed('blog/index.html')
        self.assertContains(response, self.post1.title)
        self.assertIn('post_list', response.context)
        self.assertIn('is_paginated', response.context)
        self.assertIn('page_obj', response.context)
        self.assertEqual(response.context['post_list'].count(), 1)
        expected_qs = self.cate1.post_set.all().order_by('-created_time')
        self.assertQuerysetEqual(response.context['post_list'], [repr(p) for p in expected_qs])


class PostModelTestCase(TestCase):
    def setUp(self):
        # apps.get_app_config('haystack').signal_processor.teardown()
        user = User.objects.create_superuser(
            username='admin',
            email='admin@hellogithub.com',
            password='admin'
        )
        cate = Category.objects.create(name='测试')
        self.post = Post.objects.create(
            title='测试标题',
            body='测试内容',
            category=cate,
            author=user,
        )

    def test_str_representation(self):
        self.assertEqual(self.post.__str__(), self.post.title)

    def test_auto_populate_modified_time(self):
        self.assertIsNotNone(self.post.modified_time)
        old_post_modified_time = self.post.modified_time
        self.post.body = '新的测试内容'
        self.post.save()
        self.post.refresh_from_db()
        self.assertTrue(self.post.modified_time > old_post_modified_time)

    def test_auto_populate_excerpt(self):
        self.assertIsNotNone(self.post.excerpt)
        self.assertTrue(0 < len(self.post.excerpt) <= 54)

    def test_get_absolute_url(self):
        expected_url = reverse('blog:detail', kwargs={'pk': self.post.pk})
        self.assertEqual(self.post.get_absolute_url(), expected_url)

    def test_increase_views(self):
        self.post.increase_views()
        self.post.refresh_from_db()
        self.assertEqual(self.post.views, 1)

        self.post.increase_views()
        self.post.refresh_from_db()
        self.assertEqual(self.post.views, 2)


class AdminTestCase(BlogDataTestCase):
    def setUp(self):
        super().setUp()
        self.url = reverse('admin:blog_post_add')

    def test_set_author_after_publishing_the_post(self):
        data = {
            'title': '测试标题',
            'body': '测试内容',
            'category': self.cate1.pk
        }
        self.client.login(username=self.user, password='admin')
        response = self.client.post(self.url, data=data)
        self.assertEqual(response.status_code, 302)

        post = Post.objects.all().latest('created_time')
        self.assertEqual(post.author, self.user)
        self.assertEqual(post.title, data.get('title'))
        self.assertEqual(post.category, self.cate1)
