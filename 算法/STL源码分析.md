# STL源码分析

## 容器

### hashtable

是`unorderedset/unorderedmultiset`、`unorderedmap/unorderedmultimap`的核心类。核心容器为`vector`类的一个桶(bucket)，桶的大小动态扩充，从素数表中查找。采用开链法解决碰撞问题，桶中存指向节点(node)的指针，节点中存具体元素。通过把键值(key)转换为`hashnumber`来存放节点，通过`hashnumber`直接查找出节点。

![hashtable](/Users/guosongnan/Desktop/working/notes/pic/hashtable.png)

#### 节点

存储泛型类型`value`和下一指向下一节点指针`next`，

其中`value`可以是单一值（unorderedset节点），可以是pair（unorderedmap节点）

> 当value是pair时，STL内部实现了以pair.first元素作为hashkey的代码

```c++
// hashtable 的节点定义
template <class T>
struct hashtable_node
{
  hashtable_node* next;   // 指向下一个节点
  T               value;  // 储存实值
  // 略...
};
```

#### hashfunction

对于大部分基本类型（如整型、bool、char等）hashfunction直接返回原值，哈希值为原值。

对于浮点数或`string`类型，逐位哈希

```c++
// unordered_set 类型定义
template< class Key,
    class Hash = std::hash<Key>,
    class KeyEqual = std::equal_to<Key>,
    class Allocator = std::allocator<Key>
> class unordered_set;
```

定义自己的哈希函数：（需要同时定义`equal`）

注：`equal`会影响查找操作

```c++
// hashfunction
struct Myhash {
 	size_t operator()(const T& val) {
    return ...;
  }
}
// equal
// 1. 重载==
struct T {
  ...
  bool operator==(const T& rhs) const { ... }
}
// 2. 定义equal类
struct Myequal {
  bool operator()(const T& lhs, const T& rhs) const {...}
}

// 调用，若自定义类没重载==则要传入equal函数
unordered_set<T, Myhash, Myequal> st; 
```



#### 一些函数

##### find

时间复杂度O(1)

若不存在时返回`end()`

```c++
template <class T, class Hash, class KeyEqual>
typename hashtable<T, Hash, KeyEqual>::iterator
hashtable<T, Hash, KeyEqual>::
find(const key_type& key)
{
  const auto n = hash(key); // hashkey
  node_ptr first = buckets_[n];
  for (; first && !is_equal(value_traits::get_key(first->value), key); first = first->next) {}
  // 若不存在，first为nullptr，则与end相等(也为nullptr)
  return iterator(first, this); 
}
```

##### insert

时间复杂度：O(1)

```c++
// 插入元素，键值不允许重复
pair<iterator, bool> insert_unique(const value_type& value)
{
  rehash_if_need(1); // 若空间不够则扩充空间
  return insert_unique_noresize(value); // 不管空间直接插入
}

// 不管空间直接插入，返回pair<元素位置, 是否插入成功>
template <class T, class Hash, class KeyEqual>
  pair<typename hashtable<T, Hash, KeyEqual>::iterator, bool>
    hashtable<T, Hash, KeyEqual>::
insert_unique_noresize(const value_type& value)
{
  const auto n = hash(value_traits::get_key(value)); // hashkey
  // 开链法插入
  auto first = buckets_[n];
  for (auto cur = first; cur; cur = cur->next)
  {
    if (is_equal(value_traits::get_key(cur->value), value_traits::get_key(value)))
      return mystl::make_pair(iterator(cur, this), false);
  }
  // 头插入
  auto tmp = create_node(value);  
  tmp->next = first;
  buckets_[n] = tmp;
  ++size_;
  return mystl::make_pair(iterator(tmp, this), true);
}
```

### unordered_set

#### 结构

相当于集合set，元素不重复，可以O(1)时间内访问、插入值

### unordered_map

相当于`特殊值作为索引的vector`，但其中元素的顺序不确定

可以实现O(1)时间查找、插入值

Eg. `string`作为索引，值为`int`

![unordered_map1](/Users/guosongnan/Desktop/working/notes/pic/unordered_map1.png)

#### 函数

##### 下标[]操作符

若键存在则返回其值的引用，若不存在则插入键值对，值为默认构造函数，返回值的引用

```c++
  mapped_type& operator[](key_type&& key)
  {
    iterator it = ht_.find(key);
    if (it.node == nullptr)
      it = ht_.emplace_unique(mystl::move(key), T{}).first;
    return it->second;
  }
```

### unordered_multimap

允许key值重复的`hashmap`，每个值中存放的元素顺序不确定

![unordered_multimap](/Users/guosongnan/Desktop/working/notes/pic/unordered_multimap.png)

### unordered_multiset

别用

