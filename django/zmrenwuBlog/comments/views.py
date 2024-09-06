from django.shortcuts import render
from blog.models import Post
from django.shortcuts import get_object_or_404, redirect, render
from django.views.decorators.http import require_POST
from .forms import CommentForm
from django.contrib import messages
from rest_framework import mixins, viewsets
from .models import Comment
from .serializers import CommentSerializer


# Create your views here.

class CommentViewSet(mixins.CreateModelMixin, viewsets.GenericViewSet):
    serializer_class = CommentSerializer

    def get_queryset(self):
        return Comment.objects.all()


@require_POST
def comment(request, post_pk):
    post = get_object_or_404(Post, pk=post_pk)
    form = CommentForm(request.POST)
    if form.is_valid():
        comment_in = form.save(commit=False)
        comment_in.post = post
        comment_in.save()
        messages.add_message(request, messages.SUCCESS, '评论发表成功!', extra_tags='success')
        return redirect(post)
    context = {
        'post': post,
        'form': form,
    }
    messages.add_message(request, messages.ERROR, '评论发表失败！请修改后重新评论。', extra_tags='danger')
    return render(request, 'comments/preview.html', context=context)
