.title Switch
.include 'Transmission_Gate.cdl'
X1 vdda gnda s in out SWITCHb

v1 vdda 0 1.8
v2 gnda 0 0
vclk s 0 pulse(0 1.8 4u 0.1u 0.1u 4u 8.2u)
vin in 0 sin(1 1 2k 0 0 0 )
cc out 0 2p
.tran 0.01us 0.999ms
.print v(out) V(vin) v(clk)
.option post accurate probe

.lib 'C:\Users\TORU\Desktop\22Fall\BEC\Project\paper\Sim\models\ms018.lib' tt

.end