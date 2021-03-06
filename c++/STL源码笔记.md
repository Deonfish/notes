# 小知识

### is_trivially_destructible

```c++
template<class T>
struct is_trivially_destructible{	//聚合类
public:
	static bool value;	//静态数据
  
  operator bool();	//提供类到bool的转换
}
```

调用

```c++
cout << std::is_trivially_destructible<std::string>::value
// 实测 value 无法转换为 std:: true_type
cout << std::is_trivially_destructible<std::string>{}
```

---

### 迭代器

迭代器操作           说明
(1)所有迭代器

类型 `It` 满足[*可复制构造* *(CopyConstructible)* ](https://zh.cppreference.com/w/cpp/named_req/CopyConstructible) 

类型 `It` 满足[*可复制赋值* *(CopyAssignable)* ](https://zh.cppreference.com/w/cpp/named_req/CopyAssignable) 

类型 `It` 满足[*可析构* *(Destructible)*](https://zh.cppreference.com/w/cpp/named_req/Destructible) 

类型 `It` 的[左值](https://zh.cppreference.com/w/cpp/language/value_category)满足[*可交换* *(Swappable)* ](https://zh.cppreference.com/w/cpp/named_req/Swappable) 

p++               后置自增迭代器
++p               前置自增迭代器
(2)输入迭代器
*p                 复引用迭代器，作为右值
p=p1               将一个迭代器赋给另一个迭代器
p==p1              比较迭代器的相等性
p!=p1              比较迭代器的不等性
(3)输出迭代器
*p                 复引用迭代器，作为左值
p=p1               将一个迭代器赋给另一个迭代器
(4)正向迭代器
提供输入输出迭代器的所有功能
(5)双向迭代器
--p                前置自减迭代器
p--                后置自减迭代器
(6)随机迭代器
p+=i               将迭代器递增i位
p-=i                将迭代器递减i位
p+i                在p位加i位后的迭代器
p-i                 在p位减i位后的迭代器
p[i]                返回p位元素偏离i位的元素引用
p<p1               如果迭代器p的位置在p1前，返回true，否则返回false
p<=p1              p的位置在p1的前面或同一位置时返回true，否则返回false
p>p1               如果迭代器p的位置在p1后，返回true，否则返回false
p>=p1              p的位置在p1的后面或同一位置时返回true，否则返回false

总结：

**Input Iterator**：只能单步向前迭代元素，不允许写，可判断迭代器是否相等。(只读迭代器)

> 特别的，输入迭代器只支持一次读，即不允许把当前位置迭代器记存一个副本，等以后再使用（例 istream_iterator 中从一个输入流istream中读取，传递值以后不保证这个值还存在），若想记录位置需要用 Forward Iterator

**Output Iterator**：只能单步向前迭代元素，对元素只有写的权力，不可判断迭代器是否相等。

**Forward Iterator**：InputIterator+OutputIterator，可单向迭代元素，可读可写，可以判断迭代器是否相等。（基本读写迭代器）

**Bidirectional Iterator**：该类迭代器是在Forward Iterator的基础上提供了单步向后迭代元素的能力。（双向读写迭代器）

**Random Access Iterator**：该类迭代器能完成上面所有迭代器的工作，它自己独有的特性就是可以像指针那样进行算术计算，而不是仅仅只有单步向前或向后迭代。（随机读写迭代器）



### const iterator 与 const_iterator

```c++
const vector<int>::iterator iter = vec.begin();
```

这是顶层const，迭代器不允许++但允许改变迭代器所指之物

```c++
vector<int>:: const_iterator iter = vec.begin();
```

这是底层const，迭代器允许++但不允许改变迭代器所指之物



### iterator_base

STL在实现`iterator`时把数据放在`iterator_base`类中以实现const和非const迭代器拥有相同的指针，且可相互转化类型 ( 用reinterpre_cast )



---

### noexcept

断言函数不会抛出异常，若抛出异常则程序中断

通常用于以下两种情况：

1. 程序会抛出异常：
   此时用`noexcept`是因为不知如何处理异常，直接中断
2. 程序不会抛出异常或异常被处理：
   此时用`noexcept`是为了加速编译，优化代码

```c++
void func(int x) noexcept{
	throw 1;
  std::cout << "这行不会执行\n";
}
```

```c++
//程序不会中断，因为异常被 catch 到
void func(int x) noexcept{
	try{
    throw 1;
  }
  catch(...){
    std::cout << "异常被处理\n";
  }
}
```

---

### explicit

出现在单参数构造函数中（非拷贝构造函数）

声明这不定义隐式类型转换

```c++
explicit vector(size_type n);

vector vec = 10;	//错误
vector vec(10);		//正确
```

---

### is_trivially_copy_assignable

相似的 `type_traits` 提供向 `std::true/false_type` 的隐式类型转换，bool则不可以转换为`std::true/false_type`

```c++
void __uinitialized_fill_n( ForwardIt first, Size n, const T& value,
                      std::false_type)
  
// 错误，无法转换
__uinitialized_fill_n(..., 
                      is_trivially_copy_assignable<...>::value );

// 正确
__uinitialized_fill_n(...,
                     is_trivially_copy_assignable<...>{})
```

---

### 初始化与赋值

`已分配的未初始化空间`用`placement new`(调用构造函数)(已初始化空间仍可用`placement new`，但是有可能内存泄漏)

`已分配已初始化的空间`用`拷贝赋值`，拷贝赋值负责把原对象析构

#### uinitialized_move

Uinitialized_move -> construct(T*, value&&) -> T(T&&) (调用移动构造函数)

窃取原空间并把原对象置为可析构对象（自己的空间全部放弃）

#### uinitialized_fill

Uninitialized_fill -> construct(T*, const value& ) -> T(const value& )(调用拷贝构造函数)

另行申请空间，拷贝原对象，不操作原对象

---

### 异常

如果一个函数在执行过程中拋出的异常在本函数内就被 catch 块捕获并处理，那么该异常就不会拋给这个函数的调用者（也称为“上一层的函数”）；如果异常在本函数中没有被处理，则它就会被拋给上一层的函数

---

### 继承

基类和派生类指针互相转化

```c++
struct Base
{
    int base_value = 100;
};
struct Child : public Base
{
    int child_value = 200;
};

int main()
{
    Child a{};
    Base*  bp = &a;
    cout << bp->base_value << endl; // cout: 100
    
    Base  b{};
    Child* cp = reinterpret_cast<Child*>(&b);
    cout << cp->base_value << endl;// cout: 100
    return 0;
}
```

派生类可自动转换为基类

基类指针可以通过`reinterpret_cast`转换为派生类，转换后的指针不可以访问派生类空间的元素（不存在）

如果这个基类对象本是在某处由派生类转换而来（赋值，传参，显示转换等），可以对其安全的调用`reinterpret_cast`转换为派生类

---

### 值初始化与默认初始化

> 内值类型

#### 值初始化

- 全局变量（包括全局类对象中的内值类型执行合成的构造函数）

#### 默认初始化

- 函数内部变量（包括类对象中的内置类型）
- 类成员函数（无论类对象为全局还是局部变量）

> `{}列表初始化`可避免默认初始化

---

### STL对越界异常的规定

> 好像不管...

测试：

- 在vector的越界输出乱码
- 在set的越界程序出现bug
- 在deque的越界出现bug

---

### 模板实参推导

#### 函数模板

> T永远是纯类型或指针，不会是引用或const

```c++
template <class T>
void f(T x);
template <class T>
void cf(const T x);
template <class T>
void rf(T& x);

int n;
const int cn = 10;
int &r = n;

// 顶层const在实参推导时被忽略（T不会被推导为const）
f(cn); // 调用 f(int)，T 被推导为int
cf(n); // 调用 cf(const int)，T被推导为int
f(r);  // 调用 f(int)，T被推导为int

rf(...)// 只支持精确匹配，T被推导为纯类型（非const或引用）
```

#### 类模板

> 给什么是什么

```c++
const:
vector<const int> vec(1,10);
vec[0] = 100; // error!
=========================
reference:
template <class T>
class Foo
{
public:
  // Constructor for 'Foo<int &>' must explicitly initialize the reference member 'n'
    Foo(){} 
    T n;
    void f(){ n += 10; }
};
    Foo<int&> foo;

```

不会声明`template <class const T>`之类的



---

#### constexpr 函数

优点：

- 编译时直接求值，加快运行速度
- 允许函数被应用在以前调用宏的所有场合，如数组大小处

要求：

- 参数为常量
- 函数中只能有一个return语句（有极少特例）
- 只能调用其它constexpr函数
- 只能使用全局constexpr变量

> 一个声明为constexpr的函数同样可以在运行时被调用，当这个函数的参数是非常量的

#### 聚合类

若聚合类数据成员全部为字面值，聚合类构造函数声明为constexpr，聚合类可当作常量表达式使用



### 不同机器上类型长度

char，short，float，double，longlong等在32位和64位机均相同

int：		 均为 4B ( 32位 )

long：	  4B ( 32位机 ) 或 8B（64位机）

pointer： 4B（32位机）或 8B（64位机）

size_t：	4B（32位机）或 8B（64位机）



### 可以根据返回类型重载函数



---



### bug记录

忘记this是指针

 ```c++
bool operator!=(const ... rhs){ return !(this == rhs); }  // wrong
bool operator!=(const ... rhs){ return !(*this == rhs); }	// correct
 ```

rb_tree_erase节点替换时不可以简单的swap，会引起destroy错误 ( 慎用swap⚠️ )

```c++
// 错误
if(y != z)
{
  std::swap(y->value, z->value);
  rb_tree-transplant(y, x, root, lmost, rmost);
}
// 正确
if(y != z)
    {// y 指向z的后继，x指向y的右节点（可能为空）
        if(y->parent != z){
            rb_tree_transplant(y, x, root, lmost, rmost);
            y->right = z->right;
            y->right->parent = y;
        }
        rb_tree_transplant(z, y, root, lmost, rmost);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
        z = y;  // 由上层控制释放z的空间
    }
```

initializer_list ❓