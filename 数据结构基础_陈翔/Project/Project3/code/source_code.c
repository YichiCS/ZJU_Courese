#include<stdio.h>
#include<stdlib.h>
#define MAX 1000

struct Point{
    int number;
    int distance;
    int known;
    int path;
};
//Define the data type of the node, including the distance and the previous node

int M,N;
//Define the number of nodes and the number of edges

int output[MAX]={0};
//Array for storing results

int G[MAX][MAX]={0};
//Define the connection state of the graph

struct Point station0[MAX];
struct Point station1[MAX];
//Array for storing paths

int FindMin(struct Point station[M]);
int Find2ndMin();

int main(){

    scanf("%d %d",&M,&N);
    //Input M,N

    for(int i=0;i<N;i++){
        int x,y,d;
        scanf("%d %d %d",&x,&y,&d);
        G[x-1][y-1]=d;
        //Unidirectional path
    }
    //Save the state of the graph to array

    FindMin(station0);
    //Finding the minimum path

    Find2ndMin();
    //Finding the 2nd minimum path

}

int FindMin(struct Point station[M]){

    struct Point temp;

    for(int i=0;i<MAX;i++){
        station[i].number=i;
        station[i].distance=10000;
        station[i].known=0;
        station[i].path=-1;
    }
    station[0].distance=0;
    //Initialization

    while(1){

        int Min=10000,MinPos;
        for(int i=0;i<M;i++){
            if(station[i].distance<Min && station[i].known==0){
                temp=station[i];
                MinPos=i;
                Min=station[i].distance;
            }
        }
        //Find the unoperated node with the shortest distance

        if(Min==10000)  break;
        //If not, end the loop

        station[MinPos].known=1;
        for(int i=0;i<M;i++){
            if(G[temp.number][i]>0 && station[i].known==0 && station[i].distance>temp.distance+G[temp.number][i]){
                station[i].distance=temp.distance+G[temp.number][i];
                station[i].path=temp.number;
                //Update the distance of this point if the condition is met
            }
        }

    }
    
}

int Find2ndMin(){
    struct Point temp = station0[M-1];
    int Result[M],Min=station0[M-1].distance,Min2=99999999;


    while(temp.number!=0){

        int TempDis=G[temp.path][temp.number];
        G[temp.path][temp.number]=0;
        //Removing an edge from the shortest path

        FindMin(station1);
        //Finding the shortest path in a new graph

        if(station1[M-1].distance<Min2 && station1[M-1].distance>Min){
            
            Min2=station1[M-1].distance;

            for(int i=0;i<M;i++){
                Result[i]=-1;
            }

            int i=M-1;
            while(station1[i].path!=-1){
                Result[i]=station1[i].path;
                i=station1[i].path;
            }
        }
        //If the condition is met, save this path as the second shortest path

        G[temp.path][temp.number]=TempDis;
        temp=station0[temp.path];
        //Restore the removed edge

    }

    int i=M-1,j=0;
    printf("%d ",Min2);

    while(i!=-1){
        output[j]=i+1;
        i=Result[i];
        j++;
    }

    for(int k=j-1;k>=0;k--){
        printf("%d ",output[k]);
    }
    //Output second shortest path
    
}