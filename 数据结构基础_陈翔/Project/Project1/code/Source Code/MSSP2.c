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
}
int MaxMatrixSum(int size){

    int ThisSum=0,MaxSum=a[0][0];                       //Used to record the sum of each matrix
                                   
    int x=0,y=0,m=0,n=0;                                        //Used to record the max matrix

    for(int i1=0;i1<size;i1++){
        for(int i2=0;i2<size;i2++){                     //Determine the position of the first number
            int temp[150]={0};                          //Design a array to hold the merged matrix
            
            for(int j1=i1;j1<size;j1++){
                ThisSum=0;
                for(int j2=i2;j2<size;j2++){            //Determine the position of the last number
                    temp[j2]+=a[j1][j2];
                    ThisSum+=temp[j2];
                    if(ThisSum>MaxSum){                 //Compare sum
                        x=i1;
                        y=i2;
                        m=j1;
                        n=j2;
                        MaxSum=ThisSum;
                    }
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
    printf("%d",MaxSum);
}