module decoder_2to4(d, out);

input [1:0] d;
output reg [3:0] out;

always @* begin
    case (d)
        2'b00: out = 4'b1110;
        2'b01: out = 4'b1101;
        2'b10: out = 4'b1011;
        2'b11: out = 4'b0111;
    endcase
end
endmodule