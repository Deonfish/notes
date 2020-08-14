# java学习笔记

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

