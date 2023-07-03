.tittle comparator

.include 'comparator_o.cdl'
x1 vdda gnda vip vin outp clk comparator
v1 vdda 0 1.8 
v2 0 gnda 0
vclk clk 0 pulse(0 1.8 5us 0.1us 0.1us 1us 2us)
vip  vip 0 pwl (0 0.6 0.01ms 1.4 0.02ms 0.6 0.03ms 1.4 0.04ms 0.6 0.05ms 1.4)
vin  vin 0 dc 1

.tran 0.1us 50us
.print v(outp) v(vin) v(clk) v(vip)
.option post accurate probe
.lib 'C:\Users\TORU\Desktop\22Fall\BEC\Project\paper\Sim\models\ms018.lib' tt

.end