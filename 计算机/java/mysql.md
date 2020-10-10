# mysql

```mysql
mysql -u root -p [passward]; //	start mysql
show databases;
create datebase [database];
use [database];
show tables; 							// 查看所有表格
source [path]; 						// 初始化数据库
drop database [database]; // 删除数据库
desc [database];					// 查看表结构
select database();				// 查看当前数据库
select version();					// 查看当前版本
```

## 查询语句

### 条件查询

```mysql
select [字段名] from [表名] where [条件];

// 查询年薪，重命名为yearsal
select name, sal*12 (as) yearsal from emp; 
// 查询全部字段（实际开发中不使用）
select * from emp;
// 查询工资是null的
select name, sal from emp where sal is null;
// 查询工资是1000或5000
select name, sal from emp where sal in(1000, 5000);
// 找出名字中有o的
select name from emp where name like '%o';
// 找出名字中第二个字母是o的
select name from emp where name like '_o%';
// 找出名字中有_的
select name from emp where name like "%\_%";

```

> Sql语句以";"结尾
>
> sql语句不区分大小写
>
> 字符串最好使用单引号（兼容性好）

### 排序查询

```mysql
// 默认升序，asc:升序，desc:降序
select [字段]	from [表名] order by [字段] [asc/desc]; 

// 按照工资将序，名字升序排（工资相等时）
select name, sal from emp order by sal desc, name asc;
// 根据第二列排序
select name, sal from emp order by 2;

```

去除重复

```mysql
select distinct job from emp;
// 去除depno,job均重复的
select distinct deptno, job from emp;
// 统计job种类数
select count(distinct job) from emp;
```

### 分组函数

#### 多行处理函数

```mysql
select func([字段]) from [表名]

sum
max
min
avg
count
```

> 分组函数忽略null

#### 单行处理函数

```mysql
select name, (sal+comm)*12 as yearsal from emp;

// null映射为0
select name, ifnull(comm, 0) as comm from emp;
```

> 若数据中有null，运算结果为null

#### group by 和 having

`group by`分组，`having`对分组后过滤

```mysql
// 相等的分为一组
select func([字段]) from [表名] group by [字段];

// 找出每个部门不同岗位的最高薪资(按部门现分组，再按岗位分组)
select deptno, job, max(sal) from emp group by deptno, job;

// 找出每个部门平均薪资，显示大于2000的数据(having 效率较低)
select deptno, avg(sal) from emp group by deptno having avg(sal) > 2000
```

> select中的字段只能是group by 的字段

执行顺序：

```
select   5
from     1
where    2
group by 3
having   4
order by 6
```

### 连接查询

#### 内连接

条件匹配不上的丢失

```mysql
// 两张表的笛卡尔积
select name, dname from emp, dept; 
// 别名,过滤查询（老语法）
select e.name, d.dname from emp e , dept d where e.deptno = d.deptno;
// （新语法）
select [..] from [..] (inner) join [..] on [条件]
// 等值连接
select e.name, d.dname from empe join dept d on e.deptno = d.deptno;
// 非等值连接
select e.name, e.sal, s.grad from emp e join salgrade s on e.sal between s.losal and s.hisal;
// 自连接(自己连自己)
// 找领导
select a.name, b.name from emp join emp b on a.mgr = b.empno;
```

#### 外连接

分主副表，主表全部匹配出来，副表匹配不出来用`null`匹配

```mysql
// 左边是主表
select a.name, b.name from emp a left (outer) join emp b on a.mgr = b.empno;
// 三张表连接
select e.ename, d.dname, s.grade from emp e join dept d on e.deptno = d.deptno join salgrade s on e.sal between s.losal and s.hisal;
```

### 子查询

```mysql
select [子查询] from [子查询] where [子查询];
```

### union

”拼“表

```mysql
select ename, job from emp where job = 'MANAGER'
union
select ename, job from emp where job = 'SALESMAN';
```

### limit

mysql 特有，在语句中最后执行

```mysql
limit startIndex, length
// 取出工资前五名
select ename, sal from emp order by sal desc limit 0, 5;
```

---

## 创建语句

### 创建

```mysql
create teble [table](
	[字段] [数据类型], default [value]... // 默认值
)
```

数据类型

| 类型    | 含义                                      | Java                       |
| ------- | ----------------------------------------- | -------------------------- |
| int     | 整数                                      | int                        |
| bigint  | long整数                                  | long                       |
| float   | 浮点数                                    | float/double               |
| char    | 定长字符串                                | String                     |
| varchar | 不定长字符串                              | StringBuffer/StringBuilder |
| date    | 日期类型                                  | java.sql.Date              |
| BLOB    | 二进制对象｜Binary Large Object           | Object                     |
| CLOB    | 字符对象（文本）\| Character Large Object | Object                     |

> 表名一般以"t_ \ tbl_"开始

### 插入

```mysql
// 字段和值要对应(顺序不必一致),未指定字段插入null
insert into 表名(字段1，字段2，...) values(值1，值2，...)

// 省略字段后value必须全部都有
insert into t_student values(1, 'jack', '0');
// 一次插入多行数据
insert into t_student(...) values(...), (...);
```

### 复制

```mysql
create table [表名] as [select语句] // 以查询结果创建表
insert into [表名] [select语句]			// 插入查询结果
```

### 修改数据

```mysql
update [表名] set [字段]=[值], ...
```

### 删除数据

```mysql
delete from [表名] where [条件]
delete from [表名]; 						// 删除所有记录
```

```mysql
truncate table emp; // 快速删除（不可恢复）
```

### 约束

| 约束                   | 关键字      |
| ---------------------- | ----------- |
| 非空约束               | not null    |
| 唯一约束               | unique      |
| 主键约束（非空且唯一） | primary key |
| 外键约束               | foreign key |

```mysql
create table t_user(
	username varchar(255) not null, ... // 列级约束
)
```

#### unique

```mysql
create table t_user(
	usercode varchar(255),
	username varchar(255),
	unique(usercode, username) // 表级约束，不可联合重复
)
```

#### 主键约束

```mysql
create table t(
	id int primary key, ...
)
```

> 任何一张表都应该有主键
>
> 一张表的主键约束只有一个

复合主键(不建议)

```mysql
create table t(
	id int,
	name varchar,
	primary key(id, name)
)
```

**一般主键和业务分离（id和身份证号分离）,即主键不要有含义**

主键值自增

```mysql
create teble t(
	id int primary key auto_increment,
  username varchar(255)
);
// 不用指定主键，自动增加填充
insert into t(username) values('a');
insert into t(username) values('b');
```

#### 外键约束

引用别表数据的表称为`子表`

```sql
create table t_class( // 父表
	cnum int,
	cname varchar(255),
	primary key(cnum)
);
create table t_student( // 子表
	snum int,
	sname varchar(255),
	classnum int,
	foreign key(classnum) references t_class(cnum)
);
```

> 外键可以为null
>
> 外键可以不是主键，但一定具有unique约束

## 存储引擎

![image-20200614122145131](/Users/guosongnan/Library/Application Support/typora-user-images/image-20200614122145131.png)

![image-20200614151426366](/Users/guosongnan/Library/Application Support/typora-user-images/image-20200614151426366.png)

![image-20200614151623174](/Users/guosongnan/Library/Application Support/typora-user-images/image-20200614151623174.png)

## 事务 Transaction

把一些操作存入缓存，执行时一起执行

> 一个完整的业务逻辑单元，不可再分
>
> 和事务相关的语句只有DML语句（insert delete update）

事务的四大特性：ACID

- 原子性：事务是最小单元
- 一致性：事务同时成功或同时失败
- 隔离性：事务A与事务B之间隔离
- 持久性：数据必须持久化到硬盘才算成功

事务的隔离级别：

- 第一级别：读未提交( read uncommitted )
  对方数据未提交，当前数据可以读到
- 第二级别：读已提交( read committed )
  对方提交的数据才可以读到，不可重复读取
- 第三级别：可重复读( repeatable read )
  提交的别人也读不到，解决了不可重复读的问题
  事务开始时备份数据，别人修改后我这里仍然是我的数据
- 第四级别：序列化读/串形化读( serializable )
  事务不可并发

```mysql
// 设置事务的隔离级别
set global transaction isolation level read uncommitted; 
// 查看隔离级别
select @@global.tx isolation;
```



> mysql默认第三级别
>
> 默认自动提交（执行每一个语句都提交）

```mysql
start transaction; // 开启事务
savepoint [name];  // 存储点
commit;						 // 提交事务
rollback;					 // 提交事务，回滚
```

## 索引

不加索引时搜索会搜索全表，加索引后会根据索引扫描

> 有unique约束或主键自动添加索引

```mysql
// 创建索引
create index [索引名称] on [表名]([字段名]);
// 删除索引
drop index [索引名称] on [表名];
// 根据索引查询
select name, sal from emp where sal = 5000; // sal 添加了索引
```

## 视图

```mysql
create view myview as select empno, ename from emp;
drop view myview;
```

> 修改视图会修改原表
>
> 视图可以隐藏表的实现细节

## DBA命令

```mysql
// 导出数据库(终端命令)
mysqldump [数据库]>[path/database.sql] -u [user] -p [passward]
// 导入数据库
create database [..];
use [...];
source [path/database.sql];
```

## 行级锁

```mysql
// 选中的行数据在事务结束之前不可修改
select ... for update; 
```



## 数据库设计

设计三范式

- 表都应该有主键，每个字段原子性不可再分
- 所有非主键字段完全依赖主键，不能产生部分依赖
  eg.表的主键是学生id和教师id，非主键是学生名字，只依赖学生id
- 所有非主键字段不能产生传递依赖，直接依赖主键
  eg.班级依赖学生名字，学生名字依赖主键学生id

> 解决数据冗余