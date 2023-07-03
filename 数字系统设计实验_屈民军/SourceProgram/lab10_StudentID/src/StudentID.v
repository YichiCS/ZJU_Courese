module StudentID(reset, clk, a, b, c, d, e, f, g, dp, pos);
parameter sim=0;
input reset, clk;
output a, b, c, d, e, f ,g, dp;
output [3:0] pos;

wire clk, pulse2Hz, pulse400Hz;
wire [51:0] id;
assign dp = 1;
shifter shifter1(.ld(reset), .clk(clk), .en(pulse2Hz), .q(id));

display display1(.d0(id[39:36]), .d1(id[43:40]), .d2(id[47:44]), .d3(id[51:48]), .scan(pulse400Hz) ,.clk(clk), .pos(pos), .a(a), .b(b), .c(c), .d(d), .e(e), .f(f), .g(g));

counter_n   #(.n(sim?4:25_0000), .counter_bits(sim?2:18))  DivI(.clk(clk), .r(0), .en(1'b1), .co(pulse400Hz));
counter_n   #(.n(sim?16:200), .counter_bits(sim?4:8))    DivII(.clk(clk), .r(0), .en(pulse400Hz), .co(pulse2Hz));


endmodule