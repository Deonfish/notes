# Jdbc 笔记

## JDBC

jdbc是sun公司定义的一些接口，依靠jdbc可以连接数据库并执行sql语句，需要各个厂商自行实现，如mysql实现的jdbc

```xml
<dependency>
    <groupId>mysql</groupId>
    <artifactId>mysql-connector-java</artifactId>
    <version>5.1.47</version>
    <scope>runtime</scope>
</dependency>
```

#### 获取连接

`DriverManager`会自动扫描classpath，找到所有的JDBC驱动，然后根据我们传入的URL自动挑选一个合适的驱动。

因为JDBC连接是一种昂贵的资源，所以使用后要及时调用`close()`释放。使用`try (resource)`来自动释放JDBC连接是一个好方法

```java
// JDBC连接的URL, 不同数据库有不同的格式:
String JDBC_URL = "jdbc:mysql://localhost:3306/test";
String JDBC_USER = "root";
String JDBC_PASSWORD = "password";
// 获取连接:
try (Connection conn = DriverManager.getConnection(JDBC_URL, JDBC_USER, JDBC_PASSWORD)) {
    ...
}
```

#### 获取状态

`PreparedStatement`对象用于执行sql语句改变数据库状态，`PreparedStatement`与具体sql对象绑定，防止sql注入

```java
try (PreparedStatement ps = conn
					.prepareStatement("SELECT * FROM students WHERE grade = ? AND score >= ?")) {
				ps.setInt(1, 3); 
				ps.setInt(2, 90); 
  ...
}
```

#### 获取执行结果

`ResultSet`保存执行结果，通过`next()`不断获取下一个实体对象（查询语句）

```java
try (ResultSet rs = ps.executeQuery()) {
  while (rs.next()) {
    var std = new Student();
		std.setId(rs.getLong("id"));
		std.setName(rs.getString("name"));
		std.setGender(rs.getBoolean("gender"));
		std.setGrade(rs.getInt("grade"));
		std.setScore(rs.getInt("score"));
    
    System.out.println(std);
  }
}
```

### 事务

#### 隔离级别

| 隔离级别       | 含义                                                         |
| -------------- | ------------------------------------------------------------ |
| 读未提交(不用) | 可以读到未提交的数据，相当于每句都自动提交，不存在事务       |
| 读提交         | 只可以读到update事务提交后的数据，即执行update事务时不允许读 |
| 可重复读       | 读事务中见不可插入update事务，读事务中读到的数据全部一致，但可插入insert/delete |
| 串形化(不用)   | 读的时候不允许所有写操作，写的时候不允许所有读操作           |

| 问题       | 描述                                                         |
| ---------- | ------------------------------------------------------------ |
| 脏读       | 读到了另一个事务未提交的数据                                 |
| 不可重复读 | 在一个读事务中两次读同一个数据结果不一致(中间插入了update事务) |
| 幻读       | 在一个读事务中两次读操作得到的所有数据集合不一致(中间插入了insert/delete事务) |



控制事务函数: `conn.setAutoCommit( );` `conn.commit();` `conn.rollback();` 

```java
Connection conn = openConnection();
try {
    // 关闭自动提交:
    conn.setAutoCommit(false);
    // 执行多条SQL语句:
    insert(); 
  	update(); 
  	delete();
    // 提交事务:
    conn.commit();
} catch (SQLException e) {
    // 回滚事务:
    conn.rollback();
} finally {
    conn.setAutoCommit(true);
    conn.close();
}
```



### 连接池

在执行JDBC的增删改查的操作时，如果每一次操作都来一次打开连接，操作，关闭连接，那么创建和销毁JDBC连接的开销就太大了。为了避免频繁地创建和销毁JDBC连接，我们可以通过连接池（Connection Pool）复用已经创建好的连接。
一开始，连接池内部并没有连接，所以，第一次调用`ds.getConnection()`，会迫使连接池内部先创建一个`Connection`，再返回给客户端使用。当我们调用`conn.close()`方法时（`在try(resource){...}`结束处），不是真正“关闭”连接，而是释放到连接池中，以便下次获取连接时能直接返回。

JDBC连接池有一个标准的接口`javax.sql.DataSource`，要使用JDBC连接池，我们必须选择一个JDBC连接池的实现（如Druid）

```java
// HikariCP 链接池
HikariConfig config = new HikariConfig();
config.setJdbcUrl("jdbc:mysql://localhost:3306/test");
config.setUsername("root");
config.setPassword("password");
config.addDataSourceProperty("connectionTimeout", "1000"); // 连接超时：1秒
config.addDataSourceProperty("idleTimeout", "60000"); // 空闲超时：60秒
config.addDataSourceProperty("maximumPoolSize", "10"); // 最大连接数：10
DataSource ds = new HikariDataSource(config);
```

---

## jdbcTemplate

在Spring使用JDBC，首先我们通过IoC容器创建并管理一个`DataSource`实例，然后，Spring提供了一个`JdbcTemplate`，来管理`Connection`,`PreperedStatement`,`ResultSet`(也可以部分手动管理)

```java
// appconfig文件

@Configuration
@ComponentScan
@PropertySource("jdbc.properties") // 通过jdbc.properties文件读取url,username,password
public class AppConfig {

    @Value("${jdbc.url}")
    String jdbcUrl;

    @Value("${jdbc.username}")
    String jdbcUsername;

    @Value("${jdbc.password}")
    String jdbcPassword;

  	// 通过Ioc定义数据源
    @Bean
    DataSource createDataSource() {
        HikariConfig config = new HikariConfig();
        config.setJdbcUrl(jdbcUrl);
        config.setUsername(jdbcUsername);
        config.setPassword(jdbcPassword);
        config.addDataSourceProperty("autoCommit", "true");
        config.addDataSourceProperty("connectionTimeout", "5");
        config.addDataSourceProperty("idleTimeout", "60");
        return new HikariDataSource(config);
    }

  	// 通过Ioc定义jdbcTemplate
    @Bean
    JdbcTemplate createJdbcTemplate(@Autowired DataSource dataSource) { // 注入数据源
        return new JdbcTemplate(dataSource);
    }
}
```

### jdbc用法

#### 查询

`T execute(ConnectionCallback<T> action)`方法(自己管理`prepareStatement`和`resultSet`)

```java
public User getUserById(long id) {
    // 注意传入的是ConnectionCallback:
    return jdbcTemplate.execute((Connection conn) -> { 
      	// 参数是jdbcTemplate管理的Connection，不需要用户管理，由jdbcTemplate创建/释放
        // 在内部手动创建的PreparedStatement、ResultSet必须用try(...)释放:
        try (var ps = conn.prepareStatement("SELECT * FROM users WHERE id = ?")) {
            ps.setObject(1, id);
            try (var rs = ps.executeQuery()) {
                if (rs.next()) {
                    return new User( // new User object:
                            rs.getLong("id"), // id
                            rs.getString("email"), // email
                            rs.getString("password"), // password
                            rs.getString("name")); // name
                }
                throw new RuntimeException("user not found by id.");
            }
        }
    });
}
```

`T execute(String sql, PreparedStatementCallback<T> action)`方法 (自己管理`resultSet`)

```java
public User getUserByName(String name) {
    // 需要传入SQL语句，以及PreparedStatementCallback:
    return jdbcTemplate.execute("SELECT * FROM users WHERE name = ?", (PreparedStatement ps) -> {
        // PreparedStatement实例已经由JdbcTemplate创建，并在回调后自动释放:
        ps.setObject(1, name);
        try (var rs = ps.executeQuery()) {
            if (rs.next()) {
                return new User( // new User object:
                        rs.getLong("id"), // id
                        rs.getString("email"), // email
                        rs.getString("password"), // password
                        rs.getString("name")); // name
            }
            throw new RuntimeException("user not found by id.");
        }
    });
}
```

`T queryForObject(String sql, Object[] args, RowMapper<T> rowMapper)`方法

```java
public User getUserByEmail(String email) {
    // 传入SQL，参数和RowMapper实例:
    return jdbcTemplate.queryForObject("SELECT * FROM users WHERE email = ?", new Object[] { email },
            (ResultSet rs, int rowNum) -> {
                // 将ResultSet的当前行映射为一个JavaBean:
                return new User( // new User object:
                        rs.getLong("id"), // id
                        rs.getString("email"), // email
                        rs.getString("password"), // password
                        rs.getString("name")); // name
            });
}
```

`T queryForObject(String sql, Object[] args, RowMapper<T> rowMapper)`
只需操作`ResultSet`，无需自己创建任何组件
返回类型为RowMapper的`T`，从`RowMapper<T> rowMapper`return处自动推导，`RowMapper`不一定返回JavaBean，实际上它可以返回任何Java对象

```java
public User getUserByEmail(String email) {
    // 传入SQL，参数和RowMapper实例:
    return jdbcTemplate.queryForObject("SELECT * FROM users WHERE email = ?", new Object[] { email },
            (ResultSet rs, int rowNum) -> {
                // 将ResultSet的当前行映射为一个JavaBean:
                return new User( // new User object:
                        rs.getLong("id"), // id
                        rs.getString("email"), // email
                        rs.getString("password"), // password
                        rs.getString("name")); // name
            });
}
```

如果我们期望返回多行记录，而不是一行，可以用`List<T> query(String sql, Object[] args, RowMapper<T> rowMapper)`方法：
如果数据库表的结构恰好和JavaBean的属性名称一致，那么`BeanPropertyRowMapper`就可以直接把一行记录按列名转换为JavaBean

```java
public List<User> getUsers(int pageIndex) {
    int limit = 100;
    int offset = limit * (pageIndex - 1);
    return jdbcTemplate.query("SELECT * FROM users LIMIT ? OFFSET ?", new Object[] { limit, offset },
            new BeanPropertyRowMapper<>(User.class));
}
```

`<T> T query(String sql, Object[] args, ResultSetExtractor<T> rse)`返回单行数据

```java
    public Users selectUserById(Integer id) {
        String sql = "select * from users where userid = ?";
        Object[] arr = new Object[] {id};
        return jdbcTemplate.query(sql, arr, (ResultSet rs) -> {
            rs.next();
            return new Users(rs.getInt("userid"), rs.getString("username"), rs.getString("usersex"));
        });
    }
```



#### 更新

```java
public void updateUser(User user) {
    // 传入SQL，SQL参数，返回更新的行数:
    if (1 != jdbcTemplate.update("UPDATE user SET name = ? WHERE id=?", user.getName(), user.getId())) {
        throw new RuntimeException("User not found by id");
    }
}
```

#### 插入

```java
public void insertUsers(Users users) {
        String sql = "insert into users(username, usersex) values(?,?)";
        jdbcTemplate.update(sql,users.getUsername(), users.getUsersex());
    }
```

#### 删除

```java
public void deleteUserById(Integer id) {
        String sql = "delete from users where userid = ?";
        jdbcTemplate.update(sql, id);
    }
```

