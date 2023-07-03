`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: zju
// Engineer:qmj
////////////////////////////////////////////////////////////////////////////////

module timing_tb;

	// Inputs
	reg clk;
	reg en;
    reg r;
	// Outputs
	wire [3:0] q0;
	wire [3:0]   q_s_0;
	wire [3:0]   q_s_1;
	wire [3:0] qm;	
	// Instantiate the Unit Under Test (UUT)
	 timing  uut (
		.clk(clk),
        .clr(r), 
		.en(en), 
		
        .q_0(q0),
		.q_s_0(q_s_0),
		.q_s_1(q_s_1),
		.q_m(qm));

	//clk
   always #50 clk=~clk;
	
	//  clr
	initial 
	 begin
	   clk = 0;r=0;en = 0;
       #(51) r=1;
  	   #(100)r=0 ;
       repeat (620)  begin 
	     #(100*3)  en=1;
	     # 100  en=0; end
         #1000 $stop;
  end
      
endmodule

