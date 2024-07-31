import re
from django.shortcuts import render, get_object_or_404
from django.http import HttpResponse

from comments.serializers import CommentSerializer
from .models import Post, Category, Tag
import markdown
from django.utils.text import slugify
from markdown.extensions.toc import TocExtension
from django.views.generic import ListView, DetailView
from rest_framework.decorators import api_view, action
from rest_framework.response import Response
from .serializers import PostListSerializer
from rest_framework.generics import ListAPIView
from rest_framework.pagination import PageNumberPagination, LimitOffsetPagination
from rest_framework.permissions import AllowAny
from rest_framework import viewsets, mixins, status
from rest_framework.serializers import DateField
from django_filters.rest_framework import DjangoFilterBackend
from .filters import PostFilter
from rest_framework_extensions.cache.decorators import cache_response
from rest_framework_extensions.key_constructor.bits import (ListSqlQueryKeyBit, PaginationKeyBit,
                                                            RetrieveSqlQueryKeyBit,
                                                            )
from rest_framework_extensions.key_constructor.constructors import DefaultKeyConstructor
from .utils import UpdatedAtKeyBit
from rest_framework.throttling import AnonRateThrottle


# Create your views here.

class PostSearchAnonRateThrottle(AnonRateThrottle):
    THROTTLE_RATES = {"anon": "5/min"}


class PostUpdatedAtKeyBit(UpdatedAtKeyBit):
    key = "post_updated_at"


class CommentUpdatedAtKeyBit(UpdatedAtKeyBit):
    key = "comment_updated_at"


class PostListKeyConstructor(DefaultKeyConstructor):
    list_sql = ListSqlQueryKeyBit()
    pagination = PaginationKeyBit()
    updated_at = PostUpdatedAtKeyBit()


class PostObjectKeyConstructor(DefaultKeyConstructor):
    retrieve_sql = RetrieveSqlQueryKeyBit()
    updated_at = PostUpdatedAtKeyBit()


class CommentListKeyConstructor(DefaultKeyConstructor):
    list_sql = ListSqlQueryKeyBit()
    pagination = PaginationKeyBit()
    updated_at = CommentUpdatedAtKeyBit()


class PostViewSet(mixins.ListModelMixin, mixins.RetrieveModelMixin, viewsets.GenericViewSet):
    serializer_class = PostListSerializer
    serializer_class_table = {
        'list'
    }
    queryset = Post.objects.all()
    pagination_class = PageNumberPagination
    permission_classes = [AllowAny]
    filter_backends = [DjangoFilterBackend]
    filterset_class = PostFilter

    @action(
        methods=["GET"], detail=False, url_path="archiev/dates", url_name="archive-date"
    )
    def list_archive_dates(self, request, *args, **kwargs):
        dates = Post.objects.dates("created_time", "month", order="DESC")
        date_field = DateField()
        data = [date_field.to_representation(date) for date in dates]
        return Response(data=data, status=status.HTTP_200_OK)

    @action(
        methods=["GET"],
        detail=True,
        url_path="comments",
        url_name="comment",
        pagination_class=LimitOffsetPagination,
        serializer_class=CommentSerializer,
    )
    @cache_response(timeout=5 * 60, key_func=CommentListKeyConstructor())
    @action(
        methods=["GET"],
        detail=True,
        url_path="comments",
        url_name="comment",
        pagination_class=LimitOffsetPagination,
        serializer_class=CommentSerializer,
    )
    def list_comments(self, request, *args, **kwargs):
        post = self.get_object()
        queryset = post.comment_set.all().order_by("-created_time")
        page = self.paginate_queryset(queryset)
        serializer = self.get_serializer(page, many=True)
        return self.get_paginated_response(serializer.data)

    @cache_response(timeout=6 * 60, key_func=PostListKeyConstructor())
    def list(self, request, *args, **kwargs):
        return super().list(request, *args, **kwargs)

    @cache_response(timeout=5 * 60, key_func=PostObjectKeyConstructor())
    def retrieve(self, request, *args, **kwargs):
        return super().retrieve(request, *args, **kwargs)


index = PostViewSet.as_view({'get': 'list'})


class IndexPostListAPIView(ListAPIView):  # 必须继承ListAPIView而不是ListView
    serializer_class = PostListSerializer
    queryset = Post.objects.all()
    pagination_class = PageNumberPagination
    permission_classes = [AllowAny]


class IndexView(ListView):
    model = Post
    template_name = 'blog/index.html'
    context_object_name = 'post_list'
    paginate_by = 10


class CategoryView(ListView):
    model = Post
    template_name = 'blog/index.html'
    context_object_name = 'post_list'

    def get_queryset(self):
        cate = get_object_or_404(Category, pk=self.kwargs.get('pk'))
        return super(CategoryView, self).get_queryset().filter(category=cate)


class PostDetailView(DetailView):
    model = Post
    template_name = 'blog/detail.html'
    context_object_name = 'post'

    def get(self, request, *args, **kwargs):
        response = super(PostDetailView, self).get(request, *args, **kwargs)
        self.object.increase_views()
        return response

    def get_object(self, queryset=None):
        post = super().get_object(queryset=None)
        md = markdown.Markdown(extensions=[
            'markdown.extensions.extra',
            'markdown.extensions.codehilite',
            TocExtension(slugify=slugify),
        ])
        post.body = md.convert(post.body)
        m = re.search(r'<div class="toc">\s*<ul>(.*)</ul>\s*</div>', md.toc, re.S)
        post.toc = m.group(1) if m is not None else ''
        return post


@api_view(http_method_names=["GET"])
def index(request):
    post_list = Post.objects.all().order_by('-created_time')
    serializer = PostListSerializer(post_list, many=True)
    return Response(serializer.data, status=status.HTTP_200_OK)


def detail(request, pk):
    post = get_object_or_404(Post, pk=pk)
    post.increase_views()
    md = markdown.Markdown(extensions=[
        'markdown.extensions.extra',
        'markdown.extensions.codehilite',
        TocExtension(slugify=slugify),
    ])
    post.body = md.convert(post.body)
    m = re.search(r'<div class="toc">\s*<ul>(.*)</ul>\s*</div>', md.toc, re.S)
    post.toc = m.group(1) if m is not None else ''
    return render(request, 'blog/detail.html', context={'post': post})


def archive(request, year, month):
    post_list = Post.objects.filter(created_time__year=year,
                                    created_time__month=month).order_by('-created_time')
    return render(request, 'blog/index.html', context={'post_list': post_list})


def category(request, pk):
    cate = get_object_or_404(Category, pk=pk)
    post_list = Post.objects.filter(category=cate).order_by('-created_time')
    return render(request, 'blog/index.html', context={'post_list': post_list})


def tag(request, pk):
    t = get_object_or_404(Tag, pk=pk)
    post_list = Post.objects.filter(tags=t).order_by('-created_time')
    return render(request, 'blog/index.html', context={'post_list': post_list})
