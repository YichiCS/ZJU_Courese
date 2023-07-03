module control(clk, in, reset, count, clr, din, dout);

input   clk;
input   in;
input   reset;

output  reg count;
output  reg clr;

output  reg din;
output  reg dout;

//定义状态机的状态
parameter            RESET = 3'd0 ;
parameter            TIMING = 3'd1 ;
parameter            RECORD_0 = 3'd2 ;
parameter            RECORD_1 = 3'd3 ;
parameter            SHOW = 3'd4 ;

//定义状态寄存器和下一个状态寄存器 
reg [2:0]            state ;
reg [2:0]            next_state ;

//初始化

initial begin
    state = RESET;
end

//状态机逻辑
always @(posedge clk) begin
  if (reset) begin
    state = RESET;
  end else begin
    state = next_state;
  end
end

//状态机状态转移逻辑
always @(*) begin
    case(state)
        RESET: begin
            if(in) begin
                next_state = TIMING;
            end else begin
                next_state = RESET;
            end
        end
        TIMING: begin
            if(in) begin
                next_state = RECORD_0;
            end else begin
                next_state = TIMING;
            end
        end
        RECORD_0: begin
            if(in) begin
                next_state = RECORD_1;
            end else begin
                next_state = RECORD_0;
            end
        end
        RECORD_1: begin
            if(in) begin
                next_state = SHOW;
            end else begin
                next_state = RECORD_1;
            end
        end
        SHOW: begin
            if(in) begin
                next_state = RESET;
            end else begin
                next_state = SHOW;
            end
        end
    endcase
end

//控制输出的逻辑
always @(*) begin
    if(reset) begin
        clr = 1;
    end else begin
        case(state)
            RESET: begin
                clr = 1;
                count = 0;
                din = 0;
                dout = 0;
            end
            TIMING: begin
                clr = 0;
                count = 1;
                din = 0;
                dout = 0;
            end
            RECORD_0: begin
                clr = 0;
                count = 1;
                din = 1;
                dout = 0;
            end
            RECORD_1: begin
                clr = 0;
                count = 0;
                din = 0;
                dout = 0;
            end
            SHOW: begin
                clr = 0;
                count = 0;
                din = 0;
                dout = 1;
            end
        endcase
    end
end

endmodule