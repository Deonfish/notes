# java 反射

### Class

获取Class: 

```java
Class cl1 = String.class; // 静态
Class cl2 = s.getClass(); // 对象
Class cl3 = Class.forName("java.lang.String") // 全局静态函数
// 若类不存在则抛出异常
```

| 方法                                                         | 说明                                                         |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| String getName()                                             | 获取类名                                                     |
| static Class<?> forName(String class)                        | 静态，获取Class对象                                          |
| String modis = Modifier.toString(cl.getModifiers())          | 返回修饰符                                                   |
| getFields( ) \| getMethods( ) \| getConstructors( )          | 返回public成员，包含超类成员                                 |
| getDeclaredFields( ) \| getDeclareMethods( ) \| getDeclaredConstructors( ) | 返回全部成员，不包含超类成员                                 |
| Constructor<T\> getConstructor(Class\<?>... paramTypes)<br>Constructor<T\> getDeclaredConstructor(Class<?>... paramTypes) | 返回一个public构造器<br>返回一个构造器<br>(Method和Field均类似) |
| ClassLoader getClassLoader( )                                | 返回类加载器                                                 |
| T newInstance( )                                             | 用无参数构造器创造实例                                       |

### Field

| 方法                               | 说明                        |
| ---------------------------------- | --------------------------- |
| String getName( )                  | 获取域名                    |
| Class getType( )                   | 获取域的类型                |
| int getModifiers( )                | 获取修饰符                  |
| Object get(Object obj)             | 返回obj对象对应的域对象的值 |
| void set(Object obj, Object value) | 设置obj对象对应域对象的值   |
|                                    |                             |
|                                    |                             |

### Method

| 方法                                      | 说明                                            |
| ----------------------------------------- | ----------------------------------------------- |
| String getName( )                         | 获取函数名称                                    |
| Class getReturnType( )                    | 获取返回值类型                                  |
| Class[] getParameterTypes( )              | 获取参数类型                                    |
| int getModifiers( )                       | 获取修饰符                                      |
| Object invoke(Object obj, Object... args) | 调用obj对象对应方法，<br>静态方法第一参数位null |
|                                           |                                                 |
|                                           |                                                 |

### Constructor

| 方法                              | 说明                       |
| --------------------------------- | -------------------------- |
| T newInstance(Object... initargs) | 使用该构造函数创建新的实例 |
|                                   |                            |
|                                   |                            |

