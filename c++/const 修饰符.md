# const 修饰符

### const对象

```c++
i = ci;
ci = i;
i = r;
i = cr;
ci = r;...// (引用，指针做右值时行为相当于普通对象)
```

执行拷贝操作没有限制，因为等号左右的对象没有关系

### 引用

```c++
T &r = x;
```

r可以绑定到T类型的`非const对象`或`左值引用`

不可以重新绑定，可以修改所绑定对象的值

### 常量引用

`底层const`     `对常量的引用`     `常量引用`

```c++
const int &r = i;	

double d = 9.00;
const int &r2 = d; // 正确
```

不可以重新绑定，也不可以修改所绑定对象的值

可以绑定到

- 本类型：const/非const对象，const/非const引用
- 可以转化为该类型的：const/非const对象，const/非const引用

```c++
int x = 100;
    int const cx = 1100;
    
    int &r = x;
    int const &cr = x;
    
    int *p = &x;
    int const *cp = &x;
    
    {// 引用 = 对象
        int &r = x;
        // int &r = cx; wrong!
        int const &cr = x;
        int const &cr2 = cx;
    }
    {// 引用 = 引用
        int &r2 = r;
        int const &cr = r;
        // int &r3 = cr; wrong!
        int const &cr2 = cr;
    }
    {// 对象 = 引用
        int x = r;
        int x2 = cr;
        int const cx = r;
        int const cx2 = cr;
    }
```

> 引用不可以绑定到非常量对象或引用，剩下都可以

**函数传参：**

```c++
void f(T &x);
```

可以传入一个`T类型` `非常量` `对象/引用`(2种)

> 传入引用时即 x绑定到该引用绑定的对象

```c++
void f(T const &x);
```

可以传入`T类型/可以隐式转换为T的类型` `常量/非常量` `对象/引用`(6种)

> 传入T类型对象时则绑定到该对象，避免复制
>
> 传入非T类型对象时则绑定到该对象的拷贝，有复制

```c++
void f(T x);
```

可以传入`T类型` `常量/非常量` `对象/引用`(2种)

> 传入引用时即为引用绑定的对象值复制到x

### 指针和const

`底层const`    `指向常量的指针`   

不可以用指针改变对象的值，可以重新绑定

```c++
const int* p = &i;
```

`顶层const`    `常量指针`

不可以重新绑定，可以用来改变对象的值

```c++
int* const p = &i;
```

### const拷贝

#### 赋值

底层const = 底层const/非const/顶层const  ​​ :white_check_mark:

非const/顶层const = 底层const		:x:

总结：

>  顶层const对另一边无要求
>
> 底层const要求另一边也是底层const或可以转换为底层const（如非底层const做右值）

```c++
int a = 1;
    /*
     ----------指针-------------
     */
    {
        int* const p1 = &a;
        int* p = &a;
        //底层const = 顶层const
        const int *p2 = p1;
        //底层const = 非const
        const int *p3 = p;
        
    }
    {
        const int* p1 = &a;
        //顶层const = 底层const
        int* const p2 = p1;     //(wrong!)
        //非const = 底层const
        int* p3 = p1;           //(wrong!)
    }
    /*
    ----------引用-------------
    */
    {
        int &r = a;
        //底层const = 非const
        const int &r1 = a;
        //非const = 底层const
        int &r2 = r1;           //(wrong!)
    }
```

#### 函数传参

常量引用

底层const做左值，对const属性无要求

```c++
void f(const int& x);
```

指向常量的指针

底层const做左值，对const属性无要求

```c++
void f(const int* p);
```

常量指针

顶层const做左值，不可以传递顶层const（指向常量的指针）

```c++
void f(int* const p);
```

---

### const 类

类中成员

数据成员全部为`顶层const`

只可以调用const函数

```c++
class Foo
{
public:
    int value = 1;
    int* pointer = &value;
    
};

int main()
{
    const Foo x;
    
    int i = 11;
    // x.pointer = &i; wrong!
    *x.pointer = 11;
    cout << *x.pointer << endl;
    return 0;
}

```

