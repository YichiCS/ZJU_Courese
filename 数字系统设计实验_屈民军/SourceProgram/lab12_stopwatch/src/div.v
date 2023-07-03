module div (clk, pulse400Hz, pulse10Hz);
input clk;
output pulse400Hz;
output pulse10Hz;

parameter sim = 1'b0;

counter_n   #(.n(sim?2:250000), .counter_bits(sim?1:18))    DivI (.clk(clk), .r(0), .en(1'b1), .co(pulse400Hz), .q());
counter_n   #(.n(sim?10:40),    .counter_bits(sim?4:6))     DivII(.clk(clk), .r(0), .en(pulse400Hz), .co(pulse10Hz), .q());

endmodule