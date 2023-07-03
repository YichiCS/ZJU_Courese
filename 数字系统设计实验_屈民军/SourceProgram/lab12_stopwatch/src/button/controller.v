module controller(clk, in, reset, timer_clr, timer_done, out);

input   clk;
input   in;
input   reset;
input   timer_done;
output  reg [0:0]   timer_clr;
output  reg [0:0]   out;

//定义状态机的状态
parameter            LOW   = 3'd0 ;
parameter            WAIT_HIGH  = 3'd1 ;
parameter            HIGH  = 3'd2 ;
parameter            WAIT_LOW  = 3'd3 ;

//定义状态寄存器和下一个状态寄存器 
reg [2:0]            state ;
reg [2:0]            next_state ;

//初始化

initial begin
    state = LOW;
end

//状态机逻辑
always @(posedge clk) begin
  if (reset) begin
    state = LOW;
  end else begin
    state = next_state;
  end
end

//状态机状态转移逻辑
always @(*) begin
    case(state)
        LOW: begin
            if(in) begin
                next_state = WAIT_HIGH;
            end else begin
                next_state = LOW;
            end
        end
        WAIT_HIGH: begin
            if(timer_done) begin
                next_state = HIGH;
            end else begin
                next_state = WAIT_HIGH;
            end
        end
        HIGH: begin
            if(in) begin
                next_state = HIGH;
            end else begin
                next_state = WAIT_LOW;
            end
        end
        WAIT_LOW: begin
            if(timer_done) begin
                next_state = LOW;
            end else begin
                next_state = WAIT_LOW;
            end
        end
    endcase
end

//控制输出的逻辑
always @(*) begin
    if(reset) begin
        timer_clr = 1;
    end else begin
        case(state)
            LOW: begin
                timer_clr = 1;
                out = 0;
            end
            WAIT_HIGH: begin
                timer_clr = 0;
                out = 1;
            end
            HIGH: begin
                timer_clr = 1;
                out = 1;
            end
            WAIT_LOW: begin
                timer_clr = 0;
                out = 1;
            end
        endcase
    end
end

endmodule