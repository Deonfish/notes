# 常用算法技巧 in c++

### freopen

```c++
freopen("in.txt", "r", stdin);
```

### 寻找子串

```c++
// 寻找由','分割的字符串
for(int i = 0, j = 0; j < s.size(); ++j, i = j) // 跳过 ','
{
	while(j < s.size() && s[j] != ',') ++j; // 此时j指向末尾或 ','
  string substr = s.substr(i, j-i);
  // ...
}
```

