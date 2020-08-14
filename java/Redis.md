# Redis

## 数据结构

```
select i     // 选择数据库
DBSIZE       // 查看数据库大小
keys *       // 查看所有键
flushdb      // 清空数据库
FLUSHALL     // 清空所有数据库
EXISTS [key] // key是否存在
move [key] 1 // 移除数据
EXPIRE [key] [second] // 设置过期时间
ttl [key]    // 查看当前key剩余时间
type key		 // 查看key类型
```

Redis是单线程的，基于内存的，Redis性能瓶颈是内存是网络带宽

### String

value是`字符串`或`数字`

```
set [key] [value]
get [key]
APPEND [key] [value] // 拼接字符串
STRLEN [key]				 // 字符串长度
incr [key]
decr [key]					 // 整数value ++/--
INCRBY [key] [num]
DECRBY [key] [num]	 // 整数增加/减少num
GETRANGE [key] [beg] [end] // substr(beg, end) , 包括end
SETRANGE [key] [beg] [value] // 从beg开始替换为value
setex [key] [seconds] [value] // 设置有过期时间的数据
setnx [key] [value] // 如果不存在则设置
mset [key] [value] [key] [value]... // 批量设置
mget [key] [key]... // 批量获取
getset [key] [value] // 先get再set（若存在）
```

### List

元素均是字符串

实际上是一个链表

```
LPUSH [list] [value]      // 左插入
LRPUSH [list] [value]			// 右插入
LPOP [list]
RPOP [list]								// 删除
LRANGE [list] [beg] [end] // 范围查询
lindex [list] [index]			// 下标查询
Llen [list]								// 列表长度
lrem [list] [num] [value] // 删除num个value
ltrim [list] [beg] [end]  // 截取list
rpoplpush [list1] [list2] // 移动元素
lset [list] [index] [value] // 更改元素值(若存在)
LINSERT [list] [before/after] [value] [value] // 插入值
```

### Set

``` 
sadd [set] [value] // 添加值
SISMEMBER [set] [value] // 值是否存在
scard [set] // set长度
srem [set] [value] // 移除元素
SRANDMEMBER [set] [num] // 随机拿出元素
spop [set] // 随机删除元素
smove [set1] [set2] [value] // 移动元素
SDIF [set1] [set2] // 差集
SINTER [set1] [set2] // 交集
SUNION [set1] [set2] // 并集
```

### Hash

key-(key-value)

```
hset [hash] [field] [value] // 设置值
hget [hash] [field]					// 获取值
hmset [hash] [field] [value]... // 批量设置
ggetall [hash] // 删除所有值
hdel [hash] [field] // 删除数据
hlen [hash] // 长度
hexits [hash] [field] // 判断数据是否存在
hkeys [hash]		// 所有键
hvals [hash]		// 所有值

```

### Zset

有序集合

```bash
zadd [set] [score] [value] [score] [value] // 添加多个值(score为排序键)
ZRANGE [set] [beg] [end] // 查找范围
ZRANGEBYSCORE [set] [beg] [end] // 查找范围
zrem [set] [value] // 移除
```

### geospatial 地理位置

```
geoadd [map] [纬度] [经度] [name] // 插入
geopos [map] [name] // 查询
geodist [map] [name] [name] [单位] // 查询距离
georadius [map] [经度] [纬度] [半径] [单位]
georadiusbymember [map] [name] [半径] [单位]
```

### Hyperloglog

统计集合基数，省内存

```
PFadd [set] [value] // 添加
PFCOUNT [set] // 计数
PFMERGE [set] [set] // 合并
```

### Bitmaps

位存储

```
setbit [set] [pos] [value] // 添加
getbit [set] [pos] // 查看
bitcount [set] // 统计1的个数
```

## 事务

```
multi // 开启事物
exec  // 执行事务
discard // 放弃事务,命令都不执行
```

事务不保证原子性

异常与事务

- 编译型异常（代码错误）：事务中所有代码都不执行
- 运行时异常(1/0)：错误代码不执行，剩下的都执行

悲观锁：

安全性高，性能低

乐观锁：

安全性低，性能高

```
watch [value] // 乐观锁监视值
multi
...
另一个线程修改value
exec
失败！
unwatch // 取消乐观锁
```

## 整合

### Jedis

```xml
<dependency>
    <groupId>redis.clients</groupId>
    <artifactId>jedis</artifactId>
    <version>3.3.0</version>
</dependency>
```

```java
Jedis jedis = new Jedis(host, port); // 打开连接
jedis.close(); // 关闭连接
```

事务

```java
Transaction multi = jedis.multi() // 开启事务
try {
  ...
  multi.exec() // 关闭事务
} catch(Exception e) {
  multi.discard(); // 回滚事务
  e.printStackTrace();
} finally {
  jedis.close(); // 关闭连接
}
```

### SpringBoot 整合

Jedis: 直连，多线程不安全

Lettuce: 采用netty框架，可以在多个线程中共享，线程安全，高速

```java
// properties
spring.redis.host=127.0.0.1
spring.redis.port=6479
```

```java
redisTemplate.opsFor...(); // 对应各种数据类型的命令
```

默认的序列化方式为`jdk序列化`

自定义`RedisTemplate`

