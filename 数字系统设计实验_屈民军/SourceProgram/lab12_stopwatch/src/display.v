module display(
  input [3:0] d0,
  input [3:0] d1,
  input [3:0] d2,
  input [3:0] d3,
  input scan, clk,
  output a, b, c, d, e, f, g,
  output reg dp,
  output [3:0] pos
);

always @ (posedge clk) begin
  dp <= pos[1];
end

wire [1:0] sel;
wire [3:0] din;

counter_n   #(.n(4), .counter_bits(2)) counter_mod4(.clk(clk), .r(0), .en(scan), .co(), .q(sel));

decoder_2to4 decoder(.d(sel), .out(pos));

mux_4to1     mux(.d0(d0), .d1(d1), .d2(d2), .d3(d3), .sel(sel), .out(din));

display_decoder ddcoder(.din(din), .a(a), .b(b), .c(c), .d(d), .e(e), .f(f), .g(g));

endmodule