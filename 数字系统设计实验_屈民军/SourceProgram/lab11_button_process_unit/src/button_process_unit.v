module button_unit(reset, ButtonIn, clk, led);

input   reset;
input   ButtonIn;
input   clk;
output  led;

parameter sim = 1'b0;

wire  ButtonOut;
wire    r1;
wire    r2;



asynch  asynch(.asynch_in(ButtonIn), .clk(clk), .out(r1));

anti_vibration #(.sim(sim)) anti(.clk(clk), .in(r1), .reset(reset), .out(r2));

pulse_width_modulation  trans(.in(r2), .clk(clk), .out(ButtonOut));


dffre #(.n(1)) test(.d(~led), .en(ButtonOut), .clk(clk), .r(0), .q(led));
endmodule