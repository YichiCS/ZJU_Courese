module asynch(asynch_in, clk, out);

input   asynch_in;
input   clk;
output  out;

wire    q1;
//wire    q2;

//dffre   #(.n(1))    ff(.d(1), .en(1'b1), .r(0 || out), .clk(asynch_in), .q(q1));   
//dffre   #(.n(1))    ff1(.d(q1), .en(1'b1), .r(0), .clk(clk), .q(q2));   
//dffre   #(.n(1))    ff2(.d(q2), .en(1'b1), .r(0), .clk(clk), .q(out));   


dffre   #(.n(1))    ff(.d(asynch_in), .en(1'b1), .r(0), .clk(clk), .q(q1));   
dffre   #(.n(1))    ff1(.d(q1), .en(1'b1), .r(0), .clk(clk), .q(out));   


endmodule
