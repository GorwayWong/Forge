<<<<<<< HEAD
# Django新建网络项目实操
=======
# 来自https://www.zhihu.com/people/zhu-jia-sheng-71/posts
>>>>>>> cdecf082af18308cdc5ed45bc532b3a45595f2bb

## 创建Django项目

### 创建Django工程

cd进要存代码的文件夹，我们使用如下命令，创建一个 Django 项目，名为`django_self_practise`。

```shell
django-admin startproject django_self_practice .
```

请特别留意命令中的`.`符号，它表示当前目录。这么操作主要是为了让项目管理工具 manage.py 生成在当前目录下（其默认是创建在项目文件夹中）。

### 创建Django应用

<<<<<<< HEAD
```bash
django-admin startproject my_blog
cd my_blog
=======
```shell
django-admin startapp practice
>>>>>>> cdecf082af18308cdc5ed45bc532b3a45595f2bb
```

### 启动WEB服务

```shell
python manage.py runserver
```

<<<<<<< HEAD
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
=======
## Django配置

### settings.py

一个 Django 项目，其配置文件通常会有两处地方：Django **框架全局配置**、**项目自身配置**。

项目启动起来，它会先加载全局配置，再加载项目自身配置。如果两者不一致，以项目自身配置为准（后加载）。

在 Django 项目`django_self_practise`中，有一个名为`settings.py` 的 Python 文件。 这便是项目自身的配置文件。

- **DEBUG**

```text
# SECURITY WARNING: don't run with debug turned on in production!
DEBUG = True
```

在`DEBUG = True`的情况下，如果我们输入正确的 URL 路径，浏览器页面正常显示； 如果我们输入错误的 URL 路径，浏览器页面会提示异常信息。

在`DEBUG = False`的情况下，只有正确的 URL 路径，浏览器页面正常显示。Django 内部的异常信息，不再通过页面显示。**但是，关键是但是，一旦我们将 DEBUG 设置为 False 时，原先的 WEB 已启动服务会停止，再启动则提示如下信息。**

**`CommandError: You must set settings.ALLOWED_HOSTS if DEBUG is False.`**

- `ALLOWED_HOSTS`

我们暂时把 `DEBUG`选项设置为`True`。

在 `DEBUG` 附近，有另一个`ALLOWED_HOSTS`选项，最开始它是个空列表。填入`127.0.0.1`。（这个列表的元组可以自定义，用于允许哪些地址登录网页。限于篇幅，这里我只演示`127.0.0.1`的。）

### 框架全局配置global_settings.py

配置加载工作流：**项目启动后，先加载框架全局配置`global_settings.py`，再加载项目自身配置`settings.py`。如果两者不一致，以项目自身配置为准（后加载）。**

### APP注册

重回项目自身配置 settings.py 文件，找到`INSTALLED_APPS`选项，也是一个列表。默认情况下，Django 已经加载了一些默认应用。

需要把自己创建的APP放到列表里

## 路由

项目（Project）与应用（APP）关联，我们先记住一个口诀：**项目（根路由）+应用（二级路由）**

**【根路由，自带】项目 - `django_self_practise`**

**【二级路由，手工创建】APP - `practise`**

函数`include` 的作用是将其他模块或应用（如我们创建的`practise`应用）中的路由包含进来，使得路由结构更加清晰和可扩展。

列表`urlpatterns`用来存放路由信息。 当用户访问某个 URL 时，Django 会根据`urlpatterns`列表中的规则进行匹配，找到对应的功能来处理请求，并返回相应的响应。

## 视图

`Django`应用中用于处理视图逻辑的重要部分，其作用有：

- **定义视图函数**：这些函数接收`HttpRequest`对象作为参数，并返回`HttpResponse`对象或执行重定向等操作，用于处理用户的请求并生成相应的响应内容。
- **业务逻辑处理**：在这里实现应用的具体业务逻辑，比如数据获取、处理和展示等。
- **模板文件交互**：通过视图函数将数据传递给模板，以便渲染生成最终的页面呈现给用户。

**Django 框架用“路由”、“路由分发”等术语来表述这个过程，我们通俗的理解，其实质就是 URL 拼接，从而定位到（找到）相应的功能（函数），完成特定的动作。**

## HttpResponse

如果是 GET 方法，最后是否以`/`斜杠结尾，在Django 内部处理后，其效果是一致的。

- `requests.get("http://127.0.0.1:8000/practise")`
- `requests.get("http://127.0.0.1:8000/practise/")`

在 Django 框架默认设置情况下，如果使用 POST 方法，我们必须在 URL 最后加上一个斜杠（slash），否则会报错。我们养成习惯，一旦使用 POST 方法，相应的 URL 必须以`/`结尾。

Django 框架默认开启 CSRF 校验功能，因此，我们使用 requests 库“粗制滥造”的 POST 请求遇到了拦路虎。

# 来自大江狗blog

## MVC和django的MVT

- **Django Model(模型)**: 这个与经典MVC模式下的模型Model差不多。
- **Django View(视图)**: 这个与MVC下的控制器Controller更像。视图不仅负责根据用户请求从数据库读取数据、指定向用户展示数据的方式(网页或json数据), 还可以指定渲染模板并处理用户提交的数据。
- **Django Template(模板)**: 这个与经典MVC模式下的视图View一致。模板用来呈现Django view传来的数据，也决定了用户界面的外观。Template里面也包含了表单，可以用来搜集用户的输入内容。

`reverse()` 函数帮助你将一个易读的 URL 名称转换为一个具体的 URL 模式。

在使用`path`和`re_path`方法设计urls需注意：

- url中的参数名要用尖括号，而不是圆括号；
- 匹配模式的最开头不需要添加斜杠`/`，但建议以斜杠结尾;
- 使用`re_path`时不一定总是以`$`结尾，有时不能加。比如下例中把`blog.urls`通过`re_path`加入到项目urls中时就不能以`$`结尾，因为这里的`blog/`并不是完整的url，只是一个开头而已。

`url`是个模板标签，其作用是对命名的url进行方向解析，动态生成链接。

注意：命名的url里有几个参数，使用`url`模板标签反向生成动态链接时，就需要向它传递几个参数。比如我们的命名url`article_detail`里有整数型`id`这个参数，我们在模板中还需要传递`article.id`。

可惜的是命名的URL一般只在模板里使用，不能直接在视图里使用。如果我们有了命名的URL，我们如何把它转化成常规的URL在视图里使用呢？

Django提供的`reverse()`方法很容易实现这点。它在视图中可以对命名urls进行反向解析，生成动态链接。

**注意**：在URL配置文件中使用类视图时，需要使用`as_view()`将其伪装成方法.
>>>>>>> cdecf082af18308cdc5ed45bc532b3a45595f2bb
