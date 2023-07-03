module storage(
  input clk,
  input din,
  input clr,

  input [3:0] din0,
  input [3:0] din1,
  input [3:0] din2,
  input [3:0] din3,

  output [3:0] dout0,
  output [3:0] dout1,
  output [3:0] dout2,
  output [3:0] dout3

);

reg [15:0] data; // 内部寄存器，用于存储输入数据

reg [3:0] flag = 0;

always @(posedge clk) begin
  if (clr == 1) begin
    flag = 0;
  end
  if (din == 1 ) begin
    flag <= flag + 1;
  end
  if (din == 1 && flag == 1 ) begin
    data <= {din3, din2, din1, din0}; // 存储输入数据到寄存器中
  end
end

assign {dout3, dout2, dout1, dout0} = data; // 将寄存器中的数据输出到输出信号中

endmodule