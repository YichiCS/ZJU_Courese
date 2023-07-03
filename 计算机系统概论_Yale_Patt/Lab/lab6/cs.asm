.ORIG   x3000


        LEA     R0, HINT
        LD      R1, HEAD
        AND     R4, R4, #0
        LEA     R6, INPUT
        PUTS

LOOP_I  GETC
        OUT
        ADD     R3, R0, #-13    
        BRz     BREAK_I         
        ADD     R3, R0, #-10    
        BRz     BREAK_I
        STR     R0, R6, #0
        ADD     R6, R6, #1
        BR      LOOP_I
BREAK_I AND     R0, R0, #0
        STR     R0, R6, #0
        LEA     R6, INPUT
        LEA     R0, INPUT
LOOP    LDR     R1, R1, #0
        BRz     BREAK           
        AND     R5, R5, #0      
        LDR     R0, R1, #2      
        JSR     COMPARE
        LDR     R0, R1, #3      
        JSR     COMPARE
        ADD     R5, R5, #0      
        BRz     CONTINU
        ADD     R4, R4, #1      
        JSR     PRINT
CONTINU BR      LOOP
BREAK   ADD     R4, R4, #0      
        BRnp    FINISH
        LEA     R0, NO
        PUTS
FINISH  HALT
COMPARE ST      R7, SAVE
LOOP_C  LDR     R2, R0, #0      
        LDR     R3, R6, #0      
        NOT     R3, R3
        ADD     R3, R3, #1
        ADD     R2, R2, R3      
        BRnp    BREAK_C
        ADD     R3, R3, #0      
        BRz     FOUND           
        ADD     R0, R0, #1
        ADD     R6, R6, #1
        BR      LOOP_C    
FOUND   ADD     R5, R5, #1
BREAK_C LEA     R6, INPUT       
        LD      R7, SAVE        
        RET
PRINT   ST      R7, SAVE
        LDR     R0, R1, #2      
        PUTS
        LEA     R0, TAB
        PUTS
        LDR     R0, R1, #3      
        PUTS
        LEA     R0, TAB
        PUTS
        LDR     R0, R1, #1      
        PUTS
        LEA     R0, ENDL
        PUTS
        LD      R7, SAVE
        RET
HEAD    .FILL   x4000
SAVE    .BLKW   #1
INPUT   .BLKW   #16
TAB     .STRINGZ " "
ENDL    .STRINGZ ""
HINT    .STRINGZ "Type a name and press Enter: "
NO      .STRINGZ "No Entry"
        .END