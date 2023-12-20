# Java快速入门

- JDK：Java Development Kit
- JRE：Java Runtime Environment

JRE就是运行Java字节码的虚拟机。但是如果只有Java源码，要编译成Java字节码，就需要JDK。JDK除了包含JRE还提供了编译器、调试器等开发工具。

某个类定义的`public static void main(String[] args)`是Java程序的固定入口方法。

一个Java源码只能定义一个`public`类型的class，并且class名称和文件名要完全一致；

使用`javac`可以将`.java`源码编译成`.class`字节码；

使用`java`可以运行一个已编译的Java程序，参数是类名。

Java是面向对象的语言，一个程序的基本单位就是`class`。

类名要求：

- 类名必须以英文字母开头，后接字母，数字和下划线的组合。
- 习惯以大写字母开头

而方法名首字母小写。

- 单行注释//
- 多行注释/*开头\*/结尾
- /**开头，\*/结尾，如果有多行，每行通常以\*开头。这种特殊的多行注释需要写在类和方法的定义处，可以用于自动创建文档。

Eclipse提供了快捷键`Ctrl+Alt+L`（macOS`Command+Option+L`）快速格式化代码。

### Java基本数据类型

- 整数类型:byte,short,int,long
- 浮点数类型:float,double
- 字符类型:char
- 布尔类型:boolean

byte类型正好是一个字节,short 2字节,int 4字节,long 8字节,float 4字节,double 8字节,char 2字节.

定义整型时可以在数字中加下划线,使之更容易识别.

定义浮点数时可以用科学计数法表示(e表示为10的底数).

Java的char类型除了可表示标准的ASCII外,还可以表示一个Unicode字符.

```java
char zh='中'
```

char类型使用单引号'且仅有一个字符.

#### 引用类型

除了上述基本类型的变量,剩下的都是引用类型.比如string.

#### 常量和变量

定义变量的时候,如果加上`final`修饰符,这个变量就变成了常量.

定义变量的时候,类型的名字太长可以用var关键字省略变量类型.

```java
var sb = new StringBuilder();
```

在语句块中定义的变量,它有一个作用域:从定义处开始,到语句块结束.超出了作用域引用.

`++n`表示先加1再引用n,`n++`表示先引用n再加1.

#### 运算

通过与运算可以快速判断一个IP是否在给定的网段内.

运算优先级:

- ()
- !  ~ ++ --
- \* / %
- \+ -
- << >> >>>
- &
- |
- += -= *= /=

浮点数存在运算误差,所以比较两个浮点数是否相等常常会出现错误的结果.正确的比较方法是判断两个浮点数之差的绝对值是否小于一个很小的数.

需要特别注意,在一个复杂的四则运算中,两个整数的运算不会出现自动提升的情况.

```java
double d = 1.2 + 24 / 5;
// 结果是5.2
```

整数运算在除数为0时会报错,而浮点数运算在除数为0时,不会报错,但会返回几个特殊值:

- NaN表示Not a Number
- Infinity
- \-Infinity

整数和浮点数运算时,整型会自动提升为浮点型.

布尔运算的一个重要特点是短路运算.如果一个布尔运算的表达式能提前确定结果,则后续的计算不再执行,直接返回结果.

三元运算`b?x:y`会首先计算b,如果b为true,则只计算x,否则只计算y.此外,x和y的类型必须相同,因为返回值不是boolean,而是x和y之一.

### 字符和字符串

一个char保存一个Unicode字符.因为Java在内存中总是使用Unicode表示字符,所以一个英文字符和一个中文字符都用一个char表示,它们都占用两个字符.要显示一个字符的Unicode编码,只需将char类型直接赋值给int类型即可.

使用转义字符`\u`来表示一个字符.

```java
// 注意是十六进制:
char c3 = '\u0041'; // 'A'，因为十六进制0041 = 十进制65
char c4 = '\u4e2d'; // '中'，因为十六进制4e2d = 十进制20013
```

如果字符串里有",就用转义字符\

常见的转义字符包括:

- `\"` 表示字符`"`
- `\'` 表示字符`'`
- `\\` 表示字符`\`
- `\n` 表示换行符
- `\r` 表示回车符
- `\t` 表示Tab
- `\u####` 表示一个Unicode编码的字符

Java的编译器对字符串做了特殊照顾,可以使用+连接任意字符串和其他数据类型,这样极大方便了字符串的处理.如果用+连接字符串和其他数据类型,会将其他数据类型先自动转型为字符串再连接.

从Java13开始,字符串可以用"""..."""表示多行字符串(Text Blocks)了.

```java
String s = """
           SELECT * FROM
             users
           WHERE id > 100
           ORDER BY name DESC
           """;
```

上述多行字符串实际上是5行,在最后一个`DESC`后面还有个\n.

多行字符串前面共同的空格会被去掉.

Java中字符串不可变.

```java
package com.learn.JavaExamples;

public class Hello {
    public static void main(String[] args) {
        String s = "Hello";
        String t = s;
        s = "World";
        System.out.println(t);// 输出Hello
    }
}
```

#### 数组

- 数组所有元素初始化为默认值,整型都是0,浮点型是0.0,布尔型是false.
- 数组一旦创建后,大小就不可改变.

可以用`数组变量.length`获取数组大小.数组本身是引用类型.

### 流程控制

#### 输出

sout输出语句简写.

格式化输出使用System.out.printf()

Java的格式化功能提供的占位符号

| 占位符 | 说明                             |
| :----: | -------------------------------- |
|   %d   | 格式化输出整数                   |
|   %x   | 格式化输出十六进制整数           |
|   %f   | 格式化输出浮点数                 |
|   %e   | 格式化输出科学计数法表示的浮点数 |
|   %s   | 格式化字符串                     |

#### 输入

```java
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in); // 创建Scanner对象
        System.out.print("Input your name: "); // 打印提示
        String name = scanner.nextLine(); // 读取一行输入并获取字符串
        System.out.print("Input your age: "); // 打印提示
        int age = scanner.nextInt(); // 读取一行输入并获取整数
        System.out.printf("Hi, %s, you are %d\n", name, age); // 格式化输出
    }
}
```

要判断引用类型的变量内容是否相等,必须使用equals()方法.

```java
switch (option) {
  case 3:
      ...
      break;
  case 2:
      ...
      break;
  case 1:
      ...
      break;
  default:
    	...
      break;
}
```

`do while`至少会执行一次.

Java提供了一种for each循环,能够遍历所有“可迭代”的数据类型.

```java
public class Main{
  public static void main(String[] args){
    int[] ns = {1,4,9,16,25};
    for (int n:ns){
      System.out.println(n);
    }
  }
}
```

#### 数组

使用`Arrays.toString()`可以快速打印数组内容

调用`Arrays.sort()`可对数组进行排序.对数组进行排序实际上修改了数组本身.

打印多维数组可以使用`Arrays.deepToString()`.

多维数组的每个数据元素长度都不要求相同.

#### 命令行参数

```java
//程序的入口是main方法,而main方法可以接受一个命令行参数,它是一个String[]数组
public class Main {
    public static void main(String[] args) {
        for (String arg : args) {
            System.out.println(arg);
        }
    }
}
```

我们可以利用接收到的命令行参数,根据不同的参数执行不同的代码.

```java
public class Main {
    public static void main(String[] args) {
        for (String arg : args) {
            if ("-version".equals(arg)) {
                System.out.println("v 1.0");
                break;
            }
        }
    }
}
```

`$ javac Main.java`

`$ java Main -version`

输出`v 1.0`

# 面向对象

一个Java源文件可以包含多个类的定义,但只能定义一个public类,且public类名必须与文件名一致.如果要定义多个public类,必须拆到多个Java源文件中.

在方法内部,可以使用一个隐含的变量this,它始终指向当前示例.如果有局部变量和字段重名,那么局部变量优先级更高,就必须加上this.

#### 方法的参数绑定

基本类型参数的传递,是调用方值的复制.双方各自的后续修改,互不影响.

引用类型参数的传递,调用方的变量,和接收方的参数变量,指向的是同一个对象.双方任意一方对这个对象的修改,都会影响对方.

#### 构造方法

和普通方法相比,构造方法没有返回值(也没有void),调用构造方法必须用new操作符.

如果一个类没有定义构造方法,编译器会自动为我们生成一个默认构造方法.

```java
class Person{
  public Person(){
  }
}
```

如果我们自定义了一个构造方法,那么编译器就不再自动创建默认构造方法.如果既要能使用带参数的构造方法,又想保留不带参数的构造方法,那么只能把两个构造方法都定义出来.

一个构造方法可以调用其他构造方法,这样做的目的是便于代码复用.调用其他构造方法的语法是`this(...)`

#### 方法重载

方法名相同,但各自的参数不同,称为方法重载`Overload`

方法重载的返回值类型通常是相同的.

#### 继承

子类自动获得了父类的所有字段,严禁定义与父类重名的字段

在Java中,没有明确写extends的类,编译器会自动加上extends Object.Java只允许一个class继承自一个类,一个类有且只有一个父类.只有`Object`特殊它没有父类.

子类无法访问父类的private字段或者private方法.

为了让子类可以访问父类的字段,我们需要把private改为protected.

`protected`关键字可以把字段和方法的访问权限控制在继承树内部,一个protected字段和方法可以被其子类,以及子类的子类所访问.

`super`关键字表示父类(超类).子类引用父类的字段时,可以用`super.fieldName`

在Java中,任何class的构造方法,第一行必须是调用父类的构造方法.如果没有明确地调用父类的构造方法,编译器会自动加一句`super();`如果父类没有默认的构造方法,子类就必须显式调用`super()`并给出参数以便让编译器定位到父类的一个合适的构造方法.

#### 阻止继承

正常情况下,只要某个class没有`final`修饰符,那么任何类都可以从该class继承.

从**Java15**开始,允许使用`sealed`修饰class,并通过permits明确写出能够从该class继承的子类名称.(sealed类要启用必须使用参数`--enabled-preview`和`--source 15`)

```java
public sealed class Shape permits Rect, Circle, Triangle {
    ...
}
```

#### 向上转型

把一个子类类型安全地变为父类类型的赋值,被称为向上转型(upcasting)

#### 向下转型

如果把一个父类类型强制转换为子类类型,就是向下转型.

为了避免向下转型出错，Java提供了`instanceof`操作符，可以先判断一个实例究竟是不是某种类型：

继承是is关系，组合是has关系。

## 多态

在继承关系中,子类如果定义了一个与父类方法签名完全相同的方法,被称为覆写(Override).

Override和Overload不同的是，如果方法签名不同，就是Overload，Overload方法是一个新方法；如果方法签名相同，并且返回值也相同，就是`Override`。

注意：方法名相同，方法参数相同，但方法返回值不同，也是不同的方法。在Java程序中，出现这种情况，编译器会报错。

加上`@Override`可以让编译器帮助检查是否进行了正确的覆写。

Java的实例方法调用是基于运行时的实际类型的动态调用，而非变量的声明类型。

多态是指，针对某个类型的方法调用，其真正执行的方法取决于运行时期实际类型的方法.多态的特性就是,运行期才能动态决定调用的子类方法.

因为所有的`class`最终都继承自`Object`，而`Object`定义了几个重要的方法：

- `toString()`：把instance输出为`String`；
- `equals()`：判断两个instance是否逻辑相等；
- `hashCode()`：计算一个instance的哈希值。

在必要的情况下，我们可以覆写`Object`的这几个方法。

#### final

继承可以允许子类覆写父类的方法。如果一个父类不允许子类对它的某个方法进行覆写，可以把该方法标记为`final`。

如果一个类不希望任何其他类继承自它，那么可以把这个类本身标记为`final`。用`final`修饰的类不能被继承.

对于一个类的实例字段,同样可以用final修饰.用final修饰的字段在初始化后不能被修改.

#### 抽象类

如果父类的方法本身不需要实现任何功能，仅仅是为了定义方法签名，目的是让子类去覆写它，那么，可以把父类的方法声明为抽象方法.

如果一个`class`定义了方法，但没有具体执行代码，这个方法就是抽象方法，抽象方法用`abstract`修饰。

因为无法执行抽象方法，因此这个类也必须申明为抽象类（abstract class）。

我们无法实例化抽象类.

## 接口

在抽象类中，抽象方法本质上是定义接口规范：即规定高层类的接口，从而保证所有子类都有相同的接口实现，这样，多态就能发挥出威力。

如果一个抽象类没有字段，所有方法全部都是抽象方法,就可以把该抽象类改写为接口`interface`

接口定义的所有方法默认都是`public abstract`的，所以这两个修饰符不需要写出来（写不写效果都一样）。

Java的接口特指`interface`的定义，表示一个接口类型和一组方法签名，而编程接口泛指接口规范，如方法签名，数据格式，网络协议等。

|            | abstract class       | interface                   |
| :--------- | :------------------- | --------------------------- |
| 继承       | 只能extends一个class | 可以implements多个interface |
| 字段       | 可以定义实例字段     | 不能定义实例字段            |
| 抽象方法   | 可以定义抽象方法     | 可以定义抽象方法            |
| 非抽象方法 | 可以定义非抽象方法   | 可以定义default方法         |

一个`interface`可以继承自另一个`interface`。`interface`继承自`interface`使用`extends`，它相当于扩展了接口的方法。

在接口中，可以定义`default`方法。

实现类可以不必覆写`default`方法。`default`方法的目的是，当我们需要给接口新增一个方法时，会涉及到修改全部子类。如果新增的是`default`方法，那么子类就不必全部修改，只需要在需要覆写的地方去覆写新增方法。

`default`方法和抽象类的普通方法是有所不同的。因为`interface`没有字段，`default`方法无法访问字段，而抽象类的普通方法可以访问实例字段。

#### 接口和抽象类

1.接口不能被实例化

2.接口中所有的方法是public方法，接口中的抽象方法可以不同public修饰。

3.一个普通类实现接口，就必须将该接口的所有方法都实现

4.抽象类实现接口，可以不用实现接口的方法

5.接口中的属性只能是final的，而且是public static final修饰符

6.接口不能继承类，但可以继承多个别的接口

实现接口是对Java单继承机制的一种补充

继承的价值主要在于：解决代码的复用性和可维护性

接口的价值主要在于：设计好各种规范（方法）让其他类去实现，在一定程度上实现代码解耦.

## 静态字段和静态方法

实例字段在每个实例中都有自己的一个独立“空间”，但是静态字段只有一个共享“空间”，所有实例都会共享该字段。

不推荐用`实例变量.静态字段`去访问静态字段，因为在Java程序中，实例对象并没有静态字段。在代码中，实例对象能访问静态字段只是因为编译器可以根据实例类型自动转换为`类名.静态字段`来访问静态对象。

用`static`修饰的方法称为静态方法。调用静态方法不需要实例变量，通过类名就可以调用。

静态方法内部，无法访问`this`变量，也无法访问实例字段，它只能访问静态字段。

#### 接口的静态字段

因为`interface`是一个纯抽象类，所以它不能定义实例字段。但是，`interface`是可以有静态字段的，并且静态字段必须为`final`类型.

`interface`的字段只能是`public static final`类型.

## 包

Java定义了一种名字空间，称之为包：`package`。一个类总是属于某个包，类名（比如`Person`）只是一个简写，真正的完整类名是`包名.类名`。

在定义`class`的时候，我们需要在第一行声明这个`class`属于哪个包。

包没有父子关系。java.util和java.util.zip是不同的包，两者没有任何继承关系。

#### 包作用域

位于同一个包的类，可以访问包作用域的字段和方法。不用`public`、`protected`、`private`修饰的字段和方法就是包作用域。

还有一种`import static`的语法，它可以导入可以导入一个类的静态字段和静态方法：

```java
// 导入System类的所有静态字段和静态方法:
import static java.lang.System.*;
```

编写class的时候，编译器会自动帮我们做两个import动作：

- 默认自动`import`当前`package`的其他`class`；
- 默认自动`import java.lang.*`。

自动导入的是java.lang包，但类似java.lang.reflect这些包仍需要手动导入。

包名推荐使用倒置的域名.

## 作用域

#### public

定义为`public`的`class`、`interface`可以被其他任何类访问.

定义为`public`的`field`、`method`可以被其他类访问，前提是首先有访问`class`的权限.

#### private

定义为`private`的`field`、`method`无法被其他类访问.

实际上，确切地说，`private`访问权限被限定在`class`的内部，而且与方法声明顺序*无关*。推荐把`private`方法放到后面，因为`public`方法定义了类对外提供的功能，阅读代码的时候，应该先关注`public`方法.

由于Java支持嵌套类，如果一个类内部还定义了嵌套类，那么，嵌套类拥有访问`private`的权限.

定义在一个`class`内部的`class`称为嵌套类（`nested class`），Java支持好几种嵌套类。

#### protected

`protected`作用于继承关系。定义为`protected`的字段和方法可以被子类访问，以及子类的子类.

#### package作用域

包作用域是指一个类允许访问同一个`package`的没有`public`、`private`修饰的`class`，以及没有`public`、`protected`、`private`修饰的字段和方法。

包作用域是指一个类允许访问同一个`package`的没有`public`、`private`修饰的`class`，以及没有`public`、`protected`、`private`修饰的字段和方法。

一个`.java`文件只能包含一个`public`类,但可以包含多个非`public`类.

## 内部类

### Inner Class

如果一个类在另一个类的内部,这个类就是Inner Class.Inner Class的实例不能单独存在，必须依附于一个Outer Class的实例。

要实例化一个`Inner`，我们必须首先创建一个`Outer`的实例，然后，调用`Outer`实例的`new`来创建`Inner`实例：

```java
Outer.Inner inner = outer.new Inner();
```

这是因为Inner Class除了有一个`this`指向它自己，还隐含地持有一个Outer Class实例，可以用`Outer.this`访问这个实例。所以，实例化一个Inner Class不能脱离Outer实例。

Inner Class除了能引用Outer实例外,还可以修改Outer Class的`private`字段.

### Anonymous Class

还有一种定义Inner Class的方法，它不需要在Outer Class中明确地定义这个Class，而是在方法内部，通过匿名类（Anonymous Class）来定义。

在定义匿名类的时候就必须实例化它.

匿名类和Inner Class一样，可以访问Outer Class的`private`字段和方法。之所以我们要定义匿名类，是因为在这里我们通常不关心类名，比直接定义Inner Class可以少写很多代码。

### Static Nested Class

最后一种内部类和Inner Class类似，但是使用`static`修饰，称为静态内部类（Static Nested Class）.

用`static`修饰的内部类和Inner Class有很大的不同，它不再依附于`Outer`的实例，而是一个完全独立的类，因此无法引用`Outer.this`，但它可以访问`Outer`的`private`静态字段和静态方法。如果把`StaticNested`移到`Outer`之外，就失去了访问`private`的权限。

## classpath和jar

`classpath`是JVM用到的一个环境变量，它用来指示JVM如何搜索`class`。

因为Java是编译型语言，源码文件是`.java`，而编译后的`.class`文件才是真正可以被JVM执行的字节码。因此，JVM需要知道，如果要加载一个`abc.xyz.Hello`的类，应该去哪搜索对应的`Hello.class`文件。

现在我们假设`classpath`是`.;C:\work\project1\bin;C:\shared`，当JVM在加载`abc.xyz.Hello`这个类时，会依次查找：

- <当前目录>\abc\xyz\Hello.class
- C:\work\project1\bin\abc\xyz\Hello.class
- C:\shared\abc\xyz\Hello.class

`classpath`的设定方法有两种：

在系统环境变量中设置`classpath`环境变量，不推荐；

在启动JVM时设置`classpath`变量，推荐。

我们强烈*不推荐*在系统环境变量中设置`classpath`，那样会污染整个系统环境。在启动JVM时设置`classpath`才是推荐的做法。实际上就是给`java`命令传入`-classpath`或`-cp`参数：

```java
java -cp .;C:\work\project1\bin;C:\shared abc.xyz.Hello
```

### jar

jar包就是用来干这个事的，它可以把`package`组织的目录层级，以及各个目录下的所有文件（包括`.class`文件和其他文件）都打成一个jar文件，这样一来，无论是备份，还是发给客户，就简单多了。

因为jar包就是zip包，所以，直接在资源管理器中，找到正确的目录，点击右键，在弹出的快捷菜单中选择“发送到”，“压缩(zipped)文件夹”，就制作了一个zip文件。然后，把后缀从`.zip`改为`.jar`，一个jar包就创建成功。

# Java核心类

## 字符串和编码

在Java中，`String`是一个引用类型，它本身也是一个`class`。但是，Java编译器对`String`有特殊处理，即可以直接用`"..."`来表示一个字符串.

实际上字符串在`String`内部是通过一个`char[]`数组表示的.

Java字符串的一个重要特点就是字符串*不可变*。这种不可变性是通过内部的`private final char[]`字段，以及没有任何修改`char[]`的方法实现的。

当我们想要比较两个字符串是否相同时，要特别注意，我们实际上是想比较字符串的内容是否相同。必须使用`equals()`方法而不能用`==`。

要忽略大小写比较，使用`equalsIgnoreCase()`方法。

```java
// 是否包含子串:
"Hello".contains("ll"); // true
"Hello".indexOf("l"); // 2
"Hello".lastIndexOf("l"); // 3
"Hello".startsWith("He"); // true
"Hello".endsWith("lo"); // true
"Hello".substring(2); // "llo"
"Hello".substring(2, 4); // "ll"
```

使用`trim()`方法可以移除字符串首尾空白字符。空白字符包括空格，`\t`，`\r`，`\n`

```java
"  \tHello\r\n ".trim(); // "Hello"
```

`trim()`并没有改变字符串的内容，而是返回了一个新字符串。

另一个`strip()`方法也可以移除字符串首尾空白字符。它和`trim()`不同的是，类似中文的空格字符`\u3000`也会被移除

```java
"\u3000Hello\u3000".strip(); // "Hello"
" Hello ".stripLeading(); // "Hello "
" Hello ".stripTrailing(); // " Hello"
```

`String`还提供了`isEmpty()`和`isBlank()`来判断字符串是否为空和空白字符串

#### 替换子串

一种是根据字符或字符串替换：

```java
String s = "hello";
s.replace('l', 'w'); // "hewwo"，所有字符'l'被替换为'w'
s.replace("ll", "~~"); // "he~~o"，所有子串"ll"被替换为"~~"
```

通过正则表达式替换：

```java
String s = "A,,B;C ,D";
s.replaceAll("[\\,\\;\\s]+", ","); // "A,B,C,D"
```

#### 分割字符串

要分割字符串，使用`split()`方法，并且传入的也是正则表达式：

```java
String s = "A,B,C,D";
String[] ss = s.split("\\,"); // {"A", "B", "C", "D"}
```

#### 拼接字符串

拼接字符串使用静态方法`join()`，它用指定的字符串连接字符串数组。

```java
String[] arr = {"A", "B", "C"};
String s = String.join("***", arr); // "A***B***C"
```

#### 格式化字符串

字符串提供了`formatted()`方法和`format()`静态方法，可以传入其他参数，替换占位符，然后生成新的字符串。

#### 类型转换

要把任意基本类型或引用类型转换为字符串，可以使用静态方法`valueOf()`。这是一个重载方法，编译器会根据参数自动选择合适的方法：

```java
String.valueOf(123); // "123"
String.valueOf(45.67); // "45.67"
String.valueOf(true); // "true"
String.valueOf(new Object()); // 类似java.lang.Object@636be97c
```

把字符串转换为int

```java
int n1 = Integer.parseInt("123"); // 123
int n2 = Integer.parseInt("ff", 16); // 按十六进制转换，255
```

把字符串转换为boolean类型

```java
boolean b1 = Boolean.parseBoolean("true"); // true
boolean b2 = Boolean.parseBoolean("FALSE"); // false
```

要特别注意，`Integer`有个`getInteger(String)`方法，它不是将字符串转换为`int`，而是把该字符串对应的系统变量转换为`Integer`：

```java
Integer.getInteger("java.version"); // 版本号，11
```

转换为char[]

`String`和`char[]`类型可以互相转换，方法是：

```java
char[] cs = "Hello".toCharArray(); // String -> char[]
String s = new String(cs); // char[] -> String
```

如果修改了`char[]`数组，`String`并不会改变：

#### 编码

在Java中，`char`类型实际上就是两个字节的`Unicode`编码。如果我们要手动把字符串转换成其他编码，可以这样做：

```java
byte[] b1 = "Hello".getBytes(); // 按系统默认编码转换，不推荐
byte[] b2 = "Hello".getBytes("UTF-8"); // 按UTF-8编码转换
byte[] b2 = "Hello".getBytes("GBK"); // 按GBK编码转换
byte[] b3 = "Hello".getBytes(StandardCharsets.UTF_8); // 按UTF-8编码转换
```

转换编码后，就不再是`char`类型，而是`byte`类型表示的数组。

如果要把已知编码的`byte[]`转换为`String`，可以这样做：

```java
byte[] b = ...
String s1 = new String(b, "GBK"); // 按GBK转换
String s2 = new String(b, StandardCharsets.UTF_8); // 按UTF-8转换
```

始终牢记：Java的`String`和`char`在内存中总是以Unicode编码表示。

## StringBuilder和StringJoiner

为了能高效拼接字符串，Java标准库提供了`StringBuilder`，它是一个可变对象，可以预分配缓冲区，这样，往`StringBuilder`中新增字符时，不会创建新的临时对象。

```java
StringBuilder sb = new StringBuilder(1024);
for (int i = 0; i < 1000; i++) {
    sb.append(',');
    sb.append(i);
}
String s = sb.toString();
```

注意：对于普通的字符串`+`操作，并不需要我们将其改写为`StringBuilder`，因为Java编译器在编译时就自动把多个连续的`+`操作编码为`StringConcatFactory`的操作。在运行期，`StringConcatFactory`会自动把字符串连接操作优化为数组复制或者`StringBuilder`操作。

你可能还听说过`StringBuffer`，这是Java早期的一个`StringBuilder`的线程安全版本，它通过同步来保证多个线程操作`StringBuffer`也是安全的，但是同步会带来执行速度的下降。

`StringBuilder`和`StringBuffer`接口完全相同，现在完全没有必要使用`StringBuffer`。

用分隔符拼接数组的需求很常见，所以Java标准库还提供了一个`StringJoiner`来干这个事，还可以指定开头结尾：

```java
import java.util.StringJoiner;
public class Main {
    public static void main(String[] args) {
        String[] names = {"Bob", "Alice", "Grace"};
        var sj = new StringJoiner(", ", "Hello ", "!");
        for (String name : names) {
            sj.add(name);
        }
        System.out.println(sj.toString());
    }
}
```

`String`还提供了一个静态方法`join()`，这个方法在内部使用了`StringJoiner`来拼接字符串，在不需要指定“开头”和“结尾”的时候，用`String.join()`更方便。

## 包装类型

Java的数据类型分两种：

- 基本类型：`byte`，`short`，`int`，`long`，`boolean`，`float`，`double`，`char`
- 引用类型：所有`class`和`interface`类型。

| 基本类型 | 对应的引用类型      |
| :------- | :------------------ |
| boolean  | java.lang.Boolean   |
| byte     | java.lang.Byte      |
| short    | java.lang.Short     |
| int      | java.lang.Integer   |
| long     | java.lang.Long      |
| float    | java.lang.Float     |
| double   | java.lang.Double    |
| char     | java.lang.Character |

### Auto Boxing自动装箱

Java编译器可以帮助我们自动在`int`和`Integer`之间转型：

```java
Integer n = 100; // 编译器自动使用Integer.valueOf(int)
int x = n; // 编译器自动使用Integer.intValue()
```

自动装箱和自动拆箱只发生在编译阶段，目的是为了少写代码。

#### 不变类

所有的包装类型都是不变类。对两个`Integer`实例进行比较要特别注意：绝对不能用`==`比较，因为`Integer`是引用类型，必须使用`equals()`比较。

因为`Integer.valueOf()`可能始终返回同一个`Integer`实例，因此，在我们自己创建`Integer`的时候，以下两种方法：

- 方法1：`Integer n = new Integer(100);`
- 方法2：`Integer n = Integer.valueOf(100);`

方法2更好，因为方法1总是创建新的`Integer`实例，方法2把内部优化留给`Integer`的实现者去做，即使在当前版本没有优化，也有可能在下一个版本进行优化。

我们把能创建“新”对象的静态方法称为静态工厂方法。`Integer.valueOf()`就是静态工厂方法，它尽可能地返回缓存的实例以节省内存。

创建新对象时，优先选用静态工厂方法而不是new操作符。

数据的存储和显示要分离。

所有的整数和浮点数的包装类型都继承自`Number`，因此，可以非常方便地直接通过包装类型获取各种基本类型：

```java
// 向上转型为Number:
Number num = new Integer(999);
// 获取byte, int, long, float, double:
byte b = num.byteValue();
int n = num.intValue();
long ln = num.longValue();
float f = num.floatValue();
double d = num.doubleValue();
```

在Java中，并没有无符号整型（Unsigned）的基本数据类型。`byte`、`short`、`int`和`long`都是带符号整型，最高位是符号位。而C语言则提供了CPU支持的全部数据类型，包括无符号整型。无符号整型和有符号整型的转换在Java中就需要借助包装类型的静态方法完成。

把一个负的`byte`按无符号整型转换为`int`:

```java
public class Main {
    public static void main(String[] args) {
        byte x = -1;
        byte y = 127;
        System.out.println(Byte.toUnsignedInt(x)); // 255
        System.out.println(Byte.toUnsignedInt(y)); // 127
    }
}
```

## JavaBean

如果读写方法符合以下这种命名规范：

```java
// 读方法:
public Type getXyz()
// 写方法:
public void setXyz(Type value)
```

`boolean`字段比较特殊，它的读方法一般命名为`isXyz()`

我们通常把一组对应的读方法（`getter`）和写方法（`setter`）称为属性（`property`）。例如，`name`属性：

- 对应的读方法是`String getName()`
- 对应的写方法是`setName(String)`

只有`getter`的属性称为只读属性（read-only），只有`setter`的属性称为只写属性（write-only）。

JavaBean主要用来传递数据，即把一组数据组合成一个JavaBean便于传输。此外，JavaBean可以方便地被IDE工具分析，生成读写属性的代码，主要用在图形界面的可视化设计中。

Idea可以快速生成getters&setters

使用`Introspector.getBeanInfo()`可以获取属性列表：

```java
public class Main {
    public static void main(String[] args) throws Exception {
        BeanInfo info = Introspector.getBeanInfo(Person.class);
        for (PropertyDescriptor pd : info.getPropertyDescriptors()) {
            System.out.println(pd.getName());
            System.out.println("  " + pd.getReadMethod());
            System.out.println("  " + pd.getWriteMethod());
        }
    }
}

class Person {
    private String name;
    private int age;

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getAge() {
        return age;
    }

    public void setAge(int age) {
        this.age = age;
    }
}
```

## 枚举类enum

```java
enum Weekday {
    SUN, MON, TUE, WED, THU, FRI, SAT;
}
```

和`int`定义的常量相比，使用`enum`定义枚举有如下好处：

首先，`enum`常量本身带有类型信息，即`Weekday.SUN`类型是`Weekday`，编译器会自动检查出类型错误。

其次，不可能引用到非枚举的值，因为无法通过编译。

最后，不同类型的枚举不能互相比较或者赋值，因为类型不符。

- 定义的`enum`类型总是继承自`java.lang.Enum`，且无法被继承；
- 只能定义出`enum`的实例，而无法通过`new`操作符创建`enum`的实例；
- 定义的每个实例都是引用类型的唯一实例；
- 可以将`enum`类型用于`switch`语句。

默认情况下，对枚举常量调用`toString()`会返回和`name()`一样的字符串。

判断枚举常量的名字，要始终使用name()方法，绝不能调用toString()！

枚举类可以应用在`switch`语句中。

可以为`enum`编写构造方法、字段和方法

`enum`的构造方法要声明为`private`，字段强烈建议声明为`final`。

## 记录类

一个不变类具有以下特点：

1. 定义class时使用`final`，无法派生子类；
2. 每个字段使用`final`，保证创建实例后无法修改任何字段。

为了保证不变类的比较，还需要正确覆写`equals()`和`hashCode()`方法，这样才能在集合类中正常使用。

## BigInteger

`java.math.BigInteger`就是用来表示任意大小的整数。`BigInteger`内部用一个`int[]`数组来模拟一个非常大的整数。

对`BigInteger`做运算的时候，只能使用实例方法：

```java
BigInteger i1 = new BigInteger("1234567890");
BigInteger i2 = new BigInteger("12345678901234567890");
BigInteger sum = i1.add(i2); // 12345678902469135780
```

- 转换为`byte`：`byteValue()`
- 转换为`short`：`shortValue()`
- 转换为`int`：`intValue()`
- 转换为`long`：`longValue()`
- 转换为`float`：`floatValue()`
- 转换为`double`：`doubleValue()`

如果`BigInteger`表示的范围超过了基本类型的范围，转换时将丢失高位信息，即结果不一定是准确的。如果需要准确地转换成基本类型，可以使用`intValueExact()`、`longValueExact()`等方法，在转换时如果超出范围，将直接抛出`ArithmeticException`异常。

## BigDecimal

和`BigInteger`类似，`BigDecimal`可以表示一个任意大小且精度完全准确的浮点数。

`BigDecimal`用`scale()`表示小数位数。

可以对一个`BigDecimal`设置它的`scale`，如果精度比原始值低，那么按照指定的方法进行四舍五入或者直接截断。

对`BigDecimal`做加、减、乘时，精度不会丢失，但是做除法时，存在无法除尽的情况，这时，就必须指定精度以及如何进行截断：

```java
BigDecimal d1 = new BigDecimal("123.456");
BigDecimal d2 = new BigDecimal("23.456789");
BigDecimal d3 = d1.divide(d2, 10, RoundingMode.HALF_UP); // 保留10位小数并四舍五入
BigDecimal d4 = d1.divide(d2); // 报错：ArithmeticException，因为除不尽
```

还可以对`BigDecimal`做除法的同时求余数：

```java
public class Main {
    public static void main(String[] args) {
        BigDecimal n = new BigDecimal("12.345");
        BigDecimal m = new BigDecimal("0.12");
        BigDecimal[] dr = n.divideAndRemainder(m);
        System.out.println(dr[0]); // 102
        System.out.println(dr[1]); // 0.105
    }
}
```

## 常用工具类

### Math

#### 求绝对值

```java
Math.abs(100);
```

#### 最大最小值

```java
Math.max(100,99);
Math.min(100,99);
```

#### 计算x的y次方

```java
Math.pow(2,10);
```

#### 计算x的开方

```java
Math.sqrt(x);
```

#### 计算e的x次方

```java
Math.exp(2);
```

#### 计算以e为底的对数

```java
Math.log(4);
```

#### 计算以10为底的对数

```java
Math.log10(100);
```

#### 三角函数

```java
Math.sin(3.14); // 0.00159...
Math.cos(3.14); // -0.9999...
Math.tan(3.14); // -0.0015...
Math.asin(1.0); // 1.57079...
Math.acos(1.0); // 0.0
```

#### 数学常量

```java
double pi = Math.PI; // 3.14159...
double e = Math.E; // 2.7182818...
Math.sin(Math.PI / 6); // sin(π/6) = 0.5
```

如果我们要生成一个区间在`[MIN, MAX)`的随机数，可以借助`Math.random()`实现

```java
// 区间在[MIN, MAX)的随机数
public class Main {
    public static void main(String[] args) {
        double x = Math.random(); // x的范围是[0,1)
        double min = 10;
        double max = 50;
        double y = x * (max - min) + min; // y的范围是[10,50)
        long n = (long) y; // n的范围是[10,50)的整数
        System.out.println(y);
        System.out.println(n);
    }
}
```

Java标准库还提供了一个`StrictMath`，它提供了和`Math`几乎一模一样的方法。这两个类的区别在于，由于浮点数计算存在误差，不同的平台（例如x86和ARM）计算的结果可能不一致（指误差不同），因此，`StrictMath`保证所有平台计算结果都是完全相同的，而`Math`会尽量针对平台优化计算速度，所以，绝大多数情况下，使用`Math`就足够了。

### HexFormat

```java
import java.util.HexFormat;

public class Main {
    public static void main(String[] args) throws InterruptedException {
        byte[] data = "Hello".getBytes();
        HexFormat hf = HexFormat.of();
        String hexData = hf.formatHex(data); // 48656c6c6f
    }
}
```

如果要定制转换格式，则使用定制的`HexFormat`实例：

```java
// 分隔符为空格，添加前缀0x，大写字母:
HexFormat hf = HexFormat.ofDelimiter(" ").withPrefix("0x").withUpperCase();
hf.formatHex("Hello".getBytes())); // 0x48 0x65 0x6C 0x6C 0x6F
```

从十六进制字符串到`byte[]`数组转换，使用`parseHex()`方法：

```java
byte[] bs = HexFormat.of().parseHex("48656c6c6f");
```

### Random

`Random`用来创建伪随机数。所谓伪随机数，是指只要给定一个初始的种子，产生的随机数序列是完全一样的。

要生成一个随机数，可以使用`nextInt()`、`nextLong()`、`nextFloat()`、`nextDouble()`：

```java
Random r = new Random();
r.nextInt(); // 2071575453,每次都不一样
r.nextInt(10); // 5,生成一个[0,10)之间的int
r.nextLong(); // 8811649292570369305,每次都不一样
r.nextFloat(); // 0.54335...生成一个[0,1)之间的float
r.nextDouble(); // 0.3716...生成一个[0,1)之间的double
```

创建`Random`实例时，如果不给定种子，就使用系统当前时间戳作为种子，因此每次运行时，种子不同，得到的伪随机数序列就不同。

### SecureRandom

`SecureRandom`是用来创建不可预测的安全的随机数的。

```java
import java.util.Arrays;
import java.security.SecureRandom;
import java.security.NoSuchAlgorithmException;

public class Main {
    public static void main(String[] args) {
        SecureRandom sr = null;
        try {
            sr = SecureRandom.getInstanceStrong(); // 获取高强度安全随机数生成器
        } catch (NoSuchAlgorithmException e) {
            sr = new SecureRandom(); // 获取普通的安全随机数生成器
        }
        byte[] buffer = new byte[16];
        sr.nextBytes(buffer); // 用安全随机数填充buffer
        System.out.println(Arrays.toString(buffer));
    }
}
```

