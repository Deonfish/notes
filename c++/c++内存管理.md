# c++内存管理

### malloc/free

```c++
//接受一个size，分配size个B内存，返回void指针
void *p = malloc(512);
int *p1 = (int*)malloc(512);
//接受指针（把指针自动从T*转换为void*），free malloc申请的空间（不管多大）
free(p);
free(p1);
```

---

### operator new/delet

`可重载`

> 只是对`malloc/free`的简单包装，参数和返回值都一致

```c++
//接受一个size，分配size个B内存，返回void指针
void* p = ::operator new(512);
//static_cast把void*转int*更安全
int* p1 = static_cast<int*>(::operator new(sizeof(int)));

::operator delet(p);
::operator delet(p1);
```

#### array new/delet

`可重载`

```c++
//调用默认构造函数（此处无法赋值）并分配空间
Foo* p = new Foo[5];
//调用析构函数并释放空间
delet[] p;
```

Tips：

若`new Foo[5]`申请的空间调用`delete p`而不是`delet[] p`

对于没用另外申请空间的类（无指针的类）没有影响

对于有指针的类会造成内存泄漏，因为只调用了一次析构函数，没有调用析构函数的对象申请的空间不会释放，见下图：

![](https://i.loli.net/2020/03/06/vB9RCxQKOEtrIb4.png)

#### placement new/delet

`可重载`

```c++
//对已分配好的Foo* 对象调用构造函数，并不分配空间
Foo* p = (Foo*)::operator new(sizeof(Foo)); //分配空间
Foo* p = new(p) Foo(a1, a2, ...); //构造函数
```

所有`内置类型`，`复合类型` 均可用其构造，调用构造函数（伪）

```c++
// 用 placement new 构造 int指针
int** p = deonSTL::allocator<int*>::allocate();
::new(p) int*();
cout << *p << endl;
```



---

### expression new/delet

```c++
//new+构造函数，返回该类的指针
Foo<int>* p = new Foo<int>();
//析构函数+delet
delet p;
```

`expression new` -> `operator new + 构造函数` -> `malloc`

`expression delet` -> `析构函数 + operator delet` -> `free`

重载：

`expression new` -> `Foo::operator new`

 `expression delet` -> `Foo::operator delet`

---



### allocate/deallocate

```c++
//分配5个int
int* p = std::allocator<int>().allocate(5); //必须要count
std::allocator<int>().deallocate(p, 5);	//必须要count
```







