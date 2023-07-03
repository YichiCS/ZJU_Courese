module display(
    input [3:0] d0, d1, d2, d3,
    input scan, clk,
    output a, b, c, d, e, f, g,
    output [3:0] pos
);

    wire [1:0] sel;
    wire [3:0] din;

    mod4_counter counter(.scan(scan), .clk(clk), .q(sel));

    decoder_2to4 decoder(.d(sel), .o(pos));

    mux_4to1     mux(.d0(d0), .d1(d1), .d2(d2), .d3(d3), .sel(sel), .out(din));

    display_decoder ddcoder(.din(din), .a(a), .b(b), .c(c), .d(d), .e(e), .f(f), .g(g));

endmodule