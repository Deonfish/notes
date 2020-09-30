# java学习笔记

### 一些概念

`JDK`：java开发者套件，用来开发java的环境，包含java SE、java虚拟机和一些java开发工具（编译器javac，打包jar工具等）。

`JRE`：java运行套件，用来运行java的最小环境，包含java SE和java虚拟机。

`java SE`：标准java版本，包含了必须的java库和api (java.lang, java.io,java.util, etc...)。

`java EE`：企业java版本，包含了java SE，额外的库和api (JDBC, JPA, servlet, etc... )。

`openJDK · OracleJDK`：二者几乎相等，下载的是oracleJDK，机器内置openJDK

### 参数传递

1. 传基本类型和String类型是传值（复制品）
2. 传类类型是传引用的值（引用的复制）

### final

1. 修饰类
   表示类不会被继承，final类中的方法自动为final方法。

2. 修饰方法
   防止任何子类覆盖其方法。

3. 修饰引用

   若修饰基本类型变量或 String ，则数值一旦确定以后不能更改（类似c++const），该变量会变成一个常量。
   若修饰引用类型，则变量初始化以后不可以指向另一个对象，但对象本身可能改变。

   ```java
   final StringBuffer s = new StringBuffer("hello");
   s.append(" world!"); // 可以改变对象
   s = new StringBuffer("new hello"); // 不可以指向另一个对象
   ```

   final修饰参数：
   若参数为基本类型，则方法中的参数为原参数的拷贝，final修饰可以使该拷贝值不变。
   若参数为引用类型，方法中的参数为引用的拷贝，final可以使其引用不指向其他对象。

### 接口

接口中的非默认方法在类中必须实现，默认方法可以不实现也可以覆盖

实现接口的接口不必要重写其方法（但最好重写）

### 继承

子类中和父类名字相同、参数不同的方法定义为重载而不是覆盖

#### 构造器

若子类构造器没有显示调用超类构造器（`super()`），则自动调用超类默认构造器，若超类没有不带参数构造器则报错。

所以经常在超类中写一个默认构造器（抽象超类也写）以避免隐式调用时报错

#### 方法调用

```java
class parent {
  void prt(int x){}
  void func(){}
}
class child extends parent {
  void prt(String s){}
  void func(){}
}
```

```java
parent x = new child();
x.prt(...);  // 调用父类中定义的prt
x.func(...); // 调用子类中覆盖父类的func(在父类中有签名)
```

匹配时只寻找在`parent`中出现的方法，即`prt(int x)，func()`

#### 桥方法

```java
class parent<T>{
	void ptr(T x){}
}
class child extends parent<String> {
  void ptr(String s){}
}
parent<String> x = new child<>();
x.ptr("sss");
```

- 调用`x.ptr("sss")`期待的行为：

`parent`泛化为

```java
class parent{
void ptr(String x){}
}
```

改调用调用重载后的`child`中的`ptr(String)`

- 实际行为：

`parent`擦除为

```java
class parent{
void ptr(Object x){}
}
```

与`child`中的`ptr函数`并列重载（没有继承），会调用`parent`中的`ptr(Object)`

**所以引入桥函数以实现正确的多态**

`ptr`方法翻译为`桥函数`

```java
class parent{
	void ptr(Object x){
		ptr((String) x);
	}
}
```

### 内部类

每个外部类对象拥有一个内部类对象

```java
public class InnerClass{
        public OuterClass getOuterClass(){
            return OuterClass.this;
        }
    }

OuterClass.InnerClass innerClass = outerClass.new InnerClass();
```

内部类作用域内用`outer.this`创建外部引用

非内部类作用域，内部类类型：`outer.inner`，创建内部类对象：`outer.new`

#### 内部类的继承

父类的内部类会继承到子类中

### 泛型

> 小技巧：java泛型努力地想要工作地像c++：真正的生成对应类型的代码而不是退化类型

泛型对象不可以直接实例化

```java
public class S<E> {
	public E data1   = new E();		 // 错误！
  public E[] data2 = new E[100]; // 错误！
  public E data3	 = (E) new Object(); // 也是错误！
}
```

eg. `ArrayList类`把数组声明为Object数组以避免此类错误

```java
transient Object[] elementData;
```

### 异常

#### 异常执行顺序

碰到异常停止往下执行，自底向上寻找合适的catch字段，若无匹配的catch字段程序结束，若匹配到catch字段则执行catch字段及之后的代码（底层掠过的代码都得不到执行）

#### 异常处理

若直接`throw`出去，碰到异常时会中断并调用`e.printStackTrace()`

若`try catch`，碰到异常时会执行`catch`后继续往下执行

### 序列化

把对象转换为字节序列（二进制序列）的过程称为对象的序列化。
把字节序列恢复为对象的过程称为对象的反序列化。

#### 使用场景

- 对象的持久化（将对象内容保存到数据库或文件中）
- 远程数据传输（将对象发送给其他计算机系统）

对于数据的本地持久化，只需要将数据转换为字符串进行保存即可是实现（如把对象转换为jason格式存储到本地数据库），但对于远程的数据传输，由于操作系统，硬件等差异，会出现内存大小端，内存对齐等问题，导致接收端无法正确解析数据，所以要序列化为两端都可以识别的字节码，在另一端再反序列化。

只有实现了Serializable和Externalizable接口的类的对象才能被序列化。Externalizable接口继承自 Serializable接口，实现Externalizable接口的类完全由自身来控制序列化的行为，而仅实现Serializable接口的类可以 采用默认的序列化方式 。

```java
public class Person implements Serializable {
  private String name;
  private String sex;
  Person(String _name, String _sex) {
    name = _name; sex = _sex;
  }
}
```

java.io.ObjectOutputStream代表对象输出流，它的writeObject(Object obj)方法可对参数指定的obj对象进行序列化，把得到的字节序列写到一个目标输出流中。
java.io.ObjectInputStream代表对象输入流，它的readObject()方法从一个源输入流中读取字节序列，再把它们反序列化为一个对象，并将其返回。

```java
Person p = new Person("xiaoming", "male");

ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream(new File("~/Person.txt"))); // 创建输出流
oo.writeObject(p); // 序列化

ObjectInputStream ois = new ObjectInputStream(new FileInputStream(new File("~/Person.txt"))); // 创建输出流
Person p = (Person)ois.readObject(); // 反序列化
```

此代码生成的Person.txt文件是一个二进制流文件


