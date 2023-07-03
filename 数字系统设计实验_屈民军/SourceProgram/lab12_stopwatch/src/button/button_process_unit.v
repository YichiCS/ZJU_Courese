module button(reset, ButtonIn, ButtonOut, clk);

input   reset;
input   ButtonIn;
input   clk;

parameter sim = 1'b0;

output  ButtonOut;
wire    r1;
wire    r2;



asynch  asynch(.asynch_in(ButtonIn), .clk(clk), .out(r1));

anti_vibration #(.sim(sim)) anti(.clk(clk), .in(r1), .reset(reset), .out(r2));

pulse_width_modulation  trans(.in(r2), .clk(clk), .out(ButtonOut));
endmodule