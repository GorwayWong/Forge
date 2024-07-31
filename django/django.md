# 来自https://www.zhihu.com/people/zhu-jia-sheng-71/posts

## 创建Django项目

### 创建Django工程

cd进要存代码的文件夹，我们使用如下命令，创建一个 Django 项目，名为`django_self_practise`。

```shell
django-admin startproject django_self_practice .
```

请特别留意命令中的`.`符号，它表示当前目录。这么操作主要是为了让项目管理工具 manage.py 生成在当前目录下（其默认是创建在项目文件夹中）。

### 创建Django应用

```shell
django-admin startapp practice
```

### 启动WEB服务

```shell
python manage.py runserver
```

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