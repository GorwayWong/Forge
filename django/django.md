# Django新建网络项目实操

在想要创建项目的文件夹位置打开终端:

```bash
mkdir django_test
cd django_test
```

使用django-admin创建一个名为mytestsite的新框架站点:

可以cd到该文件夹,并在其中找到管理项目的主要脚本,名为manage.py

```bash
django-admin startproject my_blog
cd my_blog
```

可以在该文件夹中使用manage.py和runserver命令运行服务器:

```bash
python3 manage.py runserver
```

## 新建Django应用（App,即功能模块）

`python manage.py startapp article`

## 注册App

在项目名的同名目录下,修改settings.py

## 配置App的访问路径

同样在项目名的同名目录下的urls.py文件

```python
my_blog/urls.py

from django.contrib import admin
# 记得引入include
from django.urls import path, include

# 存放映射关系的列表
urlpatterns = [
    path('admin/', admin.site.urls),

    # 新增代码，配置app的url
    path('article/', include('article.urls', namespace='article')),
]
```

path为Django的路由语法：

- 参数`article/`分配了app的访问路径；
- `include`将路径分发给下一步处理；
- `namespace`可以保证反查到唯一的url，即使不同的app使用了相同的url（后面会用到）。

现在我们已经通过`path`将根路径为`article`的访问都分发给article这个app去处理。但是app通常有多个页面地址，因此还需要app自己也有一个路由分发，也就是`article.urls`了。

在app生成时并没有这个文件，因此需要自己在`article`文件夹中创建`urls.py`

```python
article/urls.py

# 引入path
from django.urls import path

# 正在部署的应用的名称
app_name = 'article'

urlpatterns = [
    # 目前还没有urls
]
```

Django2.0之后，app的`urls.py`必须配置`app_name`，否则会报错。

## 编写Model

编写跟App、业务相关的数据的Model模型

- 每个模型都被表示为 `django.db.models.Model` 类的子类，从它继承了操作数据库需要的所有方法。
- 每个字段都是 `Field` 类的实例 。比如字符字段被表示为 `CharField` ，日期时间字段被表示为 `DateTimeField`。这将告诉Django要处理的数据类型。
- 定义某些 `Field` 类实例需要参数。例如 `CharField` 需要一个 `max_length`参数。这个参数的用处不止于用来定义数据库结构，也用于验证数据。
- 使用 `ForeignKey`定义一个关系。这将告诉 Django，每个（或多个） `ArticlePost` 对象都关联到一个 `User` 对象。

Django具有一个简单的账号系统（User），满足一般网站的用户相关的基本功能。

内部类 class Meta 用于给 model 定义元数据.

函数 \__str__ 定义当调用对象的 str() 方法时的返回值内容

元数据是**“任何不是字段的东西”**，例如排序选项`ordering`、数据库表名`db_table`、单数和复数名称`verbose_name`和 `verbose_name_plural`

## 数据迁移(Migrations)

**每当对数据库进行了更改（添加、修改、删除等）操作，都需要进行数据迁移。**

`python manage.py makemigrations`对模型的更改创建新的迁移表

然后输入`python manage.py migrate`，**应用迁移到数据库中**

`migrate` 命令选中所有还没有执行过的迁移并应用在数据库上，也就是将模型的更改同步到数据库结构上。

**再重复一次**：每当你修改了`models.py`文件，都需要用`makemigrations`和`migrate`这两条指令迁移数据。

## View视图

**网页都是从视图派生而来。**每一个视图表现为一个简单的Python函数，它必须要做的只有两件事：返回一个包含被请求页面内容的 `HttpResponse`对象，或者抛出一个异常，比如 `Http404` 。

```python
from django.http import HttpResponse
def article_list(request):
  return HttpResponse("Hello World!")
```

视图函数中的`request`与网页发来的请求有关，里面包含**get**或**post**的内容、用户浏览器、系统等信息。Django调用`article_list`函数时会返回一个含字符串的 `HttpResponse`对象。

有了视图函数，还需要配置**URLconfs**，将用户请求的URL链接关联起来。换句话说，URLconfs的作用是将URL映射到视图中。

### 改写视图函数

```python
article/views.py

from django.shortcuts import render

# 导入数据模型ArticlePost
from .models import ArticlePost

def article_list(request):
    # 取出所有博客文章
    articles = ArticlePost.objects.all()
    # 需要传递给模板（templates）的对象
    context = { 'articles': articles }
    # render函数：载入模板，并返回context对象
    return render(request, 'article/list.html', context)
```

分析如下：

- `from .models import ArticlePost`从`models.py`中导入`ArticlePost`数据类

- `ArticlePost.objects.all()`是数据类的方法，可以获得所有的对象（即博客文章），并传递给`articles`变量

- `context`定义了需要传递给**模板**的上下文，这里即`articles`

  > 模板的概念马上就要讲。

- 最后返回了`render`函数。它的作用是结合模板和上下文，并返回渲染后的HttpResponse对象。通俗的讲就是把context的内容，加载进模板，并通过浏览器呈现。

`render`的变量分解如下：

- request是固定的`request`对象，照着写就可以
- `article/list.html`定义了模板文件的位置、名称
- `context`定义了需要传入模板文件的上下文

## Django管理后台

`python manage.py createsuperuser`创建管理员账号

接下来我们需要“告诉”Django，后台中需要添加`ArticlePost`这个数据表供管理。

## 编写模板(template)

在项目同名目录下的`settings.py`中,设置模板位置

```python
my_blog/settings.py

TEMPLATES = [
    {
        ...
        # 定义模板位置
        'DIRS': [os.path.join(BASE_DIR, 'templates')],
        ...
    },
]
```

这就是说模板文件在项目根目录的`templates`文件夹中.

## 调试

- 在视图函数中写的`print()`会打印到命令行中。
- 在JavaScript代码中用`console.log()`指令可以将感兴趣的内容打印到浏览器Console中查看。
- command+option+i打开控制台
