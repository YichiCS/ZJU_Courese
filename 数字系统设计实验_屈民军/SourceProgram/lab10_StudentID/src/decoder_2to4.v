module decoder_2to4(
    input [1:0] d,
    output reg [3:0] o
);

always @* begin
    case (d)
        2'b00: o = 4'b1110;
        2'b01: o = 4'b1101;
        2'b10: o = 4'b1011;
        2'b11: o = 4'b0111;
    endcase
end
endmodule