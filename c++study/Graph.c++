#include <iostream>
#include<vector>

struct arcNode
{
int cur_number;
arcNode * next;
};

struct  vNode{
    int number;
    arcNode *firstnode;
};

struct Graph
{
    vNode* Graphlist[100];
    int vertexNum;
    int edgeNUm;
    /* data */
    Graph(){
        for (int i=0;i<100;i++){
            Graphlist[i]=nullptr;
        }
    }
    
};
void initGraph(Graph &G,int n){
    G.vertexNum=n;
    G.edgeNUm=0;
        for(int i=0;i<n;i++){
        G.Graphlist[i]=new vNode();
           G.Graphlist[i]->number=i;
           G.Graphlist[i]->firstnode=NULL;

        }

    }
int main(){

Graph L1;
initGraph(L1,9);
for(int i=0;i<9;i++){
    std::cout<<L1.Graphlist[i]->number<<std::endl;
}

}