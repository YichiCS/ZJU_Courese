module stopwatch (ButtonIn, clk, reset, pos, a, b, c, d, e, f, g, dp);

input ButtonIn;
input clk;
input reset;

output wire [3:0] pos;
output a, b, c, d, e, f, g;
output dp;

wire clr;
wire count;
wire pulse10Hz;
wire pulse400Hz;
wire ButtonOut;
wire din;
wire dout;

wire [3:0] q_0;
wire [3:0] q_s_0;
wire [3:0] q_s_1;
wire [3:0] q_m;

wire [3:0] q_01;
wire [3:0] q_s_01;
wire [3:0] q_s_11;
wire [3:0] q_m1;

wire [3:0] d0;
wire [3:0] d1;
wire [3:0] d2;
wire [3:0] d3;

parameter sim = 1'b0;

mux_8to4    Mux (.d0(d0), .d1(d1), .d2(d2), .d3(d3), 
                .d0_0(q_0), .d1_0(q_s_0), 
                .d2_0(q_s_1), .d3_0(q_m), 
                .d0_1(q_01), .d1_1(q_s_01), 
                .d2_1(q_s_11), .d3_1(q_m1), 
                .sel(dout)
                );

storage  Storage(.clk(clk), .din(ButtonOut), .clr(clr),
                .din0(q_0), .din1(q_s_0), .din2(q_s_1), .din3(q_m),
                .dout0(q_01), .dout1(q_s_01), .dout2(q_s_11), .dout3(q_m1)
                );

display Display (.d0(d0), .d1(d1), .d2(d2), .d3(d3), 
                .scan(pulse400Hz), .clk(clk), 
                .a(a), .b(b), .c(c), .d(d), .e(e), .f(f), .g(g), 
                .pos(pos), .dp(dp)
                );

div #(.sim(sim))    Div (.clk(clk), 
                .pulse400Hz(pulse400Hz), .pulse10Hz(pulse10Hz)
                );

control Control (.clk(clk), .reset(reset),
                .in(ButtonOut), 
                .count(count), .clr(clr),
                .din(din), .dout(dout)
                );

timing  Timing  (.en(count && pulse10Hz), .clr(clr), .clk(clk),
                 .q_0(q_0), .q_s_0(q_s_0), .q_s_1(q_s_1), .q_m(q_m)
                );

button  #(.sim(sim))    Button  (.ButtonIn(ButtonIn),
                .clk(clk), .reset(reset),
                .ButtonOut(ButtonOut)
                );

endmodule