# const 修饰符

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



