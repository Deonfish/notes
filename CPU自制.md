# CPU自制

注：所用宏定义中的“总线”指的是：`31:0`这样形式的定义，会用在某个vector上

#### 通用寄存器

```verilog
module gpr (
	/********** 时钟 & 复位 **********/
	input  wire				   clk,				   				 // 时钟信号
	input  wire				   reset,			   				 // 异步复位
	/********** 读取端口 0 **********/
  input  wire [`RegAddrBus]  rd_addr_0,		   // 读取的地址	(寄存器号)
  output wire [`WordDataBus] rd_data_0,		   // 读出的数据
	/********** 读取端口 1 **********/
  input  wire [`RegAddrBus]  rd_addr_1,		   // 读取的地址	(寄存器号)
  output wire [`WordDataBus] rd_data_1,		   // 读出的数据
	/********** 写入端口 **********/
	input  wire				   we_,				   				 // 写入有效
  input  wire [`RegAddrBus]  wr_addr,			   // 写入地址 (寄存器号)
  input  wire [`WordDataBus] wr_data			   // 写入数据
);
```

![image-20201119100910091](/Users/guosongnan/Library/Application Support/typora-user-images/image-20201119100910091.png)

包含一个寄存器组，有两个写入端口、一个读取端口。支持对同一寄存器同时读写。

#### SPM

```verilog
module spm (
	/********** 时钟 **********/
	input  wire				   clk,										// 时钟信号
	/********** 端口A : IF阶段 **********/
  input  wire [`SpmAddrBus]  if_spm_addr,			// 地址
	input  wire				   if_spm_as_,						// 地址选通
	input  wire				   if_spm_rw,							// 读/写信号
  input  wire [`WordDataBus] if_spm_wr_data,	// 写入的数据
  output wire [`WordDataBus] if_spm_rd_data,	// 读出的数据
	/********** 端口B : MEM阶段 **********/
  input  wire [`SpmAddrBus]  mem_spm_addr,		// 地址
	input  wire				   mem_spm_as_,						// 地址选通
	input  wire				   mem_spm_rw,						// 读/写信号
  input  wire [`WordDataBus] mem_spm_wr_data, // 写入的数据
  output wire [`WordDataBus] mem_spm_rd_data	// 读出的数据
);
```

不经过总线直接访问的内存。读取指令时直接从这里读取。

#### 总线接口(bus interface)

```verilog
module bus_if (
	/********** 时钟 & 复位 **********/
	input  wire				   clk,			   					// 时钟
	input  wire				   reset,		   					// 异步复位
	/********** 流水线控制信号 **********/
	input  wire				   stall,		   					// 延迟信号
	input  wire				   flush,		   					// 刷新信号
	output reg				   busy,		   					// 总线忙信号
	/********** CPU接口 **********/
  input  wire [`WordAddrBus] addr,		   		// 地址
	input  wire				   as_,			   					// 地址有效
	input  wire				   rw,			   					// 读/写
  input  wire [`WordDataBus] wr_data,		   	// 写入数据
  output reg	[`WordDataBus] rd_data,		   	// 读出的数据
	/********** SPM接口 **********/
  input  wire [`WordDataBus] spm_rd_data,	  // 从SPM读出的数据
  output wire [`WordAddrBus] spm_addr,	   	// 地址
	output reg				   spm_as_,		   				// 地址有效
	output wire				   spm_rw,		   				// 读/写
  output wire [`WordDataBus] spm_wr_data,	  // 向SPM写的数据
	/********** 总线接口 **********/
  input  wire [`WordDataBus] bus_rd_data,	  // 从总线读出的数据
	input  wire				   bus_rdy_,	   				// 总线就绪
	input  wire				   bus_grnt_,	   				// 总线许可
	output reg				   bus_req_,	   				// 总线请求
  output reg	[`WordAddrBus] bus_addr,	   	// 地址
	output reg				   bus_as_,		   				// 地址有效
	output reg				   bus_rw,		   				// 读/写
  output reg	[`WordDataBus] bus_wr_data	  // 向总线写入的数据
);
```

主要实现由CPU接口传入指令地址`addr`，从总线/SPM中读取指令，从`spm_rd_data`或`bus_wr_data`读入，从`rd_data`端传递给CPU。

用到的宏

```verilog
// *************** stddef.h **************/

// 数据总线
/********** 最低位 *********/
`define LSB					0		 // 最低位(Least Significant Bit)
/********** 字节 (8 bit) *********/
`define BYTE_DATA_W			8		 // 字节宽度
`define BYTE_MSB			7		 // 字节最高位(Most Significant Bit)
`define ByteDataBus			7:0		 // 字节数据总线
/********** 字 (32 bit) *********/
`define WORD_DATA_W			32		 // 字宽度
`define WORD_MSB			31		 // 字最高位
`define WordDataBus			31:0	 // 字数据总线

// 地址总线
/********** 字地址 *********/
`define WORD_ADDR_W			30		 // 字地址宽度
`define WORD_ADDR_MSB		29		 // 字地址最高位
`define WordAddrBus			29:0	 // 字地址总线
/********** 字节位移 *********/
`define BYTE_OFFSET_W		2		 // 字节位移宽度
`define ByteOffsetBus		1:0		 // 字节位移总线
/********** 地址位置 *********/
`define WordAddrLoc			31:2	 // 字地址位置
`define ByteOffsetLoc		1:0		 // 字节位移位置
/********** 字节边界值 *********/
`define BYTE_OFFSET_WORD	2'b00	 // 字边界

// *************** cpu.h **************/
// 总线
`define BusIfStateBus		 1:0   // 状态总线
// 状態
`define BUS_IF_STATE_IDLE	 2'h0  // 空闲
`define BUS_IF_STATE_REQ	 2'h1  // 请求总线
`define BUS_IF_STATE_ACCESS	 2'h2  // 访问总线
`define BUS_IF_STATE_STALL	 2'h3  // 停滞

// *************** bus.h **************/
/********** 总线从属 *********/
`define BUS_SLAVE_CH	   8	 // 总线从属通道数
`define BUS_SLAVE_INDEX_W  3	 // 总线从属索引宽度
`define BusSlaveIndexBus   2:0	 // 总线从属总线
`define BusSlaveIndexLoc   29:27 // 总线从属索引位置

`define BUS_SLAVE_0		   0	 // 总线从属0号
`define BUS_SLAVE_1		   1	 // 总线从属1号
`define BUS_SLAVE_2		   2	 // 总线从属2号
`define BUS_SLAVE_3		   3	 // 总线从属3号
`define BUS_SLAVE_4		   4	 // 总线从属4号
`define BUS_SLAVE_5		   5	 // 总线从属5号
`define BUS_SLAVE_6		   6	 // 总线从属6号
`define BUS_SLAVE_7		   7	 // 总线从属7号

```

总线从属位在30,29,28位？

SPM为总线从属1号

控制CPU访问总线或SPM，CPU不知道要访问的内存是直接还是间接，只发给总线接口要访问的地址，总线接口根据地址的总线从属索引位(30,29,28位)来区分并转发。

#### IF阶段

IF寄存器

```verilog
module if_reg (
	/********** 时钟 & 复位 **********/
	input  wire				   clk,		   				// 时钟
	input  wire				   reset,	   				// 异步复位
	/********** 从IF级输入 **********/
  input  wire [`WordDataBus] insn,	   	// 读取的指令
	input  wire				   stall,	   				// 延迟
	input  wire				   flush,	   				// 刷新
  input  wire [`WordAddrBus] new_pc,	  // 新PC值
	input  wire				   br_taken,   			// 分支成立
  input  wire [`WordAddrBus] br_addr,	  // 分支目标地址
	/********** 向ID级输出 **********/
  output reg	[`WordAddrBus] if_pc,	   	// 程序计数器
	output reg	[`WordDataBus] if_insn,	  // 命令
	output reg				   if_en	   				// 流水线数据有效标志位
);
```

主要实现PC的自增。其中`if_pc`为pc寄存器，`if_insn`为IR寄存器，指令通过`insn`传递进来并被传递出去，同时PC++。

IF阶段顶层模块

```verilog
module if_stage (
	/********** 时钟 & 复位 **********/
	input  wire				   clk,								// 时钟
	input  wire				   reset,							// 非同步复位
	/********** SPM接口 **********/
	input  wire [`WordDataBus] spm_rd_data, // SPM读出的数据
	output wire [`WordAddrBus] spm_addr,		// 向spm输出的地址
	output wire				   spm_as_,						// 地址有效信号
	output wire				   spm_rw,						// 读/写
	output wire [`WordDataBus] spm_wr_data, // 向spm写的数据
	/********** 总线接口 **********/
	input  wire [`WordDataBus] bus_rd_data, // 总线读出的数据
	input  wire				   bus_rdy_,					// 总线就绪
	input  wire				   bus_grnt_,					// 总线允许
	output wire				   bus_req_,					// 总线请求
	output wire [`WordAddrBus] bus_addr,		// 向总线输出的地址
	output wire				   bus_as_,						// 地址有效信号
	output wire				   bus_rw,						// 读/写
	output wire [`WordDataBus] bus_wr_data, // 向总线写的数据
	/********** 流水线控制信号 **********/
	input  wire				   stall,							// 延时
	input  wire				   flush,							// 流水线刷新
	input  wire [`WordAddrBus] new_pc,			// 新pc值
	input  wire				   br_taken,					// 分支成立
	input  wire [`WordAddrBus] br_addr,			// 分支地址
	output wire				   busy,							// 忙碌信号
	/********** IF / ID流水线寄存器 **********/
	output wire [`WordAddrBus] if_pc,				// 程序计数器
	output wire [`WordDataBus] if_insn,			// 命令
	output wire				   if_en							// 流水线数据有效标志位
);
```

此模块主要实现PC的自增及指令的读取和传递（不包括IF/ID流水寄存器）。

#### ID阶段

用到的宏

```verilog
// isa.h (Instruction Set Architecture 指令集架构)
`define ISA_OP_W		   6	 	 	// 操作码宽度
`define IsaOpBus		   5:0	 	// 操作码总线
`define IsaOpLoc		   31:26 	// 操作码位置

// 指令集

/********** 寄存器 **********/
`define ISA_REG_ADDR_W	   5	 // 寄存器地址宽度
`define IsaRegAddrBus	   4:0	 // 寄存器地址总线
`define IsaRaAddrLoc	   25:21 // 寄存器Ra位置
`define IsaRbAddrLoc	   20:16 // 寄存器Rb位置
`define IsaRcAddrLoc	   15:11 // 寄存器Rc位置
/********** 立即数 **********/
`define ISA_IMM_W		   16	 		 // 立即数宽度
`define ISA_EXT_W		   16	 		 // 立即数位拓展所需位数
`define ISA_IMM_MSB		   15	   // 立即数最高位
`define IsaImmBus		   15:0	   // 立即数总线
`define IsaImmLoc		   15:0	   // 立即数位置

/********** 异常 **********/
`define ISA_EXP_W		   3	 		 // 异常码宽度
`define IsaExpBus		   2:0	 	 // 异常码总线
// 异常码
```

数据直通：`id_en`有表示EX阶段的数据直通，`ex_en`表示有MEM阶段的数据直通。