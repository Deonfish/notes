# c++算法相关语法小知识

#### int大小

范围：-2^31^~2^31^-1 ( 2147483647/0x7fffffff )，小于10^9^ ( 大概2*10^9^ )

占用 32bit（4B）

#### string的比较

字典序比较，从高位开始比较，哪一位大的大；若每一位都一样大则长度长的大。

`'0' < '1' < '2' < ... < '9' < 'a' < 'b' < ... < 'z'`

注意：

字符串比较不可直接作为数字比较

```c++
string s = "200", s2 = "1000000000";
    if(s > s2) printf("yes\n"); // yes
```

### 输入输出

#### scant & printf （节省时间）

格式化字符串包括读取元素(`%d`)和空白字符(空格回车等)，一个读取元素匹配一个流中的元素，一个空白字符匹配多个流中的空白符。

scanf读取时自动忽略流开始的所有空白字符(读取char除外)，从第一个非空白符开始匹配，遇到第一个不匹配元素或全部匹配成功时返回，没有匹配的字符会全部留在流中。

注意：以下代码中最后的换行符会被保留

```c++
scanf("%d %d", &a, &b); // 输入流: \n\n\n123   \n111\n\n
// a=123, b=111, 输入流=\n\n
```

scanf返回成功赋值的参数数量(无论整个输入成功与否)，若第一个参数就接受失败（如流中为结束符EOF），则返回EOF（int值为0）。

> 注意scanf别忘了`&`，输入string前别忘了resize

```c++
str.resize(100);	// 输入string前要resize!
scanf("%s %d", &str[0], &x); 			 // 输入string和整数
printf("%s %d\n", str.c_str(), x); // 输出string和整数
```

#### cin

忽略前置的空白字符(char不除外！)，匹配读取，读取到空白符结束（不消耗最后的空白符）。

若匹配失败则设置输入值为null，消耗所有流。

返回值为`basic_istream`类型，读取失败时设置该对象的bool函数为false

注：scanf可以把一个char字符输入为`\n`，而cin无法把一个cahr类型输入为`\n`因为空白符全部作为分割标志。

#### getline

在头文件`<string>`中

接收从流中第一个字符开始（空白符也计入），到换行符为止，换行符不保留在流中。

遇到文件结尾读取失败。

返回值为`basic_istream`类型，读取失败时设置该对象的bool函数为false，所以可以写如下代码:

```c++
while(getline(cin, line)) { ... }
```

> 注意与标准流(cin/scanf)配合时，标准输入流后的getline要先把换行符用掉(用getchar等)。getline之后的标准流不用特殊处理。

```c++
// \nqqq\n
getline(cin, str);
// 此时str.size()==0，因为第一个字符到第一个换行符之间有0个字符，换行符被吃掉
```

#### stringstream

可以把流想成一个队列

| 方法                      | 含义                         |
| ------------------------- | ---------------------------- |
| stringstream ss(string s) | 用字符串s构造stringstream    |
| ss.str()                  | 返回stringstream中的字符串   |
| ss << s                   | 将字符串s加入stringstream ss |
| ss >> s                   | 输出流数据到s，不消耗流      |

**注意适时清空stringsteam，因为输出不会消耗stringstream！**



#### 排序算法的cmp

cmp为一个`less` 函数，理解：判断`a...b`中元素a、b大小，如果`less(a,b)`则不交换

所以整个已序数组从宏观上来说一定是**升序序列**

#### lambda函数

```c++
[](auto p) -> bool {
  ...
  return true;
}
```

#### char转string

```c++
//使用to_string 方法会转化为char对应的ascii码
//原因是 to_string 没有接受char型参数的函数原型
//会先将char隐式转换为为int 型的ascii 码，再调用 to_string(int x)

cout << to_string('A') << endl;
//输出65

//转换方法：
string s(1,'A');
```

#### 范围for循环

```c++
for(auto x : vec) {...}
```

这里的元素x为拷贝而来，如果想避免拷贝则声明为如下：

```c++
for(const auto& x : vec) {...}
```

### 操作符重载

操作符中改变并返回自己的操作符 (+=、++等) 不加const且返回引用

不改变自己的操作符加const且返回拷贝

```c++
struct Time {
  // 数据
  int hh, mm, ss;
  // 构造函数
  Time(string s="00:00:00") { 
    hh=stoi(s.substr(0,2));
    mm=stoi(s.substr(3,2));
    ss=stoi(s.substr(6));
  }
  Time(int _hh, int _mm, int _ss):hh(_hh),mm(_mm),ss(_ss) {}
  
  // =================比较运算===================
  bool operator<(const Time& rhs) const {
    if(hh != rhs.hh) return hh<rhs.hh;
    else if(mm != rhs.mm) return mm<rhs.mm;
    else return ss < rhs.ss;
  }
  // 以下比较均基于小于，注意所有比较符号均需要const
  bool operator>(const Time& rhs) const {
    return rhs < *this;
  }
  bool operator<=(const Time& rhs) const {
    return !(*this > rhs);
  }
  bool operator>=(const Time& rhs) const {
    return !(*this < rhs);
  }
  bool operator==(const Time& rhs) const {
    return *this<=rhs && *this>=rhs;
  }
  bool operator!=(const Time& rhs) const {
    return !(*this==rhs);
  }
  // =================运算符===================
  Time& operator+=(const Time& rhs) { 
    // 注意没有const，返回的是引用
    hh+=rhs.hh; mm+=rhs.mm; ss+=rhs.ss;
    return *this;
  }
  // 用+=实现加法
  Time operator+(const Time& rhs) const {
    // 注意需要加const，返回拷贝
    Time tmp = *this; // 定义一个临时对象返回加法结果
    return tmp+=rhs;
  }
  Time operator-() const { // 重载负号
    // 注意需要const，返回拷贝
    return Time(-hh,-mm,-ss);
  }
  // =================自增自减运算符===================
  Time& operator++() { // ++Time
    自增;
    return *this;
  }
  Time operator++(int) { // Time++
    Time tmp = *this;
    ++*this; // 用前置++实现
    return tmp; // 返回临时变量
  }
}
```

#### 其他基本函数重载

拷贝构造函数、拷贝复制函数、移动函数、析构函数等一般编译器自动合成的就够用
（对于无指针数据的类型）

##### 拷贝构造函数

在函数传参、函数返回值、范围for循环等会自动调用。

```c++
Time(const Time& rhs);
```

##### 拷贝赋值函数

在对象初始化以后调用=赋值时调用。

```c++
Time& operator=(const Time& rhs);
```

