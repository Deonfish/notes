# JPA 笔记

### 配置

#### 1. Maven 依赖

```xml
        <dependency>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-starter-data-jpa</artifactId>
        </dependency>

        <dependency>
            <groupId>mysql</groupId>
            <artifactId>mysql-connector-java</artifactId>
        </dependency>
```

#### 2. Application.yml

```yaml
spring:
  datasource:
    driver-class-name: com.mysql.jdbc.Driver
    username: root
    password: guo971001
    url: jdbc:mysql://localhost:3306/mydemo?useSSL=false
```

#### 3. 实体类

```java
@Entity // 实体注解
@Table(name="users") // 对应数据表，若无则默认表名与类名相同
@Data
public class user {
    @Id // 主键
    private long userid;
    private String username;
    private String usersex;
}
```

#### 4. DAO 层

```java
@Repository	// 数据库注解								  		 <实体类, 主键类型>
public interface userDao extends JpaRepository<user, Long> { 
}
```

### 其他

#### 自定义 Repository 接口

```java
// 1. 根据函数名推断
  List<user> findByName(String name);
// 2. query注解（查询）
	@Query("user where username=?")
	List<user> findByName(String name);
```

