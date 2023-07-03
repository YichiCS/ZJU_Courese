.tittle subadc
.include 'subadc.cdl'
.include 'comparator_o.cdl'
x1 vdd vss gnd vin out1 out2 out3 out4 out5 out6 clk subadc 
vdd vdd 0 2
vss 0 vss 2
vclk clk 0 pulse(0 1.8 1u 1u 1u 5us 10us)
vgnd gnd 0 0
vin vin 0 pwl (0 -1 1ms 1)
.tran 1us 0.999ms
.print v(out1) v(out2) v(out3) v(out4) v(out5) v(out6) V(vin)
.option post accurate probe
.lib 'C:\Users\TORU\Desktop\22Fall\BEC\Project\paper\Sim\models\ms018.lib' tt
.end