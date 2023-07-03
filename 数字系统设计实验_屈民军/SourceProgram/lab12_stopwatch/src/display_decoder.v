module display_decoder(din, a, b, c, d, e, f ,g);

input [3:0] din;

output reg a, b, c, d, e, f ,g;

always@(*)
    begin
        case(din) 
            4'b0000: {a, b, c, d, e, f, g} = 7'b000_0001;
            4'b0001: {a, b, c, d, e, f, g} = 7'b100_1111;
            4'b0010: {a, b, c, d, e, f, g} = 7'b001_0010;
            4'b0011: {a, b, c, d, e, f, g} = 7'b000_0110;
            4'b0100: {a, b, c, d, e, f, g} = 7'b100_1100;
            4'b0101: {a, b, c, d, e, f, g} = 7'b010_0100;
            4'b0110: {a, b, c, d, e, f, g} = 7'b010_0000;
            4'b0111: {a, b, c, d, e, f, g} = 7'b000_1111;
            4'b1000: {a, b, c, d, e, f, g} = 7'b000_0000;
            4'b1001: {a, b, c, d, e, f, g} = 7'b000_0100;
            default: {a, b, c, d, e, f, g} = 7'b111_1111;
        endcase
    end

endmodule