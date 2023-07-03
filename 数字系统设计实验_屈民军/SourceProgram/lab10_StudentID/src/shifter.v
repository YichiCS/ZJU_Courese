module shifter(ld, clk, en, q);
  input   ld, clk, en;
  output [51:0] q;
  reg [51:0]  q=0;
  always @(posedge clk) 
  begin
      if(ld) q=52'haaa3210103159;
      else if(en)
	      begin	 
          q = {q[47:0], q[51:48]};	 
        end
  end
endmodule