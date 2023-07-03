module anti_vibration(clk, in, reset, out);

input   clk;
input   in;
input   reset;
output  out;

parameter sim = 1'b0;

wire pulse1kHz;
wire timer_clr;
wire timer_done;

counter_n   #(.n(sim?2:10**5), .counter_bits(sim?2:17))  Div(.clk(clk), .r(1'b0), .en(1'b1), .co(pulse1kHz), .q());

timer       #(.n(10), .counter_bits(4)) tenms_timer(.clk(clk), .en(pulse1kHz), .r(timer_clr), .done(timer_done));
controller  control(.clk(clk), .in(in), .reset(reset), .timer_clr(timer_clr), .timer_done(timer_done), .out(out));


endmodule