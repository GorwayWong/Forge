"""zmrenwuBlog URL Configuration

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/3.2/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  path('', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  path('', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.urls import include, path
    2. Add a URL to urlpatterns:  path('blog/', include('blog.urls'))
"""
from django.contrib import admin
from django.urls import path, include
from rest_framework import routers

import comments.views
from blog.views import PostViewSet
from rest_framework.routers import DefaultRouter

router = routers.DefaultRouter()
router.register(r'posts', PostViewSet, basename='post')
router.register(r"comments", comments.views.CommentViewSet, basename="comment")
urlpatterns = [
    path('admin/', admin.site.urls),
    path('', include('blog.urls')),
    path('', include('comments.urls')),
    path("api/v1/", include((router.urls, "api"), namespace="v1")),
    path("api/auth/", include("rest_framework.urls", namespace="rest_framework")),
]
