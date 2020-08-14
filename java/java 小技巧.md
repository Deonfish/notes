# java 小技巧

#### equals

```java
Object o = null;
Object b = new Integer(2);
System.out.println(o.equals(b));
```

当对象为null时无法调用equals函数

null对象没有方法/域，只能调用静态域/方法

#### 内部类

一个内部类不可以引用另一个`private`内部类

#### jvm内存管理

```java
d1 = d2;   // 此处原d1指向的对象被回收
d1 = null; // d1的对象被回收
```

