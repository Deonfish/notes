
## C-Style

### ctype

| 函数               | 功能                                    |
| ------------------ | --------------------------------------- |
| int isalnum(int c) | 判断一个字符是否为英文字母或数字        |
| int isalpha(int c) | 检查所传的字符是否是字母                |
| int islower(int c) | 检查所传的字符是否是小写字母            |
| int isupper(int c) | 检查所传的字符是否是大写字母            |
| int isdigit(int c) | 检查所传的字符是否为阿拉伯数字0 到9     |
| int isspace(int c) | 检查所传的字符是否是空格字符(空格、tab) |
| int tolower(int c) | 把大写字母转换为小写字母                |
| int toupper(int c) | 把小写字母转换为大写字母                |

### math

| 函数                                   | 功能                                                         |
| -------------------------------------- | ------------------------------------------------------------ |
| double modf(double x, double *integer) | 返回值为小数部分（小数点后的部分），并设置 integer 为整数部分 |
| double pow(double x, double y)         | 返回 x 的 y 次幂                                             |
| double sqrt(double x)                  | 返回大于或等于 x 的最小的整数值                              |
| double ceil(double x)                  | 返回大于或等于 x 的最小的整数值                              |
| double floor(double x)                 | 返回小于或等于 x 的最大的整数值                              |

### stdlib

| 函数                           | 功能                                        |
| ------------------------------ | ------------------------------------------- |
| double atof(const char *str)   | 把字符串str转换为浮点数(double)             |
| int atoi(const char *str)      | 把字符串str转换为整数(int)                  |
| long int atol(const char *str) | 把字符串str转换为整数(long)                 |
| int abs(int x)                 | 返回 x 的绝对值                             |
| int rand(void)                 | 返回一个范围在 0 到 RAND_MAX 之间的伪随机数 |
| void srand(unsigned int seed)  | 该函数播种由函数 rand 使用的随机数发生器    |

### stdio

| 函数                        | 功能                                                         |
| --------------------------- | ------------------------------------------------------------ |
| int sprintf(str, "%d", num) | 把num内容以流形式输入到str                                   |
| int sscanf(str, "%d", &num) | 把str内容以流的形式输入到num                                 |
| int getchar(void)           | 从标准输入 stdin 获取一个字符（一个无符号字符）              |
| int putchar(int char)       | 把参数 char 指定的字符（一个无符号字符）写入到标准输出 stdout 中 |

### string

| 函数                                                     | 功能                                                         |
| -------------------------------------------------------- | ------------------------------------------------------------ |
| int memcmp(const void *str1, const void *str2, size_t n) | 比较前n个字符，字典序，相同返回0，str1                       |
| void* memcpy(void *dest, const void *src, size_t n)      | 从 src 复制 n 个字符到 dest                                  |
| void *memset(void *str, int c, size_t n)                 | 复制字符                                                     |
| char *strcat(char *dest, const char *src)                | 把 src 所指向的字符串追加到 dest 所指向的字符串的结尾        |
| char *strncat(char *dest, const char *src, size_t n)     | 把 src 所指向的字符串追加到 dest 所指向的字符串的结尾，直到 n 字符长度为止 |
| int strcmp(const char *str1, const char *str2)           | 把 str1 所指向的字符串和 str2 所指向的字符串进行比较         |

---

### ctime

| 类      | 功能 |
| :------ | ---- |
| clock_t |      |
| time_t  |      |
| tm      |      |

#### 函数

| 函数                        | 功能 |
| --------------------------- | ---- |
| time_t time(time_t \*time); |      |

####代码

```c++
//计算时间间隔(s)
clock_t start, end;
start = clock();
for (int i = 0; i < 1000; i++) cout << "*";
cout << endl;
end = clock();
cout << "Time used: " << ((double)(end - start)) / CLOCKS_PER_SEC << endl;
```



---



## C++

### string

`npos`:以字符串子集为参数的函数以 npos 为“所有到达终点的方式”指示器

##### 构造函数

| 函数                     | 功能                              |
| ------------------------ | --------------------------------- |
| string(str)              | 生成str的复制品                   |
| string(str, pos)         | 生成pos开头到结尾的字符串         |
| string(str, pos, strlen) | 生成pos开头，长度为strlen的字符串 |
| string(cstr)             | 生成c风格字符串的复制品           |
| string(cstr, cstrlen)    | 生成cstr [0, cstrlen)的字符串     |
| string(num, c)           | 生成包含num个c字符的串            |
| string(beg, end)         | 生成[beg, end) 的字符串           |

##### 元素访问

| 函数       | 功能                                                         |
| ---------- | ------------------------------------------------------------ |
| operator[] |                                                              |
| front      |                                                              |
| back       |                                                              |
| c_str      | 返回指向`c字符串`的`临时指针`【注】与`strcpy(cstr,s.c_str());`搭配使用 |

##### 操作

| 函数                                                         | 操作                       |
| ------------------------------------------------------------ | -------------------------- |
| clear, push_back, pop_back, operator+=(后附字符到结尾)， resize |                            |
| insert                                                       | (见下文重载)               |
| erase                                                        | (见下文重载)               |
| replace, copy, swap                                          | （不用）                   |
| substr(pos = 0, count = npos)                                | 返回[pos, pos+count)的子串 |
| getline(istream, string)                                     | 读取一行                   |

*insert*

```c++
str.insert(index, count, char ch)			在index处插入count个字符ch
str.insert(index, cstr)						在index处插入c字符串cstr
str.insert(index, cstr, count)				在index处插入cstr的[0,count)子串
str.insert(index, str)						在index处插入str（c++字符串）
str.insert(index, str, index_str, count)	在index处插入str.substr(index_str, count);子串
str.insert(iterator pos(属于str的迭代器）, first, last)		在迭代器pos处插入[first, last)的子串	
```

*erase*

```
str.erase(index)							擦除[index, end)
str.erase(iterator pos)						擦除pos位置的字符
str.erase(iterator first, iterator last)	擦除[first, last)
```

##### 查找

| 函数                                                       | 功能                                       |
| ---------------------------------------------------------- | ------------------------------------------ |
| size_type find(str/cstr/ch, pos, count) ; find_first_of( ) | 寻找`字符串/字符`从pos开始第一次出现的位置 |
| size_type rfind(str/cstr/ch, pos, count) ; find_last_of( ) | 最后一次出现的位置                         |

> 若不存在则返回`npos`(整型最大值)
>
> 返回的是size_type(无符号整数)类型

##### 非成员函数

`operator+`

##### 数值转换

| 函数                             | 功能                      |
| -------------------------------- | ------------------------- |
| stoi; stol; stoll (str, pos = 0) | 字符串转换为整数          |
| stof; stod; stold (str, pos = 0) | 字符串转换为浮点数        |
| to_string(value)                 | `整数/浮点数`转化为字符串 |



---



### vector

##### 构造函数

| 函数                       | 功能       |
| -------------------------- | ---------- |
| vector{1,2,3... } 初值列表 |            |
| vector(count)              |            |
| vector(count, value)       |            |
| vector(first, last)        | 迭代器构造 |
| vector(vector& other)      | 拷贝构造   |



### set

##### 构造函数

| 函数                    | 功能                      |
| ----------------------- | ------------------------- |
| set(first, last)        | 迭代器构造                |
| set(set& other)         | 拷贝构造                  |
| set {1,2,3...} 初值列表 | initializer_list 构造函数 |

##### 成员函数

| 函数           | 功能                |
| -------------- | ------------------- |
| st.insert(key) | 插入key值           |
| st.count(key)  | 返回key值个数(1或0) |
| st.find(key)   | 返回key值的迭代器   |



### map

##### 构造函数

默认构造函数 | 迭代器构造函数 | 拷贝构造函数 | initializer_list 构造函数

##### 成员函数

| 函数          | 功能                                                    |
| ------------- | ------------------------------------------------------- |
| operator[]    | 插入元素，若不存在元素则插入(r若无显式赋值则插入默认值) |
| mp.count(key) | 返回key个数(1或0)                                       |
| mp.find(key)  | 返回key键的迭代器                                       |

```c++
map<int, int> mp;
if(mp[1] == 2) cout << "yes\n";
//此时mp.size() = 1
//此时mp[1] = 0
//正确实现：
if(mp.count(1) != 0 && mp[1] == 2) cout << "yes\n";
//&&第一位判断false之后不执行的二位
```



### unordered_map

> 计数hash

##### 构造函数

默认构造函数 | 范围构造函数 | 复制构造函数 | initializer_list 构造函数

##### 成员函数

| 函数                               | 功能     |
| ---------------------------------- | -------- |
| mlmp.insert(pair/initializer_list) | 插入元素 |
| mlmp.count(key)                    |          |
| mlmp.find(key)                     |          |

要求重载`hash function`和`==符号`

```c++
template< class Key,
    class Hash = std::hash<Key>,
    class KeyEqual = std::equal_to<Key>,
    class Allocator = std::allocator<Key>
> class unordered_set;
```

```c++
#include <unordered_set>
struct Foo
{
    Foo(int _x = 0, string _id = ""): x(_x), id(_id) {}
    ~Foo() = default;
    int x;
    string id;
    bool operator==(const Foo& rhs) const
    { return x == rhs.x; }
};
struct hashFuc
{
    size_t operator()(const Foo& c) const
    { return c.x; }
};

unordered_set<Foo, hashFuc> hashTable;
```



### unorderd_multiset

> 允许多个值存在的set
>
> 计数hash
>
> 元素顺序随机（与插入顺序不同！）

##### 构造函数

默认构造函数 | 范围构造函数 | 复制构造函数 | initializer_list 构造函数

##### 成员函数

| 函数               | 功能     |
| ------------------ | -------- |
| mlst.insert(key)   | 插入元素 |
| mlst.count(key)    |          |
| mlst.find(key)     |          |
| mlst.contains(key) |          |

同上，要求重载`hash function`和`==符号`



#### map&set对比

> map与unordered_map对比：
>
> 用到排序特性时map更优，用到hash特性时unordered_map更优

```c++
//实现string hash
//unordered_map比map在实现hash上更快
map<string, int> mp{ {"a", 1}, {"b",2} };
cout << "mp:" << endl;
cout << mp["a"] << endl;
cout << mp["b"] << endl;
//
unordered_map<string, int> mp_hash{ {"a", 1}, {"b",2} };
cout << "mp hash:" << endl;
cout << mp_hash["a"] << endl;
cout << mp_hash["b"] << endl;
```

```c++
//单个key映射到多个value,实现按名hash
	struct values
	{
		string id, gender;
	};
map<string, values> mp{ {"sam", values{"123", "male"}}, {"lili", values{"222", "female"}} };
unordered_map<string, values> mp_hash{ {"sam", values{"123", "male"}}, {"lili", values{"222", "female"}} };

cout << "id= " << mp_hash["lili"].id << " gender= " << mp_hash["lili"].gender << endl;

```



### pair

构造pair

1. pair<int, string> (1, "ss");
2. make_pair(1, "ss");

元素访问：

pr.first, pr.second



---

### bitset

#### 构造函数

| 函数                        | 功能                    |
| --------------------------- | ----------------------- |
| bitset\<size> bs            | 长度`size`，每一位为`0` |
| bitset\<size>(string / int) |                         |

> 构造时，若参数比bitset的size短，则高位用0补充，若比bitset长，则截取低位

#### 成员函数

| 函数                    | 功能                         |
| ----------------------- | ---------------------------- |
| <<                      | 输出                         |
| ^,&,\|,<<,~             | 支持位运算                   |
| []                      | 下标访问/赋值元素，最低位为0 |
| bs.count()              | 返回bitset中1的个数          |
| bs.flip(void / offset)  | 所有位均取反 / offset位取反  |
| bs.set(void / offset)   | 所有位均取1 / offset取1      |
| bs.reset(void / offset) | 所有位均取0 / offset取0      |
| bs.to_string()          | 转换为字符串                 |
| bs.to_ulong()           | 转换位long                   |



---



### 输入输出



#### cin

cin在读取到`EOF`时会返回`false`，读取成功返回`true`

**cin.getline**

```c++
istream & getline(char* buf, int bufSize);
istream & getline(char* buf, int bufSize, char delim);
```



---



#### cout

**流操作算子**

| 算子                                    | 作用                                                         |
| --------------------------------------- | ------------------------------------------------------------ |
| dec (默认) / hex / oct                  | `十进制 / 十六进制 / 八进制` 输出整数                        |
| fixed (默认) / scientific               | `普通小数 / 科学计数法` 输出小数                             |
| right(默认) / left                      | `右对齐 / 左对齐`                                            |
| setbase(b)                              | 设置输出整数时的进制`b=8、10 或 16`                          |
| setw(w)                                 | 指定输出宽度为 w 个字符，或输人字符串时读入 w 个字符         |
| setfill(c)                              | 在指定输出宽度的情况下，输出的宽度不足用字符 c 填充（默认情况是用空格填充） |
| setprecision(n)                         | 设置输出浮点数的精度为 n                                     |
| setiosflags(flag) / resetiosflags(flag) | 将某个输出格式标志置为` 1 / 0`                               |
| ···                                     | ···                                                          |

**setiosflags算子**

| 算子                           | 功能                     |
| ------------------------------ | ------------------------ |
| ios::left / ios::right         | 左对齐 / 右对齐          |
| ios::dec / ios::oct / ios::hex | 十进制、八进制、十六进制 |
| ...上表算子前加ios::           | ...                      |



---



#### stringstream

> include \<sstream>

##### 构造函数

| 函数                 | 功能      |
| -------------------- | --------- |
| stringstream is(str) | str输入流 |
| stringstream is      |           |

##### 成员函数

| 函数        | 作用                     |
| ----------- | ------------------------ |
| is.str();   | is中的内容`以string返回` |
| is.str(""); | 清空stringstream中的内容 |
| is.clear(); | 清空stringstream中的状态 |

##### 代码

```c++
#include <sstream>
//注意每次重复使用stringstream都要清空状态和内容

string str = "1010"; int x;
stringstream ss(str);
ss >> x;
x /= 10;

//注意清空
ss.str("");
ss.clear();

ss << x;
cout << ss.str(); // 101
```





----



### 算法

`algorithm`

##### 不修改序列的操作

| 函数                                | 功能                             |
| ----------------------------------- | -------------------------------- |
| for_each(first, last, 可执行对象op) | 对[first, last)每个对象执行op    |
| for_each_n(first, n, 可执行对象op)  | 对[first, first+n)每个对象执行op |
| count/count_if(first, last, op)     | 返回符合op的对象个数             |
| find/find_if(fist, last, oj/op)     | 返回第一个等于oj或符合op的迭代器 |
| find_end, find_first_of             |                                  |

##### 修改序列的操作

| 函数                                                  | 功能                               |
| ----------------------------------------------------- | ---------------------------------- |
| copy, copy_n                                          |                                    |
| fill(first, last, value); fill_n(first, count, value) | 赋值value给[first, last)           |
| swap(&a, &b) (均是引用)                               | 交换元素                           |
| reverse(first, last)                                  | 反转元素                           |
| unique(first, last)                                   | 消除连续的重复元素，返回尾后迭代器 |

##### 排序

| 函数                         | 功能                         |
| ---------------------------- | ---------------------------- |
| is_sorted(first, last, comp) | 检查是否有序，可选用comp定序 |
| sort(first, last, comp)      |                              |

##### 二分操作

| 函数                            | 功能                                    |
| ------------------------------- | --------------------------------------- |
| lower_bound(first, last, value) | 返回指向第一个大于等于value的元素迭代器 |
| upper_bound(first, last, value) | 返回指向第一个大于给定值的元素的迭代器  |

##### 最大/最小操作

| 函数                                        | 功能                  |
| ------------------------------------------- | --------------------- |
| max/min(a, b)                               |                       |
| max/min_element(first, last)                | 寻找第一个最大元素    |
| equal(first1, last1, first2)                | 若范围内相等返回true  |
| max_element/min_element(first, second, cmp) | 返回序列的最大/最小值 |

---

`numeric`

| 函数                          | 功能                                     |
| ----------------------------- | ---------------------------------------- |
| iota(first, last, value)      | 用以value开始递增的元素填充[first, last) |
| accumulate(first, last, init) | 以init为初值累加[first, last)元素        |



---



### 正则表达式

```c++
#include <regex>
```

#### 类

##### regex

```c++
R"()"为原生字符，可以不写难以理解的"//"
regex reg(R"(expr)");
```

##### smatch

> match_results对于string类型的特化

```c++
smatch s;
s.str();	//返回匹配的字符串
s.str(1);	//返回第一个子表达式的字符串...以此类推，若无子表达式则返回空串
```

#### 函数

##### regex_match

> 完全匹配，字符串模式需与表达式完全一致，不识别串中符合表达式的子串

```c++
//返回bool值表示是否匹配
smatch m;
bool result = regex_match("string", m, regex("expr"));
```

##### regex_search

> 搜索字符串中符合匹配的子串

```c++
//返回bool值表示是否匹配
//把第一个符合匹配的结果存储入smatch对象中
smatch m;
bool result = regex_search("string", m, regex("expr"));
```

搜索所有匹配 - sregex_iterator

```c++
//空迭代器end_it指示终点
string s;
regex r("expr");
sregex_iterator it(s.begin(), s.end(), r), end_it;
for(; it != end_it; it++)
    cout << it->str() << endl;
```

分词 - sregex_token_iterator

```c++
//-1表示对正则表达式之前的子式感兴趣，若为0则匹配正则表达式
string s;
regex r("expr");
sregex_token_iterator it(s.begin(), s.end(), r, -1), end_it;
for(; it != end_it; it++)
    cout << it->str() << endl;
```


