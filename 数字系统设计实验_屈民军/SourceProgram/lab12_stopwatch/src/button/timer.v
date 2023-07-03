module timer(clk,en,r,done);
    parameter  n=2; 
    parameter  counter_bits=1;
    input   clk, en, r;
    output  done;
    reg [counter_bits-1:0]  q=0;
    assign  done=(q==(n-1)) && en;
    always @(posedge clk) 
     begin
        if(r) q=0;
	    else if(en)
	            begin	 
                    q=q+1;		 
                end
    end
endmodule
