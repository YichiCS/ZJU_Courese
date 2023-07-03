#include<stdio.h>

int a[150][150];                                        //The matrix a
int MaxMatrixSum(int n);
int main(){

    int size;                                           //The size of the matrix                       

    scanf("%d",&size);
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            scanf("%d",&a[i][j]);
        }
    }                                                   //Store the matrix in a

    MaxMatrixSum(size);
    return 0;
}
int MaxMatrixSum(int size){

    int ThisSum=0,MaxSum=a[0][0];                       //Used to record the sum of each matrix
                                   
    int x=0,y=0,m=0,n=0,start=0;                                //Used to record the max matrix

    for(int i=0;i<size;i++){
        int temp[150]={0};
        for(int j=i;j<size;j++){
            ThisSum=0;
            start=0;
            for(int k=0;k<size;k++){     
                temp[k]+=a[j][k];
                ThisSum+=temp[k];
                if(ThisSum>MaxSum){
                    MaxSum=ThisSum;
                    x=i;
                    m=j;
                    n=k;
                    y=start;
                }  
                else if(ThisSum<0){
                    ThisSum=0;
                    start=k+1;
                }  
            }
       }
    }

    for(int i=x;i<=m;i++){
        for(int j=y;j<=n;j++){
            printf("%d ",a[i][j]);
        }
        printf("\n");
    }                                                    //Print the result
    printf("%d\n",MaxSum);
}
