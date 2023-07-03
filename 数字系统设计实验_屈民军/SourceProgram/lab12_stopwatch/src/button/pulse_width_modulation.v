module pulse_width_modulation(in, clk, out);

input   in;
input   clk;
output  out;

wire    q;

dffre   #(.n(1))    ff(.d(in), .en(1'b1), .r(1'b0), .clk(clk), .q(q));   

assign out = in & (~q) ; 

endmodule
