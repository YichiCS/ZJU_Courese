        .ORIG x3000
        LD  R1,BASEL    ;PTR LEFT
        LD  R2,BASEL
        ADD R2,R2,#1    ;PTR RIGHT
        LD  R4,RES
        
INPUT   TRAP    x20
        TRAP    x21
        LD  R3,ENTER
        ADD R3,R3,R0
        BRz OUTPUT
        LD  R3,PLUS
        ADD R0,R0,R3
        BRzp F1
        JSR PUSHL
        BRnzp   INPUT
F1      BRp F2
        JSR POPL
        BRnzp   INPUT
F2      ADD R0,R0,R3
        ADD R0,R0,#-1
        BRp F3
        JSR PUSHR
        BRnzp   INPUT
F3      JSR POPR
        BRnzp   INPUT
OUTPUT  NOT R3,R4
        ADD R3,R3,#2
        LD  R4,RES
FINAL   ADD R0,R3,R4
        BRp FIN
        LDR R0,R4,#0
        TRAP    x21
        ADD R4,R4,#1
        BRnzp   FINAL
        
FIN     TRAP    x25

PUSHL   TRAP    x20
        TRAP    x21
        STR R0,R1,#0
        ADD R1,R1,#-1
        RET

PUSHR   TRAP    x20
        TRAP    x21
        STR R0,R2,#0
        ADD R2,R2,#1
        RET

POPL    NOT R3,R1
        ADD R3,R3,R2
        BRp F4
        LD  R0,US
        STR R0,R4,#0
        ADD R4,R4,#1
        RET
F4      ADD R1,R1,#1
        LDR R0,R1,#0
        STR R0,R4,#0
        ADD R4,R4,#1
        RET
        
POPR    NOT R3,R1
        ADD R3,R3,R2
        BRp F5
        LD  R0,US
        STR R0,R4,#0
        ADD R4,R4,#1
        RET
F5      ADD R2,R2,#-1
        LDR R0,R2,#0
        STR R0,R4,#0
        ADD R4,R4,#1
        RET
        
PLUS    .FILL #-45
BASEL   .FILL x3200
US      .FILL #95
RES     .FILL x3400
ENTER   .FILL #-10
        .END