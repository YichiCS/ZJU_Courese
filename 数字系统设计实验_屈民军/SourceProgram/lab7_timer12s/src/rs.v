module rsff( 
  input wire clk,r,s,			//rs触发器输入信号		
  output reg q			//输出端口q，在always块里赋值，定义为reg型
 );
 always@(posedge clk)
begin
	case({r,s})
		2'b00:  q <= q;      //r,s同时为低电平，触发器保持状态不变
		2'b01:  q <= 1'b1;	   //触发器置1状态
		2'b10:  q <= 1'b0;   //触发器置0状态
		2'b11:  q <= 1'bx;   //r,s同时为高电平有效，逻辑矛盾，触发器为不定态
	endcase
end
endmodule