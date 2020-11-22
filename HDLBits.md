# HDLBits

## Verilog Language

### Basics

### Vectors

#### Vectors

`vector`可以用一个名字方便地表示一组信号。一个`vector`等价于若干条信号线(wire)

#### Vector in more detail

```verilog
output [3:0] a;  // 小端
wire [0:7] b;		 // 大端
```

verilog允许定义大端/小端的vector。

```verilog
wire [2:0] a, c;   // Two vectors
assign b = a; // 隐式wire类型
```

nets类型可能被assign语句隐式的创建，把``default_nettype`置为none可以避免这种情况。

```verilog
w[3:0]      // Only the lower 4 bits of w
x[0]        // The lowest bit of x
x[0:0]      // ...also the lowest bit of x
z[-1:-2]    // Two lowest bits of z
```

vector支持切片操作。

#### Bitwise operators

Bitwise vs. Logical Operators

按位运算：每位都参与运算（与或非等），两个n位数字运算得到n位二进制数

逻辑运算：一切非0数字当作1，两个n位数字运算得到0或1

#### vector concatenation operator

```verilog
assign {out[7:0], out[15:8]} = in;         
assign out[15:0] = {in[7:0], in[15:8]};  
```

`连接操作符`可以放在等号左边或右边

#### Replication operator

```verilog
input [7:0] in, output [31:0] out
assign out={{24{in[7]}},in};
```
有符号数位拓展电路（8位->32位）。

### Module

#### Modules and vectors

在赋值中`vector`长度和`wire`长度不必完全匹配，不匹配部分会发生补0或截断。

#### Adder1

```verilog
// module add16 ( input[15:0] a, input[15:0] b, input cin, output[15:0] sum, output cout );
wire out;
add16 adder(..., out,...); // wrong!
```

自定义vector要与模块的vector位数相匹配，否则会出现奇怪的结果。

#### Adder 2

全加器模块

```verilog
module add1 ( input a, input b, input cin, output sum, output cout );
	assign sum = a^b^cin;
  assign cout = a&b | a&cin | b&cin ;
endmodule
```

##### 半加器

不带进位输入的加法器。

<img src="/Users/guosongnan/Library/Application Support/typora-user-images/image-20201118132547159.png" alt="image-20201118132547159" style="zoom:50%;" />

![image-20201118132035952](/Users/guosongnan/Library/Application Support/typora-user-images/image-20201118132035952.png)
$$
S=A\bigoplus B \quad (异或) \\
C1=AB \quad (与)
$$

##### 全加器

<img src="/Users/guosongnan/Library/Application Support/typora-user-images/image-20201118132710932.png" alt="image-20201118132710932" style="zoom:50%;" />

![image-20201118132723700](/Users/guosongnan/Library/Application Support/typora-user-images/image-20201118132723700.png)
$$
S=CI\bigoplus A\bigoplus B\quad(异或) \\
\begin{align}
CO & = (A\cdot B)\ +\ (A\bigoplus B\cdot CI) \quad (两个半加器)\\
& =A\cdot B+A\cdot CI+B\cdot CI
\end{align}
$$

#### Adder-subtractor

用一个取值为0/1的信号x与另一个vector异或操作，可以实现对这个vector取反（x=1）或不变（x=0）。这个性质可以用来制作加减器。

### Procedures

#### Always blocks

组合逻辑：`always @(*)`

时序逻辑：`always @(posedge clk)`

时序逻辑也创建组合逻辑电路，但在组合逻辑的输出后会创建一些`D触发器/寄存器`。

在组合逻辑中用阻塞式赋值(x=y)，在时序逻辑中用非阻塞式赋值(x <= y)。

#### if statement

if总是创建2-1多选器。

`assign out = (condition) ? x : y;` `？：`操作符也创建2-1多选器。

if语句总是有值(没用空的else)，则if是组合逻辑，否则可能成为时序逻辑。

#### if statement latches

若存在没有指定的情况(空else)，verilog会创建`锁存器latches`以保持电路的状态。这十有八九是个bug。`Warning (10240): ... inferring latch(es)`

#### Priority encoder with casez

case的条件被顺序检测(有优先级)

```verilog
casez (in[3:0])
  4'bzzz1: out = 0;
  4'bzz1z: out = 1;
  4'bz1zz: out = 2;
  4'b1zzz: out = 3;
  default: out = 0;
endcase
casez (in[3:0])
  4'bzzz1: out=0;
  4'bzz10: out=1;
  4'bz100: out=2;
  4'b1000: out=3;
  default: out=0;
endcase
// 上述二者相同
```

#### Avoiding latches

使用初始赋值可以保证每个输出都有值以避免latches，default也不用写了。



## Circuits

### Combinational logic

#### Basic Gates

##### Truth Tables

若把组合逻辑的真值表写出，则所有取“1”项的积(and)之和(or)为该组合逻辑（未化简）。

##### Combine circuits A and B

task语法

```verilog
// ====定义====
task taskid;
  [declaration]
  procedural_statement
endtask
// ====调用====
// 任务调用语句可以在 initial 语句和 always 语句中使用
task_id[(端口1,  端口 2, ........,  端口 N)];
```



##### Ring or vinrate

When designing circuits, one often has to think of the problem "backwards", starting from the outputs then working backwards towards the inputs.

设计电路总是从输出开始设计到输入。

#### Multiplexers

##### Mux256to1v

```verilog
assign out = in[sel*4+3 -: 4]; 
```

通常写`[MSB:LSB]` 这里的MSB和LSB都要求是常数

而如果写`a[BASE :- WIDTH]`或`a[BASE +: WIDTH]`则允许BASE改变（但WIDTH仍需为常数）

比如定义reg [7:0] a;
a[7 -: 2]就表示a[7:6]

