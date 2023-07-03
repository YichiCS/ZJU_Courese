.title Switch
.include 'Bootstrap.cdl'

X1 vdd gnd clk in out Bootstrap

v1 vdd 0 3.3
v2 gnd 0 0
vclk clk 0 pulse(0 3.3 1u 0.1u 0.1u 4u 9u)
vin in 0 sin(0.9 0.5 2k 0 0 0 )
cc out 0 2p

.tran 0.01us 0.999ms
.print v(out)
.option post accurate probe
.measure powerall avg power
.lib 'C:\Users\TORU\Desktop\22Fall\BEC\Project\paper\Sim\models\ms018.lib' tt

.end