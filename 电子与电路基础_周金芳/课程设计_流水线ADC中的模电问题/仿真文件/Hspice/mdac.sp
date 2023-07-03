.tittle subadc
.include 'OPA.cdl'
.include 'comparator_o.cdl'
.include 'mdac.cdl'
.include 'subadc.cdl'

Xsub vdd vss gnd vin out1 out2 out3 out4 out5 out6 clk subadc
Xmadc vdd vss gnd out1 out2 out3 out4 out5 out6 vinn out outt in mdac
vdd vdd 0 2
vss 0 vss 2
vgnd gnd 0 0
vclk clk 0 pulse(0 1.8 1n 1n 1n 5us 10us)
vin vin 0 pwl (0 -1 1ms 1)
vinn vinn 0 pwl (0 1 1ms -1)
.tran 1us 0.999ms
.print V(vin)
.print v(out)
.option post accurate probe
.measure powerall avg power
.lib 'C:\Users\TORU\Desktop\22Fall\BEC\Project\paper\Sim\models\ms018.lib' tt
.end