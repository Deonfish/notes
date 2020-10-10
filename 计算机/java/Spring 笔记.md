# Spring 笔记

#### `label+th:field`

```html
<label for="name">Name: </label>
<input type="text" th:field="*{name}"/>
```

后部元素不需要加 `id`

### spring boot 日志

| 配置(properties)          | 简介                                             |
| ------------------------- | ------------------------------------------------ |
| `logging.level`           |                                                  |
| `logging.file`            | 生成日志文件（可以指定路径）                     |
| `logging.path`            | 生成日志文件的目录，使用`spring.log`作为默认名称 |
| `logging.pattern.console` | 控制台日志格式                                   |
| `loging.pattern.file`     | 日志文件日志格式                                 |



#### 从前端获取值

##### url参数 -> javaBean

```java
// 请求ULR: http://localhost:8080/test?name=xxx&pwd=yyy
@RequestMapping("test")
public String test(User user) { // 自动调用setter
  return user.getName() + "" + user.getPwd();
}
```

##### url参数

```java
// 请求ULR: http://localhost:8080/test?name=xxx&pwd=yyy
@RequestMapping("test")
public String test(String name, String pwd) {
  return name + "" + pwd;
}
```

##### 路径参数(PathVariable)

```java
// 请求ULR: http://localhost:8080/test/xxx/yyy
@RequestMapping("test/{name}/{pwd}")
public String test(@PathVariable("name") String name,
                   @PathVariable("pwd") String pwd) {
  return name + "" + pwd;
}
```

##### 表单传值

收集所有表单值，以参数形式返回，`@PostMapping`自动调用pojo对象对应属性的setter

```java
@PostMapping
	public String test(User user) {
    return user;
  }
```

```html
  <form method="POST" th:action="@{/register}">

    <!--返回的参数名为name属性的名字-->
		Username: <input type="text" name="username"/><br/>
    Password: <input type="password" name="password"/><br/>
    <input type="submit" value="Register"/>
    
  </form>
```



#### lombook

##### @Data

注解在类上，相当于同时使用了`@ToString`、`@EqualsAndHashCode`、`@Getter`、`@Setter`和`@RequiredArgsConstrutor`这些注解

##### @RequiredArgsConstructor

生成构造方法，参数是未初始化的`final`对象或`@NonNull`注解的属性



#### get&post参数传递方法

##### get

参数拼接在链接后，如`localhost:8080/xxx?name=a&pwd=www`

##### post

参数封装在报文体中，链接后无参数

![image-20200805115645705](/Users/guosongnan/Library/Application Support/typora-user-images/image-20200805115645705.png)	

