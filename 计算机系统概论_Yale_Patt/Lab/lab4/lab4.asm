;PREPARE
        .ORIG   x0200
        LD  R6,OS_SP
        LD  R0,USER_PSR
        ADD R6,R6,#-1
        STR R0,R6,#0
        LD  R0,USER_PC
        ADD R6,R6,#-1
        STR R0,R6,#0
        
        LD  R0,CODE_ADD
        STI R0,ENTRY
        LD  R0,MASK
        STI R0,KBSR_ADD
        
        RTI
            
CODE_ADD    .FILL   x2000
ENTRY       .FILL   x0180
MASK        .FILL   x4000        
KBSR_ADD    .FILL   xFE00 

OS_SP       .FILL   x3000
USER_PSR    .FILL   x8002
USER_PC     .FILL   X3000
        
        .END

;TRAP ORDER
        .ORIG   x2000
        
LOOP1   LDI R2,KBSR
        BRzp    LOOP1
        LDI R0,KBDR
        
        ADD R3,R3,#0
        BRz T0
        ADD R3,R3,#-1
        LD  R4,DOT_n
        ADD R4,R4,R0
        BRz EXIT
        STI R0,ADDR0
        AND R1,R1,#0
        ADD R1,R1,R3
EXIT    RTI
                        ;THE FIRST 20 LETTERS
T0      LD  R4,DIV
        ADD R4,R4,R0
        BRnz    NUM
        
        STI R0,ADDR0
        RTI
        
NUM     ADD R4,R4,#9
        NOT R4,R4
        ADD R1,R1,R4
        LD  R4,LIM
        ADD R4,R4,R1
        BRp    BACK 
        LD  R1,LIM_n
BACK    RTI                        
       
        STI R0,ADDR0
        RTI

LIM     .FILL   #18
LIM_n   .FILL   #-18
DIV     .FILL   #-57   
DOT_n   .FILL   #-46
KBSR	.FILL	xFE00
KBDR	.FILL	xFE02
ADDR0   .FILL   x3200   
        .END


;USER PROGRAM
        .ORIG   x3000
        LD  R3,LEN
        
CHECK   ADD R3,R3,#0
        BRp CHECK
        
        ADD R1,R1,#-15
        ADD R1,R1,#-2
        
LOOP    ADD R1,R1,#1
        BRnz    F0
        AND R1,R1,#0
F0      AND R2,R2,#0
        ADD R2,R2,R1
F1      BRz     F2
        LD  R0,DOT
        OUT
        ADD R2,R2,#1
        BRnzp   F1
        
F2      LDI R0,ADDR
        OUT
        OUT
        OUT

        AND R2,R2,#0
        ADD R2,R2,R1
        ADD R2,R2,#15
        ADD R2,R2,#2
F3      BRz NEXT
        LD  R0,DOT
        OUT
        ADD R2,R2,#-1
        BRnzp   F3

NEXT    LD  R0,ENTER
        OUT
        JSR DELAY
        BRnzp   LOOP
        
DELAY   LD R2,COUNT
REP     ADD R2,R2,#-1
        BRp REP
        RET


LEN     .FILL   #20
ADDR    .FILL   x3200
DOT     .FILL   #46        
ENTER   .FILL   #10
COUNT   .FILL   #30000
        
        .END