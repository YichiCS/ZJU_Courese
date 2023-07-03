module timing (en, clr, clk, q_0, q_s_0, q_s_1, q_m);

input   en;
input   clr;
input   clk;

output  wire [3:0]   q_0;
output  wire [3:0]   q_s_0;
output  wire [3:0]   q_s_1;
output  wire [3:0]   q_m;

wire    co_0;
wire    co_s_0;
wire    co_s_1;

counter_n   #(.n(10), .counter_bits(4))     Count_0     (.clk(clk), .r(clr), .en(en), .co(co_0), .q(q_0));

counter_n   #(.n(10), .counter_bits(4))     Count_s_0   (.clk(clk), .r(clr), .en(co_0), .co(co_s_0), .q(q_s_0));
counter_n   #(.n(6),  .counter_bits(4))     Count_s_1   (.clk(clk), .r(clr), .en(co_s_0), .co(co_s_1), .q(q_s_1));

counter_n   #(.n(10), .counter_bits(4))     Count_m     (.clk(clk), .r(clr), .en(co_s_1), .co(), .q(q_m));


    
endmodule