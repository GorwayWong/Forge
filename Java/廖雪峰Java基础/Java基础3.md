# 泛型

## 什么是泛型

泛型就是编写模板代码来适应任意类型.

泛型的好处是使用时不必对类型进行强制转换，它通过编译器对类型进行检查；

注意泛型的继承关系：可以把`ArrayList<Integer>`向上转型为`List<Integer>`（`T`不能变！），但不能把`ArrayList<Integer>`向上转型为`ArrayList<Number>`（`T`不能变成父类）。

## 使用泛型

使用`ArrayList`时，如果不定义泛型类型时，泛型类型实际上就是`Object`

编译器如果能自动推断出泛型类型，就可以省略后面的泛型类型。

```java
List<Number> list = new ArrayList<Number>();
//可以简写为
List<Number> list = new ArrayList<>();
```

#### 泛型接口

除了`ArrayList<T>`使用了泛型，还可以在接口中使用泛型。例如，`Arrays.sort(Object[])`可以对任意数组进行排序，但待排序的元素必须实现`Comparable<T>`这个泛型接口：

```java
import java.util.Arrays;

public class Main{
  public static void main(String[] args){
    Person[] ps = new Person[]{
      new Person("Bob",61);
      new Person("Alice",88);
      new Person("Lily",75);
    };
    Arrays.sort(ps);
    System.out.println(Arrays.toString(ps));
  }
}

class Person implements Comparale<Person> {
  String name;
  int score;
  Person(String name, int score){
    this.name = name;
    this.score = score;
  }
  public int compareTo(Person other){
    return this.name.compareTo(other.name);
  }
  public String toString(){
    return this.name + "," + this.score;
  }
}
```

## 编写泛型

编写泛型类比普通类要复杂。通常来说，泛型类一般用在集合类中，例如`ArrayList<T>`，我们很少需要编写泛型类。

#### 静态方法

编写泛型类时,要特别注意，泛型类型`<T>`不能用于静态方法。

对于静态方法，我们可以单独改写为“泛型”方法，只需要使用另一个类型即可。

```java
public class Pair<T>{
  private T first;
  private T last;
  public Pair(T first,T last){
    this.first = first;
    this.last = last;
  }
  public T getFirst(){...}
  public T getLast(){...}
  
  //静态泛型方法应该使用其他类型区分:
  public static <K> Pair<K> create(K first, K last){
    return new Pair<K>(first,last);
  }
}
```

这样才能清楚地将静态方法的泛型类型和实例类型的泛型类型区分开。

- 泛型类型是在实例化对象时确定的，而静态方法是在类加载时就可以直接调用的，无需创建对象实例。所以静态方法中的返回值、参数等不能依赖泛型类型\<T>，必须将静态方法的泛型类型和实例类型的泛型类型区分开。
- 此外，静态方法是与类本身相关联的，而不是与类的实例相关联的。因此，即使创建了一个类的实例，静态方法也无法访问实例的泛型类型。

#### 多个泛型类型

泛型还可以定义多种类型。例如，我们希望`Pair`不总是存储两个类型一样的对象，就可以使用类型`<T, K>`：

```java
public class Pair<T,K> {
  private T first;
  private K last;
  public Pair(T first,K last){
    this.first = first;
    this.last = last;
  }
  public T getFirst(){...}
  public K getLast(){...}
}
```

## 擦拭法

Java语言的泛型实现方式是擦拭法（Type Erasure）。

所谓擦拭法是指，虚拟机对泛型其实一无所知，所有的工作都是编译器做的。

ava的泛型是由编译器在编译时实行的，编译器内部永远把所有类型`T`视为`Object`处理，但是，在需要转型的时候，编译器会根据`T`的类型自动为我们实行安全地强制转型。

局限一：`<T>`不能是基本类型，例如`int`，因为实际类型是`Object`，`Object`类型无法持有基本类型：

```java
Pair<int> p = new Pair<>(1, 2); // compile error!
```

局限二：无法取得带泛型的`Class`。

因为`T`是`Object`，我们对`Pair<String>`和`Pair<Integer>`类型获取`Class`时，获取到的是同一个`Class`，也就是`Pair`类的`Class`。

换句话说，所有泛型实例，无论`T`的类型是什么，`getClass()`返回同一个`Class`实例，因为编译后它们全部都是`Pair<Object>`。

局限三：无法判断带泛型的类型：

```java
Pair<Integer> p = new Pair<>(123, 456);
// Compile error:
if (p instanceof Pair<String>) {
}
```

原因和前面一样，并不存在`Pair<String>.class`，而是只有唯一的`Pair.class`。

局限四：不能实例化`T`类型：

```java
public class Pair<T> {
    private T first;
    private T last;
    public Pair() {
        // Compile error:
        first = new T();
        last = new T();
    }
}
```

要实例化`T`类型，我们必须借助额外的`Class<T>`参数：

```java
public class Pair<T>{
  private T first;
  private T last;
  public Pair(Class<T> clazz){
    first = clazz.newInstance();
    last = clazz.newInstance();
  }
}
```

上述代码借助`Class<T>`参数并通过反射来实例化`T`类型，使用的时候，也必须传入`Class<T>`。

```java
Pair<String> pair = new Pair<>(String.class);
```

#### 不恰当的覆写方法

有些时候，一个看似正确定义的方法会无法通过编译。例如：

```java
public class Pair<T> {
    public boolean equals(T t) {
        return this == t;
    }
}
```

这是因为，定义的`equals(T t)`方法实际上会被擦拭成`equals(Object t)`，而这个方法是继承自`Object`的，编译器会阻止一个实际上会变成覆写的泛型方法定义。

换个方法名，避开与`Object.equals(Object)`的冲突就可以成功编译：

```java
public class Pair<T> {
    public boolean same(T t) {
        return this == t;
    }
}
```

#### 泛型继承

一个类可以继承自一个泛型类.

```java
public class IntPair extends Pair<Integer> {
}
```

前面讲了，我们无法获取`Pair<T>`的`T`类型，即给定一个变量`Pair<Integer> p`，无法从`p`中获取到`Integer`类型。

但是，在父类是泛型类型的情况下，编译器就必须把类型`T`（对`IntPair`来说，也就是`Integer`类型）保存到子类的class文件中，不然编译器就不知道`IntPair`只能存取`Integer`这种类型。

在继承了泛型类型的情况下，子类可以获取父类的泛型类型。例如：`IntPair`可以获取到父类的泛型类型`Integer`。获取父类的泛型类型代码比较复杂：

## extends通配符

用`Pair<? extends Number>`使得方法接收所有泛型类型为`Number`或`Number`子类的`Pair`类型。

```java
public class Main{
  public static void main(String[] args){
    Pair<Integer> p = new Pair<>(123,456);
    int n = add(p);
    System.out.println(n);
  }
  static int add(Pair<? extends Number> p){
    Number first = p.getFirst();
    Number last = p.getLast();
    p.setFirst(new Integer(first.intValue() + 100));
    p.setLast(new Integer(last.intValue() + 100));
    return p.getFirst().intValue() + p.getLast().intValue();
  }
}
class Pair<T> {
  private T first;
  private T last;
  public Pair(T first,T last){
    this.first = first;
    this.last = last;
  }
  public T getFirst(){
    return first;
  }
  public T getLast(){
    return last;
  }
  public void setFirst(T first){
    this.first = first;
  }
  public void setLast(T last){
    this.last = last;
  }
}
```

这样一来，给方法传入`Pair<Integer>`类型时，它符合参数`Pair<? extends Number>`类型。这种使用`<? extends Number>`的泛型定义称之为上界通配符（Upper Bounds Wildcards），即把泛型类型`T`的上界限定在`Number`了。

如果我们考察对`Pair<? extends Number>`类型调用`getFirst()`方法，实际的方法签名变成了：

```java
<? extends Number> getFirst();
```

即返回值是`Number`或`Number`的子类，因此，可以安全赋值给`Number`类型的变量：

```java
Number x = p.getFirst();
```

然后，我们不可预测实际类型就是`Integer`，例如，下面的代码是无法通过编译的：

```java
Integer x = p.getFirst();
```

这是因为实际的返回类型可能是`Integer`，也可能是`Double`或者其他类型，编译器只能确定类型一定是`Number`的子类（包括`Number`类型本身），但具体类型无法确定。

#### 使用extends限定T类型

在定义泛型类型`Pair<T>`的时候，也可以使用`extends`通配符来限定`T`的类型：

```java
public class Pair<T extends Number> { ... }
```

现在，我们只能定义：

```java
Pair<Number> p1 = null;
Pair<Integer> p2 = new Pair<>(1, 2);
Pair<Double> p3 = null;
```

#### 小结

使用类似`<? extends Number>`通配符作为方法参数时表示：

- 方法内部可以调用获取`Number`引用的方法，例如：`Number n = obj.getFirst();`；
- 方法内部无法调用传入`Number`引用的方法（`null`除外），例如：`obj.setFirst(Number n);`。

即一句话总结：使用`extends`通配符表示可以读，不能写。

使用类似`<T extends Number>`定义泛型类时表示：

- 泛型类型限定为`Number`以及`Number`的子类。

## super通配符

考察下面的`set`方法：

```java
void set(Pair<Integer> p, Integer first, Integer last) {
    p.setFirst(first);
    p.setLast(last);
}
```

传入`Pair<Integer>`是允许的，但是传入`Pair<Number>`是不允许的。

和`extends`通配符相反，这次，我们希望接受`Pair<Integer>`类型，以及`Pair<Number>`、`Pair<Object>`，因为`Number`和`Object`是`Integer`的父类，`setFirst(Number)`和`setFirst(Object)`实际上允许接受`Integer`类型。

我们使用`super`通配符来改写这个方法：

```java
void set(Pair<? super Integer> p, Integer first, Integer last) {
    p.setFirst(first);
    p.setLast(last);
}
```

注意到`Pair<? super Integer>`表示，方法参数接受所有泛型类型为`Integer`或`Integer`父类的`Pair`类型。

因此，使用`<? super Integer>`通配符表示：

- 允许调用`set(? super Integer)`方法传入`Integer`的引用；
- 不允许调用`get()`方法获得`Integer`的引用。

唯一例外是可以获取`Object`的引用：`Object o = p.getFirst()`。

换句话说，使用`<? super Integer>`通配符作为方法参数，表示方法内部代码对于参数只能写，不能读。

### 对比extends和super通配符

我们再回顾一下`extends`通配符。作为方法参数，`<? extends T>`类型和`<? super T>`类型的区别在于：

- `<? extends T>`允许调用读方法`T get()`获取`T`的引用，但不允许调用写方法`set(T)`传入`T`的引用（传入`null`除外）；
- `<? super T>`允许调用写方法`set(T)`传入`T`的引用，但不允许调用读方法`T get()`获取`T`的引用（获取`Object`除外）。

一个是允许读不允许写，另一个是允许写不允许读。

### PECS原则

何时使用`extends`，何时使用`super`？为了便于记忆，我们可以用PECS原则：Producer Extends Consumer Super。

即：如果需要返回`T`，它是生产者（Producer），要使用`extends`通配符；如果需要写入`T`，它是消费者（Consumer），要使用`super`通配符。

还是以`Collections`的`copy()`方法为例：

### 无限定通配符

我们已经讨论了`<? extends T>`和`<? super T>`作为方法参数的作用。实际上，Java的泛型还允许使用无限定通配符（Unbounded Wildcard Type），即只定义一个`?`：

```java
void sample(Pair<?> p) {
}
```

因为`<?>`通配符既没有`extends`，也没有`super`，因此：

- 不允许调用`set(T)`方法并传入引用（`null`除外）；
- 不允许调用`T get()`方法并获取`T`引用（只能获取`Object`引用）。

换句话说，既不能读，也不能写，那只能做一些`null`判断：

```java
static boolean isNull(Pair<?> p) {
    return p.getFirst() == null || p.getLast() == null;
}
```

大多数情况下，可以引入泛型参数`<T>`消除`<?>`通配符：

```java
static <T> boolean isNull(Pair<T> p) {//static后面的<T>是为了告诉编译器这是一个泛型方法,并且在这个方法中引入了泛型参数T
    return p.getFirst() == null || p.getLast() == null;
}
```

无限定通配符`<?>`很少使用，可以用`<T>`替换，同时它是所有`<T>`类型的超类。

## 泛型和反射(不太懂)

Java的部分反射API也是泛型。例如：`Class<T>`就是泛型：

```java
// compile warning:
Class clazz = String.class;
String str = (String) clazz.newInstance();

// no warning:
Class<String> clazz = String.class;
String str = clazz.newInstance();
```

调用`Class`的`getSuperclass()`方法返回的`Class`类型是`Class<? super T>`：

```java
Class<? super String> sup = String.class.getSuperclass();
```

我们可以声明带泛型的数组，但不能用`new`操作符创建带泛型的数组：

```java
Pair<String>[] ps = null; // ok
Pair<String>[] ps = new Pair<String>[2]; // compile error!
```

必须通过强制转型实现带泛型的数组：

```java
@SuppressWarnings("unchecked")
Pair<String>[] ps = (Pair<String>[]) new Pair[2];
```

使用泛型数组要特别小心，因为数组实际上在运行期没有泛型，编译器可以强制检查变量`ps`，因为它的类型是泛型数组。但是，编译器不会检查变量`arr`，因为它不是泛型数组。因为这两个变量实际上指向同一个数组，所以，操作`arr`可能导致从`ps`获取元素时报错，例如，以下代码演示了不安全地使用带泛型的数组：

```java
Pair[] arr = new Pair[2];
Pair<String>[] ps = (Pair<String>[]) arr;

ps[0] = new Pair<String>("a", "b");
arr[1] = new Pair<Integer>(1, 2);

// ClassCastException:
Pair<String> p = ps[1];
String s = p.getFirst();
```

要安全地使用泛型数组，必须扔掉`arr`的引用：

```java
@SuppressWarnings("unchecked")
Pair<String>[] ps = (Pair<String>[]) new Pair[2];
```

上面的代码中，由于拿不到原始数组的引用，就只能对泛型数组`ps`进行操作，这种操作就是安全的。

带泛型的数组实际上是编译器的类型擦除：

```java
Pair[] arr = new Pair[2];
Pair<String>[] ps = (Pair<String>[]) arr;

System.out.println(ps.getClass() == Pair[].class); // true

String s1 = (String) arr[0].getFirst();
String s2 = ps[0].getFirst();
```

所以我们不能直接创建泛型数组`T[]`，因为擦拭后代码变为`Object[]`：

```java
// compile error:
public class Abc<T> {
    T[] createArray() {
        return new T[5];
    }
}
```

必须借助`Class<T>`来创建泛型数组：

```java
T[] createArray(Class<T> cls) {
    return (T[]) Array.newInstance(cls, 5);
}
```

我们还可以利用可变参数创建泛型数组`T[]`：

```java
public class ArrayHelper {
    @SafeVarargs
    static <T> T[] asArray(T... objs) {
        return objs;
    }
}

String[] ss = ArrayHelper.asArray("a", "b", "c");
Integer[] ns = ArrayHelper.asArray(1, 2, 3);
```