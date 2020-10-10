# javaScript 笔记

## jQuery

jQuery运行在dom检测完而图片未加载时

多个入口函数会顺序执行

### p7

```javascript
$( // 1. 接收一个函数，作为入口函数
  function() {
    // 2. 接收一个字符串选择器，返回jQuery对象，其中包含DOM元素
    let $box1 = $(".box1");
    let $box2 = $("#box2");
    // 3. 接收字符串代码，返回jQuery对象，包含创建的DOM元素
    let $p = $("<p>.....</p>");
    // 4. 接收DOM元素(数组)，返回jQuery对象，包装了这个DOM元素(数组)
    let span = document.getElementsByTagName("span"); // 一组span
    let $span = $(span);
  }
);
```

### p9-p12

```javascript
// 遍历对象执行操作，返回数组对象，可以遍历伪数组
$.each(arr, function(index, value) {
  
});

// 遍历对象执行操作，生成并返回新数组，若不返回则返回空数组
$.map(arr, function(value, index) {
  return value+1;
});
```

```javascript
// 去除字符串两端的空格
$.trim(str); 
// 
$.isWindow()
$.isArray()
$.isFunction()
```

```javascript
$.holdReady(true);  // 入口函数等待
$.holdReady(false); // 入口函数等待结束
```



## Vue.js

#### html属性

##### `v-text`

```html
<h2 v-text="message"> </h2> // 替换标签内容
<script>
	let app = new Vue({
    el: "h2",
    data: {
      message: "hello vue!"
    }
  })
</script>
```

##### `v-html`

```html
<h2 v-html="content" ></h2> // 用html代码替换
```

##### `v-on/@`

```html
<div>
  <input type="button" value="绑定" v-on:click="do">
	<input type="button" value="绑定" @click="do">
</div>
<script>
	let app = new Vue({
    el: "div",
    methods: {
      do: function() {}
    }
  })
</script>
```

##### 计数器实例

```html
    <div id="counter">
        <button @click="minus">-</button>
        <span>{{ num }}</span>
        <button @click="plus">+</button>
    </div>
    <script>
        let app = new Vue({
            el: "#counter",
            data: {
                num: 0
            },
            methods: {
                minus: function() {
                    if(this.num <= 0) return;
                    this.num--;
                },
                plus: function() {
                    if(this.num >= 10) return;
                    this.num++;
                }
            }
        })
    </script>
```

##### `v-show`

```html
<img v-show="isShow">
<script>
	let app = new Vue({
    el: "img",
    data: {
      isShow: false // 可以动态更改是否显示，本质是切换display属性
    }
  }) 
</script>
```

##### `v-if`

```html
<div v-if="isShow"></div> // 是否显示元素，本质是直接加或去除元素
```

##### `v-bind`

```html
<img v-bind:src="imgSrc">
<img :class="{active:isActive}"> // 简写，若isActive=true，则class="active"
```

##### `v-for`

```html
<div>
  <ul> // 根据数组生成列表
    <li v-for="(item, index) in arr">{{ index }}{{ item }}</li>
  </ul>
</div>
<script>
  let app = new Vue({
    el: "div",
    data: {
      arr: [1,2,3,4],
    }
  })
</script>
```

##### `v-model`

```html
<input type="text" v-model="message"> // 输入与数据同步更新
```



