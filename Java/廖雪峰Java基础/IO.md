# IO

IO流以`byte`（字节）为最小单位，因此也称为*字节流*。

如果我们需要读写的是字符，并且字符不全是单字节表示的ASCII字符，那么，按照`char`来读写显然更方便，这种流称为*字符流*。

Java提供了`Reader`和`Writer`表示字符流，字符流传输的最小数据单位是`char`。

## File对象

Java的标准库`java.io`提供了`File`对象来操作文件和目录。

注意Windows平台使用`\`作为路径分隔符，在Java字符串中需要用`\\`表示一个`\`。Linux平台使用`/`作为路径分隔符.

用`.`表示当前目录，`..`表示上级目录。

### 文件和目录

`File`对象既可以表示文件，也可以表示目录。特别要注意的是，构造一个`File`对象，即使传入的文件或目录不存在，代码也不会出错，因为构造一个`File`对象，并不会导致任何磁盘操作。只有当我们调用`File`对象的某些方法的时候，才真正进行磁盘操作。

调用`isFile()`，判断该`File`对象是否是一个已存在的文件，调用`isDirectory()`，判断该`File`对象是否是一个已存在的目录.

用`File`对象获取到一个文件时，还可以进一步判断文件的权限和大小：

- `boolean canRead()`：是否可读；
- `boolean canWrite()`：是否可写；
- `boolean canExecute()`：是否可执行；
- `long length()`：文件字节大小。

对目录而言，是否可执行表示能否列出它包含的文件和子目录。

当File对象表示一个文件时，可以通过`createNewFile()`创建一个新文件，用`delete()`删除该文件：

```java
File file = new File("/path/to/file");
if (file.createNewFile()){
  if(file.delete()){
    
  }
}
```

有些时候，程序需要读写一些临时文件，File对象提供了`createTempFile()`来创建一个临时文件，以及`deleteOnExit()`在JVM退出时自动删除该文件。

```java
import java.io.*;
public class Main{
  public static void main(String[] args) throws IOException{
    FIle f = File.createTempFile("tmp-",".txt");//提供临时文件的前缀和后缀
    f.deleteOnExit();//JVM退出时自动删除
    System.out.println(f.isFile());
    System.out.println(f.getAbsolutePath);
  }
}
```

### 遍历文件和目录

当File对象表示一个目录时，可以使用`list()`和`listFiles()`列出目录下的文件和子目录名。`listFiles()`提供了一系列重载方法，可以过滤不想要的文件和目录：

```java
import java.io.*;
public class Main{
  public static void main(String[] args) throws IOException{
    File f = new File("C:\\Windows");
    File[] fs1 = f.listFiles();//列出所有文件和子目录
    printFiles(fs1);
    File[] fs2 = f.listFiles(new FilenameFilter(){//仅列出exe文件
      public boolean accept(File dir,String name){
        return name.endsWith(".exe");//返回true表示接受该文件
      }
    });
    printFiles(fs2);
  }
  static void printFiles(File[] files){
    System.out.println("============");
    if(files != null){
      for(File f : files){
        System.out.println(f);
      }
    }
    System.out.println("==========");
  }
}
```

和文件操作类似，File对象如果表示一个目录，可以通过以下方法创建和删除目录：

- `boolean mkdir()`：创建当前File对象表示的目录；
- `boolean mkdirs()`：创建当前File对象表示的目录，并在必要时将不存在的父目录也创建出来；
- `boolean delete()`：删除当前File对象表示的目录，当前目录必须为空才能删除成功。

### Path

Java标准库还提供了一个`Path`对象，它位于`java.nio.file`包。`Path`对象和`File`对象类似，但操作更加简单：

```java
import java.io.*;
import java.nio.file.*;

public class Main {
    public static void main(String[] args) throws IOException {
        Path p1 = Paths.get(".", "project", "study"); // 构造一个Path对象
        System.out.println(p1);
        Path p2 = p1.toAbsolutePath(); // 转换为绝对路径
        System.out.println(p2);
        Path p3 = p2.normalize(); // 转换为规范路径
        System.out.println(p3);
        File f = p3.toFile(); // 转换为File对象
        System.out.println(f);
        for (Path p : Paths.get("..").toAbsolutePath()) { // 可以直接遍历Path
            System.out.println("  " + p);
        }
    }
}
```

如果需要对目录进行复杂的拼接、遍历等操作，使用`Path`对象更方便。

## InputStream

`InputStream`就是Java标准库提供的最基本的输入流。它位于`java.io`这个包里。`java.io`包提供了所有同步IO的功能。

要特别注意的一点是，`InputStream`并不是一个接口，而是一个抽象类，它是所有输入流的超类。

这个抽象类定义的一个最重要的方法就是`int read()`，签名如下：

```java
public abstract int read() throws IOException;
```

这个方法会读取输入流的下一个字节，并返回字节表示的`int`值（0~255）。如果已读到末尾，返回`-1`表示不能继续读取了。

`FileInputStream`是`InputStream`的一个子类。顾名思义，`FileInputStream`就是从文件流中读取数据。下面的代码演示了如何完整地读取一个`FileInputStream`的所有字节：

```java
public void readFile() throws IOException{
  //创建一个FileInputStream对象
  InputStream input = new FileInputStream("src/readme.txt");
  for(;;){
    int n = input.read();//反复调用read()方法,直到返回-1
    if(n == -1){
      break;
    }
    System.out.println(n);//打印byte的值
  }
  input.close();//关闭流
}
```

因此，我们需要用`try ... finally`来保证`InputStream`在无论是否发生IO错误的时候都能够正确地关闭：

```java
public void readFile() throws IOException {
    InputStream input = null;
    try {
        input = new FileInputStream("src/readme.txt");
        int n;
        while ((n = input.read()) != -1) { // 利用while同时读取并判断
            System.out.println(n);
        }
    } finally {
        if (input != null) { input.close(); }
    }
}
```

### 缓冲

在读取流的时候，一次读取一个字节并不是最高效的方法。很多流支持一次性读取多个字节到缓冲区，对于文件和网络流来说，利用缓冲区一次性读取多个字节效率往往要高很多。`InputStream`提供了两个重载方法来支持读取多个字节：

- `int read(byte[] b)`：读取若干字节并填充到`byte[]`数组，返回读取的字节数
- `int read(byte[] b, int off, int len)`：指定`byte[]`数组的偏移量和最大填充数

利用上述方法一次读取多个字节时，需要先定义一个`byte[]`数组作为缓冲区，`read()`方法会尽可能多地读取字节到缓冲区， 但不会超过缓冲区的大小。`read()`方法的返回值不再是字节的`int`值，而是返回实际读取了多少个字节。如果返回`-1`，表示没有更多的数据了。

### 阻塞

在调用`InputStream`的`read()`方法读取数据时，我们说`read()`方法是阻塞（Blocking）的。它的意思是，对于下面的代码：

```java
int n;
n = input.read(); // 必须等待read()方法返回才能执行下一行代码
int m = n;
```

总是使用`try(resource)`来保证`InputStream`正确关闭。

## OutputStream

`OutputStream`也是抽象类，它是所有输出流的超类。

这个抽象类定义的一个最重要的方法就是`void write(int b)`，签名如下：

```java
public abstract void write(int b) throws IOException;
```

这个方法会写入一个字节到输出流。要注意的是，虽然传入的是`int`参数，但只会写入一个字节，即只写入`int`最低8位表示字节的部分（相当于`b & 0xff`）。

和`InputStream`类似，`OutputStream`也提供了`close()`方法关闭输出流，以便释放系统资源。要特别注意：`OutputStream`还提供了一个`flush()`方法，它的目的是将缓冲区的内容真正输出到目的地。

通常情况下，我们不需要调用这个`flush()`方法，因为缓冲区写满了`OutputStream`会自动调用它，并且，在调用`close()`方法关闭`OutputStream`之前，也会自动调用`flush()`方法。

### 阻塞

和`InputStream`一样，`OutputStream`的`write()`方法也是阻塞的。

同时操作多个`AutoCloseable`资源时，在`try(resource) { ... }`语句中可以同时写出多个资源，用`;`隔开。例如，同时读写两个文件：

```java
// 读取input.txt，写入output.txt:
try (InputStream input = new FileInputStream("input.txt");
     OutputStream output = new FileOutputStream("output.txt"))
{
    input.transferTo(output); // transferTo的作用是?
}
```

## Filter模式

Java的IO标准库提供的`InputStream`根据来源可以包括：

- `FileInputStream`：从文件读取数据，是最终数据源；
- `ServletInputStream`：从HTTP请求读取数据，是最终数据源；
- `Socket.getInputStream()`：从TCP连接读取数据，是最终数据源；
- ...

### 编写FilterInputStream

我们也可以自己编写`FilterInputStream`，以便可以把自己的`FilterInputStream`“叠加”到任何一个`InputStream`中。

下面的例子演示了如何编写一个`CountInputStream`，它的作用是对输入的字节进行计数：

```java
import java.io.*;
public class Main{
  public static void main(String[] args) throws IOException{
    byte[] data = "hello,world!".getBytes("UTF-8");
    try(CountInputStream input = new CountInputStream(new ByteArrayInputStream(data))){
      int n;
      while ((n = input.read()) != -1){
        System.out.println((char)n);
      }
      System.out.println("Total read" + input.getBytesRead() + bytes);
    }
  }
}

class CountInputStream extends FilterInputStream {
  private int count = 0;
  
  CountInputStream(InputStream in){
    super(in);
  }
  
  public int getBytesRead(){
    return this.count;
  }
  
  public int read() throws IOException{
    int n = in.read();
    if (n != -1){
      this.count++;
    }
    return n;
  }
  public int read(byte[] b, int off,int len) throws IOException {
    int n = in.read(b,off,len);
    if (n != -1){
      this.count += n;
    }
    return n;
  }
}
```



Java的IO标准库使用Filter模式为`InputStream`和`OutputStream`增加功能：

- 可以把一个`InputStream`和任意个`FilterInputStream`组合；
- 可以把一个`OutputStream`和任意个`FilterOutputStream`组合。

Filter模式可以在运行期动态增加功能（又称Decorator模式）。

## 操作Zip

`ZipInputStream`是一种`FilterInputStream`，它可以直接读取zip包的内容.

另一个`JarInputStream`是从`ZipInputStream`派生，它增加的主要功能是直接读取jar文件里面的`MANIFEST.MF`文件。因为本质上jar包就是zip包，只是额外附加了一些固定的描述文件。

### 读取zip包

我们要创建一个`ZipInputStream`，通常是传入一个`FileInputStream`作为数据源，然后，循环调用`getNextEntry()`，直到返回`null`，表示zip流结束。

一个`ZipEntry`表示一个压缩文件或目录，如果是压缩文件，我们就用`read()`方法不断读取，直到返回`-1`:

```java
try(ZipInputStream zip = new ZipInputStream(new FileInputStream(...))){
  ZipEntry entry = null;
  while ((entry = zip.getNextEntry()) != null) {
    String name = entry.getName();
    if (!entry.isDirectory()){
      int n;
      while ((n = zip.read()) != -1){
        ...
      }
    }
  }
}
```

### 写入zip包

`ZipOutputStream`是一种`FilterOutputStream`，它可以直接写入内容到zip包。我们要先创建一个`ZipOutputStream`，通常是包装一个`FileOutputStream`，然后，每写入一个文件前，先调用`putNextEntry()`，然后用`write()`写入`byte[]`数据，写入完毕后调用`closeEntry()`结束这个文件的打包。

```java
try(ZipOutputStream zip = new ZipOutputStream(new FileOutputStream(...))){
  File[] files = ...;
  for (File file : files){
    zip.putNextEntry(new ZipEntry(file.getName()));
    zip.write(Files.readAllBytes(file.toPath()));
    zip.closeEntry();
  }
}
```

## 读取classpath资源

从classpath读取文件就可以避免不同环境下文件路径不一致的问题：如果我们把`default.properties`文件放到classpath中，就不用关心它的实际存放路径。

在classpath中的资源文件，路径总是以`／`开头，我们先获取当前的`Class`对象，然后调用`getResourceAsStream()`就可以直接从classpath读取任意的资源文件：

```java
try(InputStream input = getClass().getResourceAsStream("/default.properties")){
  if (input != null) {
    // TODO:
  }
}
```

## 序列化

序列化是指把一个Java对象变成二进制内容，本质上就是一个`byte[]`数组。

为什么要把Java对象序列化呢？因为序列化后可以把`byte[]`保存到文件中，或者把`byte[]`通过网络传输到远程，这样，就相当于把Java对象存储到文件或者通过网络传输出去了。

有序列化，就有反序列化，即把一个二进制内容（也就是`byte[]`数组）变回Java对象。有了反序列化，保存到文件中的`byte[]`数组又可以“变回”Java对象，或者从网络上读取`byte[]`并把它“变回”Java对象。

一个Java对象要能序列化，必须实现一个特殊的`java.io.Serializable`接口，它的定义如下：

```java
public interface Serializable {
}
```

### 序列化

把一个Java对象变为`byte[]`数组，需要使用`ObjectOutputStream`。它负责把一个Java对象写入一个字节流：

```java
import java.io.*;
import java.util.Arrays;
public class Main{
  public static void mian(String[] args) throws IOException{
    ByteArrayOutputStream buffer = new ByteArrayOutputStream();
    try(ObjectOutputStream output = new ObjectOutputStream(buffer)){
      //写入int：
      output.writeInt(12345);
      //写入String:
      output.writeUTF("Hello");
      //写入Object
      output.writeObject(Double.valueOf(123.456));
    }
    System.out.println(Arrays.toString(buffer.toByteArray()));
  }
}
```

`ObjectOutputStream`既可以写入基本类型，如`int`，`boolean`，也可以写入`String`（以UTF-8编码），还可以写入实现了`Serializable`接口的`Object`。

因为写入`Object`时需要大量的类型信息，所以写入的内容很大。

### 凡序列化

和`ObjectOutputStream`相反，`ObjectInputStream`负责从一个字节流读取Java对象：

```java
try(ObjectInputStram input = new ObjectInputStream(...)) {
  int n = intput.readInt();
  String s = input.readUTF();
  Double d = (Double) input.readObject();
}
```

除了能读取基本类型和`String`类型外，调用`readObject()`可以直接返回一个`Object`对象。要把它变成一个特定类型，必须强制转型。

`readObject()`可能抛出的异常有：

- `ClassNotFoundException`：没有找到对应的Class；
- `InvalidClassException`：Class不匹配。

对于`ClassNotFoundException`，这种情况常见于一台电脑上的Java程序把一个Java对象，例如，`Person`对象序列化以后，通过网络传给另一台电脑上的另一个Java程序，但是这台电脑的Java程序并没有定义`Person`类，所以无法反序列化。

对于`InvalidClassException`，这种情况常见于序列化的`Person`对象定义了一个`int`类型的`age`字段，但是反序列化时，`Person`类定义的`age`字段被改成了`long`类型，所以导致class不兼容。

要特别注意反序列化的几个重要特点：

反序列化时，由JVM直接构造出Java对象，不调用构造方法，构造方法内部的代码，在反序列化时根本不可能执行。

### 安全性

因为Java的序列化机制可以导致一个实例能直接从`byte[]`数组创建，而不经过构造方法，因此，它存在一定的安全隐患。一个精心构造的`byte[]`数组被反序列化后可以执行特定的Java代码，从而导致严重的安全漏洞。

实际上，Java本身提供的基于对象的序列化和反序列化机制既存在安全性问题，也存在兼容性问题。更好的序列化方法是通过JSON这样的通用数据结构来实现，只输出基本类型（包括String）的内容，而不存储任何与代码相关的信息。

Java的序列化机制仅适用于Java，如果需要与其它语言交换数据，必须使用通用的序列化方法，例如JSON。

## Reader

`Reader`是Java的IO库提供的另一个输入流接口。和`InputStream`的区别是，`InputStream`是一个字节流，即以`byte`为单位读取，而`Reader`是一个字符流，即以`char`为单位读取：

| InputStream                         | Reader                                |
| :---------------------------------- | :------------------------------------ |
| 字节流，以`byte`为单位              | 字符流，以`char`为单位                |
| 读取字节（-1，0~255）：`int read()` | 读取字符（-1，0~65535）：`int read()` |
| 读到字节数组：`int read(byte[] b)`  | 读到字符数组：`int read(char[] c)`    |

`java.io.Reader`是所有字符输入流的超类，它最主要的方法是：

```
public int read() throws IOException;
```

这个方法读取字符流的下一个字符，并返回字符表示的`int`，范围是`0`~`65535`。如果已读到末尾，返回`-1`。

### FileReader

`FileReader`是`Reader`的一个子类，它可以打开文件并获取`Reader`。下面的代码演示了如何完整地读取一个`FileReader`的所有字符：

```java
public void readFile() throws IOException{
  //创建一个FileReader对象
  Reader reader = new FileReader("src/readme.txt",StandardCharsets.UTF_8);
  for(;;){
    int n = reader.read();//反复调用read()方法,直到返回-1
    if(n == -1){
      break;
    }
    System.out.println((char)n);//打印char
  }
  reader.close();
}
```

```java
public int read() throws IOException;
```

这个方法读取字符流的下一个字符，并返回字符表示的`int`，范围是`0`~`65535`。如果已读到末尾，返回`-1`。

`Reader`还提供了一次性读取若干字符并填充到`char[]`数组的方法：

```java
public int read(char[] c) throws IOException
```

它返回实际读入的字符个数，最大不超过`char[]`数组的长度。返回`-1`表示流结束。

### InputStreamReader

既然`Reader`本质上是一个基于`InputStream`的`byte`到`char`的转换器，那么，如果我们已经有一个`InputStream`，想把它转换为`Reader`，是完全可行的。`InputStreamReader`就是这样一个转换器，它可以把任何`InputStream`转换为`Reader`。示例代码如下：

```java
//持有InputStream
InputStream input = new FileInputStream("src/readme.txt");
//变换为Reader
Reader reader = new InputStreamReader(input,"UTF-8");
```

## Writer

`Reader`是带编码转换器的`InputStream`，它把`byte`转换为`char`，而`Writer`就是带编码转换器的`OutputStream`，它把`char`转换为`byte`并输出。

| OutputStream                           | Writer                                   |
| :------------------------------------- | :--------------------------------------- |
| 字节流，以`byte`为单位                 | 字符流，以`char`为单位                   |
| 写入字节（0~255）：`void write(int b)` | 写入字符（0~65535）：`void write(int c)` |
| 写入字节数组：`void write(byte[] b)`   | 写入字符数组：`void write(char[] c)`     |
| 无对应方法                             | 写入String：`void write(String s)`       |

### FileWriter

```java
try(Writer writer = new FileWriter("readme.txt",StandardCharsets.UTF_8)){
  writer.write('H');//写入单个字符
  writer.write("Hello".toCharArray());//写入char[]
  writer.write("Hello");//写入String
}
```

### OutputStreamWriter

除了`CharArrayWriter`和`StringWriter`外，普通的Writer实际上是基于`OutputStream`构造的，它接收`char`，然后在内部自动转换成一个或多个`byte`，并写入`OutputStream`。因此，`OutputStreamWriter`就是一个将任意的`OutputStream`转换为`Writer`的转换器：

```java
try (Writer writer = new OutputStreamWriter(new FileOutputStream("readme.txt"), "UTF-8")) {
    // TODO:
}
```

## PrintStream和PrintWriter

### PrintStream

`PrintStream`是一种`FilterOutputStream`，它在`OutputStream`的接口上，额外提供了一些写入各种数据类型的方法：

- 写入`int`：`print(int)`
- 写入`boolean`：`print(boolean)`
- 写入`String`：`print(String)`
- 写入`Object`：`print(Object)`，实际上相当于`print(object.toString())`
- ...

以及对应的一组`println()`方法，它会自动加上换行符。

我们经常使用的`System.out.println()`实际上就是使用`PrintStream`打印各种数据。

`System.err`是系统默认提供的标准错误输出。

`PrintStream`和`OutputStream`相比，除了添加了一组`print()`/`println()`方法，可以打印各种数据类型，比较方便外，它还有一个额外的优点，就是不会抛出`IOException`，这样我们在编写代码的时候，就不必捕获`IOException`。

### PrintWriter

`PrintStream`最终输出的总是byte数据，而`PrintWriter`则是扩展了`Writer`接口，它的`print()`/`println()`方法最终输出的是`char`数据。

## 使用Files

虽然`Files`是`java.nio`包里面的类，但他俩封装了很多读写文件的简单方法，例如，我们要把一个文件的全部内容读取为一个`byte[]`，可以这么写：

```java
byte[] data = Files.readAllBytes(Path.of("/path/to/file.txt"));
```

如果是文本文件，可以把一个文件的全部内容读取为`String`：

```
// 默认使用UTF-8编码读取:
String content1 = Files.readString(Path.of("/path/to/file.txt"));
// 可指定编码:
String content2 = Files.readString(Path.of("/path", "to", "file.txt"), StandardCharsets.ISO_8859_1);
// 按行读取并返回每行内容:
List<String> lines = Files.readAllLines(Path.of("/path/to/file.txt"));
```

写入文件也非常方便：

```java
// 写入二进制文件:
byte[] data = ...
Files.write(Path.of("/path/to/file.txt"), data);
// 写入文本并指定编码:
Files.writeString(Path.of("/path/to/file.txt"), "文本内容...", StandardCharsets.ISO_8859_1);
// 按行写入文本:
List<String> lines = ...
Files.write(Path.of("/path/to/file.txt"), lines);
```

此外，`Files`工具类还有`copy()`、`delete()`、`exists()`、`move()`等快捷方法操作文件和目录。

最后需要特别注意的是，`Files`提供的读写方法，受内存限制，只能读写小文件，例如配置文件等，不可一次读入几个G的大文件。读写大型文件仍然要使用文件流，每次只读写一部分文件内容。

