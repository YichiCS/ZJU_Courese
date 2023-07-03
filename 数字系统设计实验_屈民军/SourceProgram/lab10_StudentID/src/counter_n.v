module counter_n(clk,en,r,co);
  parameter  n=2; 
  parameter  counter_bits = 1;
  input   clk,en,r ;
  output  co;
  reg [counter_bits-1: 0] q = 0;
  assign  co=(q==(n-1)) && en;
  always @(posedge clk) 
  begin
      if(r) q=0;
	  else if(en)
	          begin	 
                if(q==(n-1))  q=0 ;
                else q=q+1;		 
              end
  end
endmodule
