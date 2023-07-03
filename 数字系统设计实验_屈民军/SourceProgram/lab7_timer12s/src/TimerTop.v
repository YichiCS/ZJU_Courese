module TimerTop (clk, reset, start, LED1, LED0);
    input clk, reset, start;
    output LED1, LED0;
    parameter sim = 1'b0;

    wire pulse10Hz,pulse1Hz;
    wire TimerEn, TimerOut;
    wire clr;

    assign LED1 = TimerEn;

    counter_n   #(.n(sim?2:10**7), .counter_bits(sim?1:24))  DivI(.clk(clk), .r(0), .en(1'b1), .co(pulse10Hz), .q());
    counter_n   #(.n(10), .counter_bits(4))                  DivII(.clk(clk), .r(0), .en(pulse10Hz), .co(pulse1Hz), .q());

    timer       #(.n(12), .counter_bits(4))                  TimerInst(.clk(clk), .r(reset || start), .en(pulse1Hz && TimerEn), .done(TimerOut));

    rsff        ff1(.clk(clk), .r(reset || TimerOut), .s(start), .q(TimerEn));
    rsff        ff2(.clk(clk), .r(TimerOut), .s(reset || start), .q(clr));

    dffre       #(.n(1))        ff3(.d(~LED0), .en(pulse10Hz), .r(clr), .clk(clk), .q(LED0));      

endmodule