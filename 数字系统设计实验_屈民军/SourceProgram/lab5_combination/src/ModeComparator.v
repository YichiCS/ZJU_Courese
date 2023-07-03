module ModeComparator(a,b,m,y);
    input   [7:0]   a,b;
    input   [0:0]   m;
    output  [7:0]   y;

    wire agb;
    comp #(.n(8))comp_input(.a(a), .b(b), .agb(agb), .aeb(), .alb());

    wire addr;
    assign addr = ~m^agb;

    mux_2to1 #(.n(8))mux1(.out(y), .in0(a), .in1(b), .addr(addr));

    endmodule