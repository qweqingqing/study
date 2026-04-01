#include<iostream>
using namespace std;
struct tree1{

};

 struct treeNode{
    treeNode *r_child;
    treeNode *l_child;
    int number;
};
typedef treeNode *Btree;

treeNode *BSF_search(Btree T,int x){
    if(T==NULL){
        return NULL;
    }
    while(T!=NULL&&T->number!=x){
        if(x>T->number)T=T->r_child;
        else T=T->l_child;
    }
    return T;
}


int  BSF_insert(Btree &T,int x){
    if(T==NULL){
        T=new treeNode;
        T->number=x;
        T->l_child=NULL;
        T->r_child=NULL;
        return 1;
    }

     if(T->number==x){
        return -1;
    }
     if(x>T->number){
        return BSF_insert(T->r_child,x);//可以改成T->r_child=BSF_insert(T->R_child,x)，只要把int改成Btree
    }
    else if(x<T->number){
        return BSF_insert(T->l_child,x);
    }
    return 0;
}

treeNode* find_rTree_min(Btree T){
    while(T->l_child!=NULL){
        T=T->l_child;
    }
    return T;
}

void delete_Tree(Btree&T,int x){
    if(T==NULL){
        std::cout<<"值不存在" ;
        return ;
    }
    if(x>T->number){
        delete_Tree(T->r_child,x);
    }
    else if(x<T->number){
        delete_Tree(T->l_child,x);
    }
    else{
        if(T->l_child==NULL&&T->r_child==NULL){
            delete T;
            T=NULL;
        }
        else if(T->l_child==NULL){
            treeNode*temp=T;
            T=T->r_child;
            delete temp;
        }
        else if(T->r_child==NULL){
            treeNode*temp=T;
            T=T->l_child;
            delete temp;
        }   
        else{
            treeNode* mintemp=find_rTree_min(T);
            T->number=mintemp->number;
            delete_Tree(T->r_child,mintemp->number);
        }
        std::cout<<"删除成功";
    }
}


void  create_Tree(Btree &T,int a[],int n)
{   T=NULL;
    int i=0;
    while (i<n)
    {
        BSF_insert(T,a[i]);
        i++;
    }
    
    
}

void InOrderTraverse(Btree T) {
    if (T == nullptr) return;
    InOrderTraverse(T->l_child);
    cout << T->number << " ";
    InOrderTraverse(T->r_child);
}


int main(){
    int a[6]={45,24,53,45,12,24};
    Btree T=NULL;
    create_Tree(T,a,6);

    InOrderTraverse(T);
    delete_Tree(T,12);
    InOrderTraverse(T);
    
    return 0;
}