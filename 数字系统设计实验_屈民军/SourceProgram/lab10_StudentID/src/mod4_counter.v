module mod4_counter(
    input scan,
    input clk,
    output reg [1:0] q = 0
);

always @(posedge clk) begin
    if (scan) begin
        q <= q + 1;
        if (q == 2'd3) begin
            q <= 2'd0;
        end
    end
end

endmodule