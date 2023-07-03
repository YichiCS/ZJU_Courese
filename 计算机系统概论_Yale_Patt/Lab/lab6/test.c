#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

int num;
int finish=0;
int line=0;
int LABEL_n=2;
int bin[300][16]={0};

char opcode[10];
char operand[10];
char LABEL_num[300][20];
int LABEL_pos[300][1];

char op[40][10]={
    "BR", "ADD", "LD", "ST", "JSR", "AND", "LDR", "STR", "RTI", "NOT", "LDI",
    "STI", "JMP","@@", "LEA", "TRAP",
    ".ORIG", ".FILL", ".BLKW", ".STRINGZ", ".END",
    "GETC", "OUT", "PUTS", "IN", "PUTSP", "HALT",
    "JSRR","RET",
    "BRp", "BRz", "BRzp", "BRn", "BRnp", "BRnz", "BRnzp"
};
int get_lable(char* name,int me){
    if(me==0){
    	for(int i=2;i<LABEL_n;i++){
    		if(strcmp(name,LABEL_num[i])==0){
    			LABEL_pos[i][0]=line;
    			return 0;
			}
		}
		strcat(LABEL_num[LABEL_n],name);
		LABEL_pos[LABEL_n][0]=line;
		LABEL_n++;
		return 0;
	}
	else{
		for(int i=2;i<LABEL_n;i++){
    		if(strcmp(name,LABEL_num[i])==0){
    			num=i;
    			return 0;
			}
		}
		strcat(LABEL_num[LABEL_n],name);
		num=LABEL_n;
		LABEL_n++;
		return 0;
	}
}


int get_opc(){
    strcpy(opcode,"");
    scanf("%s",opcode);
    for(int i=0;i<41;i++){
        if(strcmp(opcode,op[i])==0){
            return i;
        }
    }
    return -1;
}

int get_ope(){
    num=0;
    int i=1;
    int mode=0;
    strcpy(operand,"");
    scanf("%s",operand);
    if(operand[0]=='R' && operand[1]>='0' && operand[1]<='9') mode=1;   //Reg
    if(operand[0]=='#') mode=10;                                        //Dec
    if(operand[0]=='x') mode=16;                                        //Hex
    if(mode!=0){
        while(1){
            if(operand[i]>='0' && operand[i]<='9'){
                num=num*abs(mode)+operand[i]-'0';
            }
            else if(operand[i]>='A' && operand[i]<='F'){
               num=num*abs(mode)+operand[i]-'A'+10;
            }
            else if(operand[i]=='-') mode=-mode;
            else    return mode;
            i++;
        }   
    }
    else{
        get_lable(operand,1);
        return mode;
    }    
}

void write(int a,int b,int n,int mode){
    int t;
    if(mode < 0){
        n=pow(2,b-a+1)-n;
    }
    for(int i=b;i>=a;i--){
        t=n%2;
        bin[line][i]=t;
        n/=2;
    }
}

void type1(int op_num){
    int mode;
    write(0,3,op_num,1);
    mode=get_ope();
    write(4,6,num,mode);
    mode=get_ope();
    write(7,9,num,mode);
    mode=get_ope();
    if(mode==1){
        write(13,15,num,mode);
    }
    else{
        if(op_num<=5){
            write(10,10,1,1);
            write(11,15,num,mode);
        }   
        else{
            write(10,15,num,mode);
        }
    }
}
void type2(int op_num){
    int mode;
    write(0,3,op_num,1);
    mode=get_ope();
    write(4,6,num,mode);
    mode=get_ope();
    write(7,9,num,mode);
    write(10,15,63,1);
}
void type3(int op_num){
    int mode;
    write(0,3,op_num,1);
    mode=get_ope();
    write(4,6,num,mode);
    mode=get_ope();
    if(mode!=0)    write(7,15,num,mode);
    else    bin[line][7]=num;

}

void type4(int op_num){
    int mode;
    write(0,3,4,1);
    if(op_num==4){
        write(4,4,1,1);
        mode=get_ope();
        if(mode!=0)    write(5,15,num,mode);
        else bin[line][5]=num;
    } 
    else{
        mode=get_ope();
        write(7,9,num,mode);
    }  
}

void type5(int op_num){
    int mode;
    write(0,3,12,1);
    if(op_num==12){
        mode=get_ope();
        write(7,9,num,mode);
    }
    else    write(7,9,7,1);
}

void type6(int op_num){
    write(0,3,8,1);
}

void type7(int op_num){
    int mode;
    write(0,3,15,1);
    if(op_num==15){
        mode=get_ope();
        write(8,15,num,mode);
    }
    else    write(8,15,op_num+11,1);
}

void type8(int op_num){
    int mode;
    write(0,3,0,1);
    if(op_num!=0)	write(4,6,op_num-28,1);
    else	write(4,6,7,1);
    mode=get_ope();
    if(mode!=0)    write(7,15,num,mode);
    else bin[line][7]=num;
}

void orig_fill(int op_num){
    int mode;
    mode=get_ope();
    write(0,15,num,mode);
}
void blkw(int op_num){
    int mode;
    mode=get_ope();
    for(int i=1;i<=num;i++){
        write(0,15,30583,1);
        line++;
    }
    line--;
}

void stringz(int op_num){
    int st;
    char str[100];
    gets(str);
    for(int i=0;i<strlen(str)-1;i++){
        if(str[i]=='"'){
            st=i+1;
            break;
        }
    }
    for(int i=st;i<strlen(str)-1;i++){
        write(0,15,str[i]-'0'+48,1);
        line++;
    }
}


void op_choose(int op_num){
    switch(op_num){
        case 1:
        case 5:
        case 6:
        case 7: type1(op_num);break;    //ADD,AND,LDR,STR

        case 9: type2(op_num);break;    //NOT

        case 2:
        case 3:
        case 10:
        case 11:
        case 14:type3(op_num);break;    //LD,ST,LDI,STI,LEA

        case 4:
        case 27:type4(op_num);break;    //JSR,JSRR

        case 12:
        case 28:type5(op_num);break;    //JMP,RET

        case 8: type6(op_num);break;    //RTI

        case 15:
        case 21:
        case 22:
        case 23:
        case 24:
        case 25:
        case 26:type7(op_num);break;    //TRAP...

        case 29:
        case 30:
        case 31:
        case 32:
        case 33:
        case 34:
        case 35:
        case 0:type8(op_num);break;    //BR...

        case 16:
        case 17:orig_fill(op_num);break;
        case 18:blkw(op_num);break;
        case 19:stringz(op_num);break;
        case 20:finish=1;break;
    }
}


void trans(){
    int op_num;
    while(1){
        op_num=get_opc();
        if(op_num==-1){
            get_lable(opcode,0);
            op_num=get_opc();
        }
        op_choose(op_num);
        line++;
        if(finish==1)   break;
    }
}

void LABEL_write(int a,int b,int n,int line){
    int t;
    if(n < 0){
        n=pow(2,b-a+1)+n;
    }
    for(int i=b;i>=a;i--){
        t=n%2;
        bin[line][i]=t;
        n/=2;
    }
}

void LABEL_change(){
    for(int i=0;i<line-1;i++){
        for(int j=0;j<16;j++){
            if(bin[i][j]>1){
                LABEL_write(j,15,LABEL_pos[bin[i][j]][0]-i-1,i);
            }
        }
    }
}

void output(){
    for(int j=0;j<line-1;j++){	
    	for(int i=0;i<16;i++){
    		printf("%d",bin[j][i]);
		}
		printf("\n");
	}
}

int main(){
    trans();
    LABEL_change();
    output();
}