
### char转string

```c++
//使用to_string 方法会转化为char对应的ascii码
//原因是 to_string 没有接受char型参数的函数原型，有一个参数类型
//为int 的函数原型，所以传入char型字符 实际是先将char 转化
//为int 型的ascii 码，然后再转变为string

cout << to_string('A') << endl;
//输出65

//转换方法：
char c = 'A';
string s(1,c);
```

