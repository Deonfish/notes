# html

```html
<!DOCTYPE html>  <!--html5-->
<html lang="en"> <!--提示浏览器为英文-->
<head>
    <meta charset="UTF-8"><!--字符集-->
</head>
</html>
```

`<div>`独占一行

`<span>`不独占一行

​	`<a>`

```html
<!--_blank为在新页面打开-->
<a href="跳转链接" target="_self(默认)/_blank"> xxxx </a>

<!--空链接-->
<a href="#">xxx</a>

<!--下载链接（文件,压缩包)-->
<a href="file.zip">xxx</a>

<!--图片上加超链接-->
<a href="xxx.html"><img src="img.jpg"/></a>

<!--锚点链接-->
<a href="#point">xxx</a>
<h3 id="point">.......</h3> <!--锚点-->
```

表格

```html
<!-- 
tr:一行，th:表头单元格，td:单元格
thead:表头区域，tbody:表单区域
-->
<table>
  <thead>
  <tr> <th>name</th> <th>job</th> </tr>
  </thead>
  <tbody>
  <tr> <td>james</td> <td>player</td> </tr>
  <tr> <td colspan="2">xxx</td></tr> <!--跨列合并单元格-->
  </tbody>
</table>
```

列表

```html
<!--无序列表-->
<ul>
  <li>xxx</li>
  <li>xxx</li>
</ul>
<!--有序列表-->
<ol>
  <li>xxx</li>
  <li>xxx</li>
</ol>
<!--自定义列表-->
<dl>
  <dt>名词</dt>
  <dd>解释1</dd>
  <dd>解释2</dd>
</dl>
```

表单

```html
<form> <!--表单域-->
  name: <input type="text" name="name" value="输入用户名"> <br/>
  password: <input type="password" name="password"> <br/>
  <!--单选按钮-->
  select: 1 <input type="radio" name="s1" checked="checked"> 2 <input type="radio" name="s1"> <br/>
  <!--多选按钮-->
  select: 1 <input type="checkbox" name="s2"> 2 <input type="checkbox" name="s2"> <br/>
  <!--提交按钮-->
  <input type="submit" value="submit">
  <!--重置按钮-->
  <input type="reset" value="reset"> <br/>
  <!--普通按钮 结合js使用-->
  <input type="button" value="获取验证码">
  <!--文件上传-->
  <input type="file" value="上传文件">
  <!--label 点击文字即可选中表单-->
  <input type="radio" id="male"> <label for="male">男</label>
</form>
```

`checked="checked"`用于单选/复选按钮，设置默认值

```html
籍贯:
<form>
  <select>
    <option selected="selected">山东</option> <!--默认选中-->
    <option>河北</option>
  </select>
</form>
```

```html
<form>
  留言:
  <textarea>
    默认留言
  </textarea>
</form>
```

# CSS

多类名

```html
<div class="red font20">xxx</div>
```

字体复合属性

```css
* {
	/* font: font-style font-weight font-size/line-height font-family; */
  /* font-weight: 700/bold:加粗,400/normal:不加粗 */
  font: italic 700 16px 'Microsoft yahei'; 
  /*font-size和font-family不可省略*/
  font: 20px 'Microsoft yahei';
}
```

```css
* {
	color: red; /* 字体颜色 */
  text-align: center; /* 文字对齐(居中于盒子) */
  text-decoration: underline/none; /* 下划线/不要下划线 */
  text-indent: 2em; /* 首行锁进(em为当前元素大小) */
  line-height: 20px; /* 行高 */
}
```

复合选择器

```css
/* 后代选择器 */
.xx li { /* 选择xx类后代中所有的li */
}
/* 子选择器 */
ol > li { /* 选择ol的直接孩子中的li */
}
/*  并集选择器 */
p, div {
}
/* 伪类选择器 */
a:link 		/* 选择所有未被访问标签 */
a:visited /* 选择所有已被访问标签 */
a:hover 	/* 选择鼠标悬停的标签 */
a:active  /* 选择被点击的标签 */
a { color:gray;} /* 开发中常用写法 */
a:hover {color:red;}

input:focus { /* 选择被选中的表单元素 */
  background-color: blue;
}
```

#### 元素显示模式

- 块级元素：

`<h1>, <p>, <div>, <ul>, <table>, <form>`

独占一行，可以设置高度宽度等，可容纳行内元素或块级元素

- 行内元素：

`<span>`

相邻元素显示在一行，不可设置高度宽度，默认为元素本身高/宽，行内元素只能容纳文本或其他行内元素

特别的：`<a>`中可放块级元素

- 行内块元素

`<img/>, <input/> <td>`

相邻元素显示在一行，默认宽度为元素本身宽度，高/宽等可以控制



显示模式转换

```css
a {
  width: 150px;
  height: 50px;
  display: block; /* 行内元素转换为块级元素，可以设置高/宽 */
}
<a href="#">xxx</a>

div {
  display: inline; /* 块级元素转换为行内元素 */
}
<div>xxx</div>

span {
  width: 100px;
  height: 30px;
  display:inline-block; /* 转换为行内块元素 */
}
```

文字垂直居中

```css
a {
  height: 40px;
  line-height: 40px; /* 行高和高度一致 */
}
```

背景图片

```css
div {
  width: 300px;
  height: 300px;
  background-color: rgba(0,0,0,0.4) /* 背景颜色半透明 */
  background-image: url(image.png);
  background-position: center center; /* 背景图片位置 */
  background-attachment: fixed/scroll(默认); /* 图片固定不滚动 */
}
/* 背景属性复合写法 */
div {
  /* 背景颜色 图片地址 平铺 滚动 背景图片位置 */
  background: transparent url(img.png) no-repeat fixed center top;
}
```

#### css三大特性

- 层叠特性

  相同选择器样式冲突，就近原则

- 继承性

  子元素继承父元素的样式(text-, font-, line- , color)

```css
body {
  font: 12px/1.5 'Microsoft YaHei'; /* 行高为当前元素的1.5倍 */
}
p {
  font-size: 16px; /* 继承得来的行高为1.5倍字体大小 */
}
```

- 优先级

  不同选择器有优先级

  权重叠加，可以叠加不会进位

  ```css
  ul li{ } /* 权重为0001+0001=2 */
  li { }   /* 权重为0001 */
  ```



边框

```css
div {
  border-width: 1px;									/* 边框宽度 */
  border-style: solid/dashed/dotted;  /* 边框样式 */
  border-color: red;									/* 边框颜色 */
  /* 边框复合写法，无序 */
  border: 1px solid red; 
  /* 上边框 根据就近原则会覆盖上面的border */
  border-top: 1px solid black;
}

/* 表格边框 */
table, td, th {
  border: 1px solid pink;
  border-collapse: collapse; /*相邻边框重叠*/
}
```

边框会拓宽盒子的大小

```css
/*padding*/
div {
  padding: 5px;							/* 上下左右 */
  padding: 5px 5px;					/* 上下 左右 */
  padding: 5px 5px 5px;			/* 上 左右 下 */
  padding: 5px 5px 5px 5px;
}
```

padding也会拓宽盒子的大小，若无`width/height`属性则对应方向不会拓宽，会直接继承父元素的高/宽

```css
/*css*/
div {
  margin: ...; /* 与padding一致 */
  margin: 0 auto; /* 左右居中显示 */
  text-align: center; /* 子行内元素或行内块元素居中显示 */
}
```

嵌套元素外边距塌陷

```css
/* 1.为父元素定义边框 */
.father {
  width: 400px;
  height: 400px;
  margin-top:50px;
  border: 1px solid transparent;
}
.son {
  width: 200px;
  height: 200px;
  margin-top: 100px;
}
/* 2. 为父元素添加内边距 */
/* 3. 为父元素添加 overflow:hidden */
```

清除边距

```css
* {
  padding: 0;
  margin: 0;
}
```

行内元素尽量只设置左右外边距（设置上下也不起作用）

```css
/* 盒子圆角 */
div {
  border-radius: 10px; /* 圆角边框 */
  border-radius: 50%;  /* 圆矩形 */
  border-radius: 10px 10px 10px 10px; /* 四个角 */
}
/* 盒子阴影 */
div {
  /* h-shadow(必须) v-shadow(必须) blur spread color inset */
  box-shadow: 10px 10px 10px 10px rgba(0,0,0,.3);
}
```

### 浮动

三种传统网页布局方式

- 普通流（标准流）
  块级元素，行级元素按默认方式排列
- 浮动
  多个块级元素横向排列
- 定位

浮动特点

- 脱离标准流，不保留原位置
- 浮动的盒子顶端对齐排列，若父元素装不下盒子则另起一行顶端对齐
- 浮动盒子有行内块特点，默认宽度根据内容决定

浮动元素常常搭配标准流父级使用

浮动注意点：

一个盒子浮动，其他兄弟盒子也应该浮动（否则会出现问题）

浮动的盒子只会影响盒子后面的标准流，不影响之前的

#### 清除浮动

- 额外标签法

```html
<div class="box">
  <div>xxx</div>
  <div>xxx</div>
  <div style="clear:both"></div> <!--必须是块级元素-->
</div>
```

- 父元素添加 overflow
  缺点：无法显示溢出部分

```css
.box {overflow:hidden;}
```

- :after伪元素清除

```css
.clearfix:after { /* 父元素处添加 */
  content: "";
  display: block;
  height: 0;
  clear:both;
  visibility: hidden;
}
.clearfix { /* IE6,7 */
  *zoom: 1;
}

/* 双端清除 */
.clearfix:before,
.clearfix:after {
  content: "";
  display: table;
}
.clearfix:after {
  clear: both;
}
.clearfix {
  *zoom: 1;
}
```

> 父元素与子元素位置/大小关系：
>
> 若父元素不设置宽度/高度，子元素会撑大父元素
>
> 若子元素仅设置高/宽，另一项会跟随父元素，且跟随的那个属性padding不会向外扩展
>
> 子元素的浮动是定义在父元素内的

### 定位

- 静态定位

- 相对定位 relative

相对于自己原来的位置，不脱离标准流，下面的盒子还保持原来的位置

- 绝对定位 absolute

相对于有祖先元素的位置，若无祖先元素或祖先无定位则以浏览器边框为标准
若祖先有定位，则参照最近一级有定位的祖先

不占有位置，脱离标准流

- 固定定位 fixed

以浏览器的可视窗口为标准

```css
.fixed {
  position: fixed;
  left: 50%;
  margin-left: 版心宽度/2;
}
```

- 粘性定位 sticky

```css
.sticky {
  position: sticky;
  top: 0px;
}
```

#### 定位特点

定位叠放顺序

```css
z-index: 1; /* 默认为0 */
```

属性越大越考上，属性相同时书写顺序靠下的在上

定位居中

```css
.div {
  position: absolute;
  left: 50%;
  margin-left: -宽度/2;
  top: 50%;
  margin-top: -宽度/2;
}
```

- 行内元素定位后可设置高度，宽度

- 块级元素定位后高宽默认为内容大小

- 脱标的盒子不会触发外边距塌陷
- 浮动元素只会压住标准流下的盒子，不会压住文字
  绝对定位会压住下面标准流所有内容

#### 总结

盒子上下排列，用标准流布局

盒子左右排列，用浮动布局

元素在某个盒子内移动，覆盖，用定位布局



```css
div {
  display: none/block; /* 隐藏对象，不保留位置 */
  visibility: hidden/visible; /* 隐藏对象，保留位置 */
  overflow: hidden/visible; /* 隐藏溢出的内容 */
  overflow: scroll; /* 溢出部分显示滚动条 */
  overflow: auto; /* 溢出时显示滚动条，不溢出不显示滚动条 */
}
```

三角制作

```css
.box {
  width: 0; /* 高度宽度必须是0 */
  height: 0;
  border: 10px solid transparent;
  border-top-color: pink;
}

.block {
  position: relative;
  width: 120px;
  height: 220px;
  background-color: pink;
}
.block span {
  position: absolute;
  right: 15px;
  top: -10px;
  width: 0;
  height: 0;
  /* 照顾兼容性 */
  line-height: 0;
  font-size:0;
  border: 5px solid transparent;
  border-bottom-color: pink;
}

<div class="block">
	<span></span>
</div>
```

鼠标样式

```css
div {
  cursor: default;
  cursor: pointer;
  cursor: move;
  cursor: text;
  cursor: not-allowed;
}
```

轮廓线

```css
input { /* 取消表单轮廓线 */
  outline: none;
}
```

文本域取消大小可变

```css
textarea {
  resize: none;
  outline: none; /* 也可以 */
}
```

垂直居中对齐

```css
img { /* 行内块元素可添加，图片和旁边的文字垂直对齐 */
  vertical-align: top;
  vertical-align: middle;
	vertical-align: bottom;
}
```

图片下白边消除

```css
/* 1.对齐 */
div { border: 2px solid red; }
img { vertical-align: nottom; } /* 消除白边 */
/* 2.转换为块级元素 */
img { display: block; }
<div>
	<img src=".."/>
</div>
```

溢出文字用省略号显示

```css
/* 单行文字 */
div {
  white-space: nowrap;      /* 文字不允许换行 */
  overflow: hidden;					/* 溢出隐藏 */
  text-overflow: ellipsis;  /* 溢出显示省略号 */
}
/* 多行文字,注意要控制盒子高宽 */
div {
  overflow: hidden;
  text-overflow: ellipsis;
  /* 适用于web-kit内核 */
  display: -webkit-box; /* 显示为弹性伸缩盒子模型 */
  -webkit-line-clamp: 3; /* 显示文本行数 */
  -webkit-box-orient: vertical; /* 子元素排列方式 */
}
```

#### 布局技巧

```css
/* 消除重叠边框 */
ul li {
  float: left;
  width: 150px;
  height: 200px;
  border: 1px solid red;
  margin-left: -1px; /* 消除边框 */
}
<ul>
	<li></li>
	<li></li>
</ul>

/* 悬浮出现边框 */
ul li:hover { /* 盒子没有定位 */
  position: relative;
  border: 1px solid blue;
}
ul li:hover {
  z-index: 1;
  border: 1px solid blue;
}
```

```css
/* 三角形 */
.box {
  width: 0;
  height: 0;
  border-top: 100px solid transparent;
  border-right: 50px solid skyblue;
  border-bottom: 0 solid blue;
  border-left: 0 solid blue;
}
```

```html
<!--利用三角制作矩形块-->
<style>
  .price {
    width: 160px;
    height: 24px;
    line-height: 24px
    border: 1px solid red;
    margin: 0 auto;
  }
  .miaosha {
    position: reletive;
    float:left;
    width: 90px;
    height: 100%;
    background-color: red;
    text-align: center;
    color: #fff;
    font-weight: 700;
  }
  .miaosha i { /* i标签专门做三角 */
    position: absolute;
    right:0;
    top:0;
    width: 0;
    height: 0;
    border-color: transparent #fff transparent transparent;
    border-style: solid;
    border-width: 24px 10px 0 0;
  }
</style>

<div class="price">
  <span class="miaosha">
    $1650
    <i></i>
  </span>
  <span>¥5650</span>
</div>
```



## 新特性

### html5

- `<header>` 头部标签
- `<nav>` 导航标签
- `<article>` 内容标签
- `<section>` 定义文档某个区域
- `<aside>` 侧边栏标签
- `<footer>` 尾部标签

（IE9中需要把这些元素转换为块级标签）

#### 视频和音频

```html
<video src="..." controls="controls" ></video>
```

#### 表单

```html
<input type="email/number/search/..." required="required" placeholder="提示信息" />
```

### css3

#### 属性选择器

#### 结构伪类选择器

| 选择器                         | 含义                                                  |
| ------------------------------ | ----------------------------------------------------- |
| E : first-child/last-child     | 选择E元素的第一个/最后一个孩子                        |
| E : nth-child(...)             | 选择E元素的第n个子元素(n可以为数字/公式/odd/even)     |
| E : nth-child(n/2n/n+5/-n+5)   | (n从0开始递增) 所有 / 偶数 / 第5个及以后所有 / 前五个 |
| E : first-of-type/last-of-type | 选择E元素的第一个/最后一个孩子                        |
| E : nth-of-type(...)           | 选择E元素的第n个子元素                                |
| 结构选择器部分(冒号以后)       | 权重为10                                              |

```css
ul li:first-child {
  /* 选择ul的第一个是li的孩子，第一个元素不是li则不选 */
}
ul li:first-of-type {
  /* 选择ul的孩子中是li的第一个元素 */
}
```

#### 伪元素选择器

利用css创建html标签

（css2写法为单冒号`:`）

| 选择符     | 简介                     |
| ---------- | ------------------------ |
| `::before` | 在元素内部的前面插入元素 |
| `::after`  | 在元素内部的后面插入元素 |

插入的元素为行内元素，必须有`content`，权重和标签选择器一样为1

```html
<!--鼠标悬浮变图片暗效果-->
<style>
  .box {...}
  .box img {...}
  .box::before {
    content: '';
    display: none;
    position: absolute;
    top: 0;
    left: 0;
    width: 100%;
    height: 100%;
    background-color: rgb(0,0,0, .4);
  }
  .box:hover ::before {
    display: block;
  }
</style>

<div class="box">
  <img src="..." >
</div>
```

```css
/* 清除浮动 */
.clearfix:after {
  content: '';
  display: block;
  height: 0;
  clear:both;
  visibility: hidden;
}
/* 第二种清除浮动 */
.clearfix:before, .clearfix:after {
  content: '';
  display: table;
}
.clearfix:after {
  clear: both;
}
```

#### css3 盒子模型

| 模型                     | 含义                                    |
| ------------------------ | --------------------------------------- |
| box-sizing : content-box | 旧盒子                                  |
| box-sizing : border-box  | 定宽度盒子，padding和border不会撑大盒子 |

#### 其他

`calc() `

```css
div {
  width: calc(100%-80px); /* 支持公式 */
}
```

#### 过渡

`transition: 变化的属性 花费时间 运动曲线 何时开始`

哪个元素变化给哪个元素加`transition`

运动曲线默认 ease，何时开始默认0s

```html
<style>
  div {
    width: 200px;
    height: 100px;
    background-color: pink;
    transition: width .5s, height .5s; /* 多个属性变化 */
    transition: all .5s; /* 所有属性变化 */
  }
  div:hover {
    width: 400px;
    height: 200px;
  }
</style>

<div>
</div>
```

