from django.urls import path
from . import views
from .views import index

app_name = 'blog'
urlpatterns = [
    path('', views.IndexView.as_view(), name='index'),
    path('posts/<int:pk>/', views.detail, name='detail'),
    path('archives/<int:year>/<int:month>', views.archive, name='archive'),
    path('categories/<int:pk>/', views.CategoryView.as_view(), name='category'),
    path('tags/<int:pk>/', views.tag, name='tag'),
    # path('api/index/', views.index),
    # path('api/index/', views.IndexPostListAPIView.as_view()),
    path("api/index/", index),
]
