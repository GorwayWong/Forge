# HTML基础

HTML主要用于网页主体结构的搭建

CSS主要用于页面元素美化

JavaScript主要用于页面元素的动态处理

## HTML基础结构

```html
<!-- 
1.html文件的根标签<html></html>所有的其他标签都要在这个标签中
2.html根标签下有两个一级子标签
<head></head>头标签:
字符集
css引入
js引入
其他
<body></body>体标签:
定义要展示到页面主体的标签
3.专业词汇
标签tag 页面的一对<>
属性attribute 对标签特征进行设置的一种方式 属性一般在开始标签中定义
文本text 双标签中间的文字
元素 element 开始标签+属性+文本+结束标签 称之为一个元素
4.更多的语法细节
根标签只能有一个
无论是单标签还是双标签都需要正确关闭
标签可以嵌套但不能交叉嵌套
注释语法不能嵌套
属性必须有值,值必须加引号(h5中单引号双引号都可以),h5中属性名和值相同时可以省略属性值
html中不严格区分字符串使用单双引号
html标签不严格区分大小写,但不能大小写混用
html中不允许自定义标签名,强行自定义则无效
-->
<html>
  <head>
    <title>
    	第一个页面
    </title>
    <meta charset="utf-8"/>
  </head>
  <body>
    <h1>
      first page
    </h1>
  </body>
</html>
```

## 常用标签

### 标题标签

```html
<!--
标题 h1-h6
段落 p
换行 br hr (都是单标签,hr带分割线)

-->
```

### 列表标签

- 有序列表标签 ol
- 无序列表标签 ul
- 列表项标签 li
- 列表可以嵌套

### 超链接标签

herf 用于定义要跳转的目标资源的地址

- 完整的url http://www.gorway.cn:8443

- 相对路径 以当前资源的所在路径作为出发点去找目标资源

  ./表示当前资源的所在路径可以省略不写

  ../表示当前资源的上一层路径,需要时必须显式写出

- 绝对路径 以/开头

target 用于定义目标资源的打开方式

- _self 在当前窗口打开目标资源
- _blank 开启新窗口打开目标资源

### 图片标签

img

- src定义图片的路径
- title定义鼠标悬停时提示的文字
- alt定义图片加载失败时提示文字

### 表格标签

table 整张表格

- thead表头
- tbody表体
- tfoot表尾
- tr表中的一行
- td行中的一个单元格
- th自带居中加粗效果的td
- 使用colspan和rowspan来合并单元格

## 表单标签

form 表单标签

- action定义数据的提交地址
  - url
  - 相对路径
  - 绝对路径
  
- method 定义数据的提交方式
  - GET 参数会以键值对形式放在url后提交,数据会暴露在地址栏,相对不安全,地址栏长度有限,相比于POST效率更高
  
  - POST 参数默认不放到url后,数据不会直接暴露在地址栏上,相对安全
  
    - 数据是单独打包通过请求体发送,提交的数据量比较大
  
    - 请求体中可以是字符也可以是字节数据,可以提交文件

input 表单项标签 一定要定义name属性

- type 输入信息的表单项类型
  - text 单行普通文本框
  - password 密码框
  - submit 提交按钮
  - reset 重置
  - radio 单选框,多个单选框使用相同的name属性,会自带互斥效果
  - check 复选框
  - hidden 隐藏域,不显示在页面上,提交时会携带
  - file 文件上传框
- value 用于明确提交时的实参
- name 该属性用于明确提交时的参数名
- readonly只读,提交时携带
- disabled 不可用,提交时不携带

textarea多行文本框 没有value属性

select 下拉框

- option 选项

### 布局相关标签

div 块元素的一种 自己独占一行的元素  块内的css样式的宽、高等等 往往都是生效的

span 行内元素的一种 不会自己独占一行的元素 行内的css样式的宽、高等等 很多都是**不生效**的

### 特殊字符

对于html代码来说,某些符号是有特殊含义的,如果想显示这些特殊符号,需要进行转义.

w3school中有表格可查.

# CSS

层叠样式表

### 三种引入方式

#### 行内式

通过元素的style属性引入样式

`style="样式名:样式值;样式值:样式名;..."`

- 代码复用度低 不利于维护
- css代码和html代码交织在一起,影响阅读,文件大影响性能

#### 内嵌式

通过在head标签中的style标签定义本页面的公共样式

通过选择器确定样式的作用元素.

#### 外部样式表

将css代码单独放入一个.css文件中,哪个html需要这些代码就在head中通过link标签引入.

### css选择器

#### 元素选择器

根据标签的名字确定样式的作用元素

`标签名:{}`

缺点:某些同名元素不希望使用该样式或某些不同名元素也使用该样式

#### id选择器

根据标签的id值确定样式的作用元素

一般每个元素都有id属性,但在一个页面中,id属性值应唯一.

`#id值{}`

#### class选择器

根据元素的class属性值确定样式的作用元素

元素的class属性值可以重复 而且一个class属性可以有多个值

`.class值{}`

### css浮动

浮动一定不会把文字挡住

![image-20240405173508377](/Users/gorwaywong/Library/Application Support/typora-user-images/image-20240405173508377.png)

### css定位

position

- static 默认
- absolute 绝对
- relative 相对 相对元素原本的位置
- fixed 相对浏览器窗口的位置

### css盒子模型

css盒模型本质上是一个盒子

- margin(外边距) 清除边框外的区域 外边距是透明的
- border(边框) 围绕在内边距和内容外的边框
- padding(内边距) 清除内容周围的区域,内边距是透明的
- content(内容) 盒子的内容,显示文本和图像

![image-20240405195529243](/Users/gorwaywong/Library/Application Support/typora-user-images/image-20240405195529243.png)

# JavaScript

## 引入方式

### 内嵌式

在head中通过一对script标签定义脚本代码

- 一个html中可以有多个script标签
- 一对script标签不能在引入外部js文件的同时定义内部脚本
- script标签如果用于引入外部js文件,中间最好不要有任何字符 包括空格和换行

## JS的数据类型

JS中的变量的声明通通使用`var`

JS是弱类型语言,变量在声明时不指定类型,赋值时才确定类型.

#### 常见数据类型

数值类型  number

字符串类型 string

布尔类型 boolean

引用类型 Object

function类型 function

命名未赋值 undefined 值undefined

赋予null 类型Object 值null

##### 使用var声明变量的特点

- 弱类型变量,可以统一声明成var
- var声明的变量可以再次声明
- 变量可以使用不同的数据类型多次赋值
- JS的语句可以以;结尾,也可以不以;结尾
- 变量标识符严格区分大小写
- 标识符的命名规则参照Java
- 如果一个变量只声明,没赋值,那么值是undefined

## JS的运算符

除0结果是Infinity

模0结果是NaN

`==`如果两端的数据类型不一致,会尝试把两端的数据类型都转换为number再对比

`===`如果两端的数据类型不一致,直接返回false,相同则会继续对比

## JS的流程控制和函数

### JS分支结构

非空字符串会判断为true `''`会判断为false

非空对象会判断为true

非0number会判断为true

### 循环结构

跟Java大致相同

`for each`跟Java不同在于:`:`要改成`in`且`var index in arr`中的index是索引不是数组中的元素.

### JS函数声明

- 函数没有权限控制符
- 不用声明函数的返回类型,需要返回在函数体中直接return即可,也无需void关键字
- 参数列表中,无需数据类型
- 调用函数时,实参和形参的个数可以不一致
- 声明函数时需要用function关键字
- JS函数没有异常列表
- 没有访问修饰符
- 函数可作为参数传递给另一个方法

```js
function 函数名(){}
```

### 创建对象

```js
new Object()
```

或者

```js
{属性名:属性值,...,函数名:function(){}}
```

### JSON

- 属性名必须用“”包裹
- 属性值 字符串必须用“”包好,数字可以不做处理
- 通过`JSON.parse()`可以将一个JSON串转换为一个对象
- 通过`JSON.stringify()`将一个对象转换为JSON串

### 常用对象

#### 数组

数组的创建方式:

- `new Array()`创建空数组
- `new Array(5)`创建数组时给定长度
- `new Array(ele1,ele2,ele3,...,elen)`创建数组时指定元素值
- `[ele1,ele2,ele3,...,elen]`

### 常见事件

事件的触发:行为触发 DOM触发

- 鼠标事件
- 键盘事件
- 表单事件
- 页面加载事件 onload

事件的绑定方式

- 通过元素的属性绑定
- 通过DOM编程动态绑定

注意:

- 一个事件可以同时绑定多个函数
- 一个函数可以同时绑定多个事件

### 表单事件

`onsubmit`要写到form表单里,`type=“submit”`的button只是触发该form

`onreset`也是

### 事件通过DOM编程绑定和触发

```html
<script>
  // 通过dom获得要操作的元素
	var btn = document.getElementById("btn1")
  // 绑定一个单击事件
  btn.onclick = function(){
    alert("button clicked.")
  }
</script>
```

## BOM编程

window

- history 历史
- location 地址栏
- document 浏览器打开的html文档
- console F12开发者工具的控制台
- screen 屏幕
- navigator 浏览器软件本身
- sessionStorage 会话级存储
- localStorage  持久级存储

### window 对象是由浏览器提供的

无需new

#### 三种弹窗方式

- alert
- prompt
- confirm

...

## DOM编程

document对象代表整个html文档,DOM编程就是使用document对象的API完成对网页HTML文档进行动态修改,以实现网页数据和样式动态变化效果的编程.

1. 获得document dom树

   window.document

2. 从document中获取要操作的元素

   - 直接获取

     ```js
     var el1 = document.getElementById() // 根据元素的id值获取页面上唯一的一个元素
     var els = document.getElementByTagName() // 根据元素的标签名获取多个同名元素
     var els = document.getElementByName() // 根据元素的name属性值获取多个元素
     var els = document.getElementByClassName() // 根据元素的class属性值获取多个元素
     ```

   - 间接获取

     ```js
     var cs = div01.children // 通过父元素获取第一个子元素
     var firstChild = div01.firstElementChild // 通过父元素获取最后一个子元素
     var lastChild = div01.lastElementChild // 通过父元素获取最后一个子元素
     var parent = pinput.parentElement // 通过子元素获取父元素
     var pElement = pinput.previousElementSibling // 获取前面的第一个元素
     var nElement = pinput.nextElementSibling // 获取后面的第一个元素
     ```

3. 对元素进行操作

   - 操作元素的属性 `元素名.属性名=""`
   
   - 操作元素的样式 
   
     `元素名.style.样式名=“”`原始样式名中的“-”符号要转换驼峰式 background-color➡️backgroundColor 
   
   - 操作元素的文本
   
     `元素名.innerText`只识别文本
   
     `元素名.innerHTML	`同时可以识别HTML结构
   
   - 增删元素
   
     `var element = document.createElement("元素名")`
   
     `父元素.appendChild(子元素)`
   
     `父元素.insert Before(新元素,参照元素)`
   
     `父元素.replaceChild(新元素,被替换的元素)`
   
     哪个元素调用remove该元素就会从dom树中删除
   
   

# XML

可扩展标记语言,常见配置文件类型:

- properties文件,例如druid连接池就是使用properties文件作为配置文件
- XML文件,例如Tomcat使用的
- YAML文件,例如SpringBoot使用的
- json文件,常用来做文件传输,也可以用来做前端或者移动端的配置文件

# Tomcat

webapps文件夹是网络应用的路径,访问方式:

http://localhost:8080/examples/index.html

