        .ORIG X3000

        LD R0,#255      ;将数据加载到R0
        AND R1,R1,#0    ;初始化R1，用于存放掩码
        AND R2,R2,#0    ;初始化R2，用于存放结果
        AND R3,R3,#0    ;初始化R3，用于存放掩码与数据的与运算结果
        AND R4,R4,#0    ;初始化R4，用于存放掩码的相反数的补码
        AND R5,R5,#0    ;初始化R5，用于计数器

        ADD R1,R1,#15
        ADD R5,R5,#-13  ;计数器初始值

        AND R3,R0,R1    ;获得掩码与数据的与运算结果
        NOT R4,R1       
        ADD R4,R4,#1    ;获得掩码的反码的补码
        ADD R3,R3,R4    ;计算结果

JUDGE   BRZ RESULT;判断结果是否为0
        ADD R5,R5,#1    ;R5自增
        BRZ FINAL;判断R5是否为0

        ADD R1,R1,R1    ;掩码前移
        AND R3,R0,R1    ;获得掩码与数据的与运算结果
        NOT R4,R1       
        ADD R4,R4,#1    ;获得掩码的反码的补码
        ADD R3,R3,R4    ;计算结果

        BRNZP JUDGE     ;返回判断语句

RESULT  ADD R2,R2,#1
FINAL   HALT
        .END