module mux_8to4(d0, d1, d2, d3, d0_0, d1_0, d2_0, d3_0, d0_1, d1_1, d2_1, d3_1, sel);

input [3:0] d0_0;
input [3:0] d1_0;
input [3:0] d2_0;
input [3:0] d3_0;

input [3:0] d0_1;
input [3:0] d1_1;
input [3:0] d2_1;
input [3:0] d3_1;

output reg [3:0] d0;
output reg [3:0] d1;
output reg [3:0] d2;
output reg [3:0] d3;

input  sel;


always @(*)
    begin
        case(sel)
		    1'b0:begin	
				d0 <= d0_0;
				d1 <= d1_0;
				d2 <= d2_0;
				d3 <= d3_0;
			end
			1'b1:begin	
				d0 <= d0_1;
				d1 <= d1_1;
				d2 <= d2_1;
				d3 <= d3_1;
			end
	    endcase
    end
endmodule