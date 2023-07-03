#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

typedef struct Instr{
    char name[100];
    int line_n;
    struct Instr *next;
}Instr_t;

typedef struct Label{
    char name[100];
    Instr_t *line;
    struct Label *next;
}Label_h;

Instr_t* instr_head = NULL;
Instr_t* instr_tail = NULL;
int linenum;
Label_h* labtab_head = NULL;
Label_h* labtab_tail = NULL;

const char op_Instr[60][10] = {
    "ADD", "AND", "NOT", "LD", "LDR", "LDI", "LEA",
    "ST",  "STR", "STI", "TRAP",    
    "BR",  "JMP", "JSR", "RTI", ".ORIG",
    ".FILL",    ".BLKW",    ".STRINGZ", ".END",
    "GETC","OUT", "PUTS", "IN", "PUTSP", "HALT","JSRR","RET","BRn", "BRz", "BRp",
    "BRnz", "BRzp", "BRnp", "BRnzp",0
};

const char binValue[16][5] = {"0000","0001","0010","0011",
						      "0100","0101","0110","0111",
						      "1000","1001","1010","1011",
						      "1100","1101","1110","1111"
};

const char binVal_3[8][4] = {"000","001","010","011",
                             "100","101","110","111"
};

Label_h* ins_label( char* newlab ,Instr_t* line_ins){
    Label_h *p;
    p = (Label_h*)malloc(sizeof(Label_h));          
    strcpy( p->name , newlab);              //store the name of the label
    p->line = line_ins;                     //store the pointer to the instruction line
    p->next = NULL;
    if( ! labtab_head ){
        labtab_head = p; 
        labtab_head->next = NULL;           //create the head of the linked list 
    }else{
        labtab_tail->next = p;
    }
    labtab_tail = p;

    return labtab_head;
}

char* itoa_my(int value, char* str, int radix) {
    static char dig[] =
        "0123456789"
        "abcdefghijklmnopqrstuvwxyz";
    int n = 0, neg = 0;
    unsigned int v;
    char* p, *q;
    char c;
    if (radix == 10 && value < 0) {
        v = -value;
        neg = 1;
    }else
    {
        v = value;
    }
    do {
        str[n++] = dig[v%radix];
        v /= radix;
    } while (v);
    if (neg)
        str[n++] = '-';
    str[n] = '\0';
    for (p = str, q = p + (n-1); p < q; ++p, --q)
        c = *p, *p = *q, *q = c;
    return str;
}

void cal_Hex( char x ){
    if( x >= '0' && x <= '9' ){
            printf("%s",binValue[x-'0']);
        }else if(x >= 'a' && x <='f' ){
            printf("%s",binValue[x-'a'+10]);
        }else{
            printf("%s",binValue[x-'A'+10]);
        }
}

Instr_t* read_opcode(){
    Instr_t *p;
    char line[100],content[1000];
    while(1){
        gets(content);                          //read the new line
        char* firstc = content;
        while(1){
                if( *firstc == ' ' || *firstc == '\r' ){    
                    firstc++;
                }else{
                    break;                      //clear the extra blank space
                }
        }
        int test = sscanf(firstc,"%s",line);
        while(  test != EOF ){                  //check if one line is ended
            if( strcmp( line , op_Instr[19] ) == 0 ){
                return instr_head;      //op_Instr stores the opcodes' names
            }                                   //check if "END", 
                                                //to stop reading
            if( line[0] == ';' ){
                break;                          //check the comments
            }

            p = (Instr_t*)malloc(sizeof(Instr_t));
            strcpy( p->name , line);
            p->line_n = -1;
            p->next = NULL;
            if( ! instr_head ){
                instr_head = p; 
                instr_head->next = NULL;
            }else{
            instr_tail->next = p;               //create the linked list
            }
            instr_tail = p;
            if( *firstc == '\"' ){
                firstc += 2;
            }                        //if "STRINGZ.", jump 2 locations more
            firstc += strlen(line);  //the pointer jump to the next 
            
            while(1){
                if( *firstc == ' ' || *firstc == '\r' ){
                    firstc++;
                }else{
                    break;
                }                               //ignore the blank space
            }
            if( *firstc == '\"' ){
                test = sscanf(firstc+1,"%[^\"]%*c",line);
                if( test == 0 ){
                    line[0] = '\0';       //read the contents between the /"
                }
            }else{
                test = sscanf(firstc,"%s",line);  //test the next element
            }
        }
    }

}

int get_opcode(const char* str){
    int i;
    for( i = 0 ; op_Instr[i][0] != 0 ; i++ ){   
        if( strcmp( op_Instr[i] , str ) == 0 ){
            return i;
        }
    }
    return -1;
}

Instr_t *seek = NULL;

void Instr_NOT(){
    seek = seek->next;                //binVal_3 stores 3 bits characters 
    printf("1001%s",binVal_3[seek->name[1]-'0']);  //from 0 ~ 7   
    seek = seek->next;                              
    printf("%s111111\n",binVal_3[seek->name[1]-'0']);
}

void Instr_3opr1( int opnum ){
    if( opnum == 0 ){
        printf("0001");             //ADD
    }else if( opnum == 1 ){
        printf("0101");             //AND
    }
    seek = seek->next;
    printf("%s",binVal_3[seek->name[1]-'0']);
    seek = seek->next;
    printf("%s",binVal_3[seek->name[1]-'0']);
    seek = seek->next;
    if( seek->name[0] == 'R' ){
        printf("000%s",binVal_3[seek->name[1]-'0']);
    }else{
        int val;
        if( seek->name[1] == '-' ){
            if( seek->name[0] == '#' ){
               val = atoi( seek->name+2 );  //decimal system
            }else{                          //store in val
                sscanf(seek->name+2,"%x",&val);
            }
            val = 16-val;
            printf("11%s",binValue[val]);   //negative number
        }else{
            int val;
            if( seek->name[0] == '#' ){
               val = atoi( seek->name+1 ); 
            }else{
                sscanf(seek->name+1,"%x",&val);
            }
            printf("10%s",binValue[val]);
        }    
    } 
    printf("\n");
}

void Instr_3opr2( int opnum ){
    if( opnum == 4 ){
        printf("0110");
    }else if( opnum == 8 ){
        printf("0111");
    }
    seek = seek->next;
    printf("%s",binVal_3[seek->name[1]-'0']);
    seek = seek->next;
    printf("%s",binVal_3[seek->name[1]-'0']);
    seek = seek->next;                  //registers oprands
    int fill;
    if( seek->name[0] == '#' ){
        fill = atoi( seek->name+1 );    
    }else{                              //hexadecimal 
        if( seek->name[1] == '-' ){
            sscanf(seek->name+2,"%x",&fill);
            fill = - fill;
        }else{
            sscanf(seek->name+1,"%x",&fill);
        }
    }
    char s[32] = {0};
    itoa_my(fill,s,2);                  //gcc in PTA doesn't
    if( fill >= 0 ){                    //contain itoa, 
        int i;                          //redifine a function 
    for( i = 0 ; i < 6-strlen(s) ; i++ ){  //to solve this
        printf("0");
    }
        printf("%s\n",s);
    }else{
        printf("%s\n",s+26);            
    }
}
//itoa use 32 bits, so the program use pointer + 32-needed bits.
void Instr_2opr( int opnum ){
    if( opnum == 3 ){
        printf("0010");
    }else if( opnum == 5 ){
        printf("1010");
    }else if( opnum == 6 ){
        printf("1110");
    }else if( opnum == 7 ){
        printf("0011");
    }else if( opnum == 9 ){
        printf("1011");
    }
    Instr_t* seek1 = seek->next;
    int minus;
    printf("%s",binVal_3[seek1->name[1]-'0']);
    seek1 = seek1->next;
    if( seek1->name[0] == '#' ){
        minus = atoi( seek1->name+1 );
    }else{
        Label_h* p = labtab_head;
        while( strcmp(p->name,seek1->name) != 0 ){
            p = p->next;
        }
        Instr_t* term = p->line;
        minus = term->line_n - 1 - seek->line_n;
    }   
    char s[32] = {0};
    itoa_my(minus,s,2);
    if( minus >= 0 ){
        int i;
        for( i = 0 ; i < 9-strlen(s) ; i++ ){
            printf("0");
        }
        printf("%s\n",s);
    }else{
        printf("%s\n",s+23);
    }
    seek = seek1;
}

void Instr_BR( int opnum ){
    if( opnum == 11 || opnum == 34 ){
        printf("0000111");
    }else if( opnum == 28 ){
        printf("0000100");
    }else if( opnum == 29 ){
        printf("0000010");
    }else if( opnum == 30 ){
        printf("0000001");
    }else if( opnum == 31 ){
        printf("0000110");
    }else if( opnum == 32 ){
        printf("0000011");
    }else if( opnum == 33 ){
        printf("0000101");
    }
    Instr_t* seek1 = seek->next;
    int minus;
    if( seek1->name[0] == '#' ){
        minus = atoi( seek1->name+1 );
    }else{
        Label_h* p = labtab_head;
        while( strcmp(p->name,seek1->name) != 0 ){
            p = p->next;
        }
        Instr_t* term = p->line;
        minus = term->line_n - 1 - seek->line_n;
    } 
    char s[32] = {0};
    itoa_my(minus,s,2);
    if( minus >= 0 ){
        int i;
        for( i = 0 ; i < 9-strlen(s) ; i++ ){
            printf("0");
        }
        printf("%s\n",s);
    }else{
        printf("%s\n",s+23);
    }
    seek = seek1;
}

void Instr_TRAP(){
    seek = seek->next;
    printf("11110000");
    for( int i = 0 ; i < 3-strlen(seek->name) ; i++ ){
        printf("0000");
    }
    for( int i = 1 ; i < strlen(seek->name) ; i++ ){
        cal_Hex( seek->name[i] );
    }
    printf("\n");
}

void Instr_ORIG(){
    seek = seek->next;
    for( int i = 0 ; i < 5-strlen(seek->name) ; i++ ){
        printf("0000");
    }
    for( int i = 1 ; i < strlen(seek->name) ; i++ ){
        cal_Hex( seek->name[i] );
    }
    printf("\n");
}

void Instr_JMPSRR( int opnum ){
    if( opnum == 12 ){
        printf("1100");
    }else if( opnum == 26 ){
        printf("0100");
    }
    seek = seek->next;
    printf("000%s000000\n",binVal_3[seek->name[1]-'0']);
}

void Instr_JSR(){
    printf("01001");
    Instr_t* seek1 = seek->next;
    int minus;
    if( seek1->name[0] == '#' ){
        minus = atoi( seek1->name+1 );
    }else{
        Label_h* p = labtab_head;
        while( strcmp(p->name,seek1->name) != 0 ){
            p = p->next;
        }
        Instr_t* term = p->line;
        minus = term->line_n - 1 - seek->line_n;
    } 
    char s[32] = {0};
    itoa_my(minus,s,2);
    if( minus >= 0 ){
        int i;
        for( i = 0 ; i < 11-strlen(s) ; i++ ){
            printf("0");
        }
        printf("%s\n",s);
    }else{
        printf("%s\n",s+21);
    }
    seek = seek1;
}

void Instr_RTI(){
    printf("1000000000000000\n");
}

void Instr_FILL(){
    seek = seek->next;
    int fill;
    if( seek->name[0] == '#' ){
        fill = atoi( seek->name+1 );
        char s[32] = {0};
        itoa_my(fill,s,2);
        if( fill >= 0 ){
            int i;
            for( i = 0 ; i < 16-strlen(s) ; i++ ){
                printf("0");
            }
            printf("%s\n",s);
        }else{
            printf("%s\n",s+16);
        }
    }else{
        if( seek->name[1] == '-' ){
            sscanf(seek->name+2,"%x",&fill);
            fill = - fill;
            char s[32] = {0};
            itoa_my(fill,s,2);
            if( fill >= 0 ){
                int i;
                for( i = 0 ; i < 16-strlen(s) ; i++ ){
                    printf("0");
                }
                printf("%s\n",s);
            }else{
                printf("%s\n",s+16);
            }
        }else{
            for( int i = 0 ; i < 5-strlen(seek->name) ; i++ ){
            printf("0000");
            }
            for( int i = 1 ; i < strlen(seek->name) ; i++ ){
                cal_Hex( seek->name[i] );
            }
            printf("\n");
        }    
    }
}

void Instr_BLKW(){
    seek = seek->next;
    int i,fill = atoi( seek->name+1 );
    for( i = 0 ; i < fill ; i++ ){
        printf("0111011101110111\n");
    }
}

void Instr_STRINGZ(){
    seek = seek->next;
    int i;
    for( i = 0 ; seek->name[i] != '\0' ; i++ ){
        char s[32] = {0};
        itoa_my(seek->name[i],s,2);
        int j;
        for( j = 0 ; j < 16-strlen(s) ; j++ ){
            printf("0");
        }
        printf("%s\n",s);
    }
    printf("0000000000000000\n");
}

void seek_label(){
    seek = instr_head;
    int num = 0 , linenum = 0 ;
    while(seek != NULL ){
        num = get_opcode( seek->name );
        seek->line_n = linenum++;       //check the number of opcode
        switch( num ){
            case 0 :
            case 4 :
            case 8 : 
            case 1 : seek = seek->next;
                     seek = seek->next;
                     seek = seek->next;break;   //jump over 3 oprands 
            case 3 :
            case 5 :
            case 6 :
            case 7 :
            case 9 :
            case 2 : seek = seek->next;
                     seek = seek->next;break;   //2 oprands
            case 11:
            case 12:
            case 13:
            case 15:
            case 16:
            case 17:
            case 18:
            case 26:
            case 28:
            case 29:
            case 30:
            case 31:
            case 32:
            case 33:
            case 34:
            case 10: seek = seek->next;break;   //1 oprands
        }                          //the other with no oprand
        Instr_t *p = NULL;
        p = seek->next;
        if( p == NULL ){
            return;
        }
        if( num == 17 ){
            linenum += atoi( seek->name+1 )-1;  //BLKW. 
        }                             //add extra line number
        if( num == 18 ){                //STRINGZ.
            linenum += strlen( seek->name );
        }
        num = get_opcode( p->name );
        if( num < 0 ){
            ins_label( p->name , p->next );
            seek->next = p->next;
            free(p);                    //free the label
        }
        seek = seek->next;
    }
}


void seek_instr(){
    seek = instr_head;
    int num = 0;
    while(seek != NULL ){
        num = get_opcode( seek->name );
        switch( num ){
            case 0 :                                    //ADD
            case 1 : Instr_3opr1( num );break;          //AND 
            case 4 :                                    //LDR
            case 8 : Instr_3opr2( num );break;         //STR
            case 2 : Instr_NOT();break;                   //NOT
            case 3 :                                    //LD
            case 5 :                                    //LDI
            case 6 :                                    //LEA
            case 7 :                                    //ST
            case 9 : Instr_2opr( num );break;           //STI
            case 10: Instr_TRAP();break;
            case 11:                                    //BR
            case 28:
            case 29:
            case 30:
            case 31:
            case 32:
            case 33:
            case 34: Instr_BR( num );break;
            case 12:                                        //JMP
            case 26: Instr_JMPSRR( num );break;             //JSRR
            case 13: Instr_JSR();break;
            case 14: Instr_RTI();break;
            case 15: Instr_ORIG();break;
            case 16: Instr_FILL();break;
            case 17: Instr_BLKW();break;
            case 18: Instr_STRINGZ();break;
            case 20: printf("1111000000100000\n");break;    //GETC
            case 21: printf("1111000000100001\n");break;    //OUT
            case 22: printf("1111000000100010\n");break;    //PUTS
            case 23: printf("1111000000100011\n");break;    //IN
            case 24: printf("1111000000100100\n");break;    //PUTSP
            case 25: printf("1111000000100101\n");break;    //HALT
            case 27: printf("1100000111000000\n");break;   //RET
        }
        seek = seek->next;
    }
    
}

int main(){
    read_opcode();
    seek_label();
    seek_instr();
    


    system("pause");
}

