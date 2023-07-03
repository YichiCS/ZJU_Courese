module dffre(d, en, r, clk, q);
parameter n = 1;
output [n-1:0]  q;
input d, en, r, clk;
reg[n-1:0] q;

always@(posedge clk)
begin
    if(r == 1'b1)begin
        q <= 0;
    end
    else begin
        if(en == 1'b1)begin
            q <= d;
        end
        else begin
            q <= q;
        end
    end
end
endmodule