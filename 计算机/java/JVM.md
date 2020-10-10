# JVM

## 运行时类结构 & 数据初始化时机

### 运行时类数据结构（逻辑结构）

- 静态类数据（方法区mostly）：

类的所有方法（静态/非静态，包括自动生成的`<init>``<clinit>`）都存储在方法区，而继承来的父类的方法存在父类的方法区区域中。类的static字段（常量非常量）存放于堆中（逻辑上在方法区，也可认为在方法区存放），从父类继承来的static字段在父类的堆中。

<img src="/Users/guosongnan/Desktop/working/notes/pic/静态数据.png" alt="静态数据" style="zoom:50%;" />

- 实例对象数据（堆）：

首先是对象头。

对象的特有字段（对象的新字段和与父类字段同名的字段）存储在堆上。
父类的字段（继承的字段）单独于子类存储于堆上。

<img src="/Users/guosongnan/Desktop/working/notes/pic/实例数据.png" alt="实例数据" style="zoom:50%;" />

### 数据初始化时机

- 静态类数据：

类加载的加载阶段装入所有方法。在类加载的准备阶段，为类的静态变量分配空间并赋0值（常量赋其给定的初始值）。在类加载的初始化阶段，执行`<clinit>`类构造函数，为所有static字段赋设置值并执行static代码块，若父类未加载，则先加载父类，初始化父类的static字段并执行父类的static代码块。

- 实例对象数据：

初始化实例对象的过程即JVM new 指令的执行过程。

先同时为父类实例和子类实例分配空间，初始化为0值。为父类字段赋设置的初始值，执行父类的实例构造函数（若父类无该构造函数则报错）。为子类字段赋设置的初始值，执行子类的实例构造函数。所有数据存在堆中，构造函数返回一个该类型引用，引用分配在栈上。

【注】java寻找字段是根据类的静态类型，确定重载是根据参数静态类型，寻找方法是根据实际类型。

## 编译

#### CLASS文件

### 例1

```java
public class A {
    private int a;
    static private int sa;
    static {
        System.out.println("static block");
    }

    public void func() {
        System.out.println("in func");
    }

}
```

```java
public class Main {
    public static void main(String[] args) {
        A a = new A();
    }
}
```

编译Main.java文件的同时会编译与之关联的A.java文件

##### 类 A

字段表

```
struct field_info fields[0]
	u2 access_flags 2 					# private
	u2 name_index 25  					# a
	u2 descriptor_index 26 		 	# I
struct field_info fields[1]
	u2 access_flags 10 					# private static
	u2 name_index 27 						# sa
	u2 descriptor_index 26 			# I
```

方法表

```
struct method_info methods[0]
	u2 access_flags 1 									# public
	u2 name_index 5 										# <init>
	u2 descriptor_index 6 							# ()V
	struct attribute_info attributes
		u2 attribute_name_index 28 				# Code
		u2 max_stack 1
		u2 max_locals 1
		struct code
			2A															# aload_0
			B7 00 01 												# invokespecial java/lang/Object.<init>()V
			B1															# Return
		struct attribute_info attributes
			u2 attribute_name_index 29 			# LineNumberTable
			struct line_number_table
----------------------------------------------------------------
struct method_info methods[1]
	u2 access_flags 1 									# public
	u2 name_index 30 										# func
	u2 descriptor_index 6 							# ()V
	struct attribute_info attributes
		u2 attribute_name_index 28 				# Code
		u2 max_stack 2
		u2 max_locals 1
		struct code
			B2 00 07 												# getstatic java/lang/System.outLjava/io/PrintStream;
			12 0D 													# ldc in func
			B6 00 0F 												# invokevirtual java/io/PrintStream.println(Ljava/lang/String;)V
			B1 															# Return
		struct attribute_info attributes
			u2 attribute_name_index 29 			# LineNumberTable
			...
----------------------------------------------------------------
struct method_info methods[2]
	u2 access_flags 8  #  static
	u2 name_index 31 # <clinit>
	u2 descriptor_index 6 # ()V
	struct attribute_info attributes
		u2 attribute_name_index 28 # Code
		u2 max_stack 2
		u2 max_locals 0
		struct code
			B2 00 07 # getstatic java/lang/System.outLjava/io/PrintStream;
			12 15 # ldc static block
			B6 99 9F	# invokevirtual java/io/PrintStream.println(Ljava/lang/String;)V
			B1 # Return
		struct attribute_info attributes
			u2 attribute_name_index 29 # # LineNumberTable
			...

```

##### 问题

1. 常量池中第0号常量是什么，CONSTANT_Fieldref、CONSTANT_Methodref等是什么
   符号引用，在指令中出现，在解析阶段解析为地址。
2. java动态连接
   在加载Class文件的解析阶段解析符号引用以连接不同的类文件。
3. 异常表、Exception属性
   java中没有异常跳转指令，异常跳转位置存储在Code属性的异常表中
   Exception属性是与Code属性同级的属性 (隶属于某个方法表 )，列出方法可能抛出的属性

### 例2

```java
public class Supper {
    public int fi = 1;
    
    public void func1() {
        System.out.println("supper func1");
    }
    public void func2() {
        System.out.println("supper func2");
    }
}
```

```java
public class Son extends Supper {
    public void func2() {
        System.out.println("son func2");
    }
    public void sonFunc() {
        System.out.println("son addition func");
    }
    
}
```

```java
public class Main {
    public static void main(String[] args) {
        Supper son = new Son();
        son.func1();
        son.func2();
    }
}
```

字段表

```
# Supper.class

struct field_info fields
	...
```

son.class 中无字段。因为子类CLASS文件中不会包含从父类继承来的数据。

方法表

```
# Supper.class

struct method_info methods[0]		# <init>()V
struct method_info methods[1] 	# func1()V
struct method_info methods[2] 	# func2()V
```

```
# son.class

struct method_info methods[0]		# <init>()V
struct method_info methods[1] 	# func2()V
struct method_info methods[2]		# sonFunc()V
```

son.class 中无`func1()V`，同上，子类CLASS文件中不会包含从父类继承来的数据。

```
# Main.class main方法 Code属性

new Son
dup
invokespecial Son.<init>()V
astore_1
aload_1
invokevirtual Supper.func1()V
aload_1
invokevirtual Supper.func2()V
Return
```

问题：

1. java静态内部类？

## java虚拟机

虚拟机运行 Main 的过程：

类加载 ( class loading )

1. 加载
   - 根据类的全限定名称获取 Main.class文件。
   - 把Main.class文件装入**方法区**。
   - 在**堆**中生成一个代表这个类的 java.lang.Class对象。
2. 验证
3. 准备
   在**堆**上为 Main的静态字段分配空间，赋0值（静态常量为设置的初始值）。
4. 解析
   把`CONSTANT_Class_Info`, `CONSTANT_Fieldref_info`, `CONSTANT_Methodref_info`等符号引用解析为地址，若遇到未加载的类则加载该类。
5. 初始化
   执行类构造器`<clinit>`。为所有静态字段赋值，执行静态代码块。

执行 ( running )

把PC设置为Main类的main方法的第一行，开始执行代码。

遇到需要初始化的类可能执行类加载。

