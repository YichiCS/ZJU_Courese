module mux_4to1(out, d0, d1, d2, d3, sel);
output [3:0]  out;
input [3:0]  d0, d1, d2, d3;
input [1:0] sel;

reg[3:0] out;

always @*
    begin
        case(sel)
		    2'b00:  out <= d0;
		    2'b01:  out <= d1;
		    2'b10:  out <= d2;
		    2'b11:  out <= d3;
	    endcase
    end
endmodule