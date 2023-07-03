module comp(a, b, agb, aeb, alb);
    parameter n=1;
    input   [n-1:0] a,b;
    output reg agb;
    output reg aeb;
    output reg alb;
    always @(a or b)
    begin 
        if (a > b)
            begin
                agb = 1;
                aeb = 0;
                alb = 0;
            end 
        else if(a < b)
            begin
                agb = 0;
                aeb = 0;
                alb = 1;
            end 
        else 
            begin
                agb = 0;
                aeb = 1;
                alb = 0;
            end 
    end

endmodule  