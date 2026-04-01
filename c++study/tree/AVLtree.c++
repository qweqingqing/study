#include <iostream>
#include <algorithm>
using namespace std;

struct treeNode
{
    int number;
    treeNode *left_child;
    treeNode *right_child;
    int balance; // 平衡因子
};
typedef treeNode *Btree;

int get_hight(Btree T)
{ // 获取当前树的长度
    int hightl;
    int hightr;
    if (T == NULL)
    {
        return 0;
    }
    hightl = get_hight(T->left_child);
    hightr = get_hight(T->right_child);
    return max(hightl, hightr) + 1;
}

void update_balance(Btree T)
{ // 求平衡因子
    if (T == NULL)
        return;
    else
        T->balance = get_hight(T->right_child) - get_hight(T->left_child);
}


treeNode* find_rTree_min(Btree T){
    while(T->left_child!=NULL){
        T=T->left_child;
    }
    return T;
}

Btree rotateLL(Btree T)//替换原根节点，使成为右子树
{                                         // 右旋
    Btree newRoot = T->left_child;        // 替换原根节点
    T->left_child = newRoot->right_child; // 将新根节点的右子树移到原根节点的左子树
    newRoot->right_child = T;//右旋，使原根节点成为右子树
    update_balance(T);       // T的平衡因子
    update_balance(newRoot); // 新树的平衡因子
    return newRoot;
}

Btree rotateRR(Btree T)
{ // 左旋
    Btree newRoot = T->right_child;
    T->right_child = newRoot->left_child;
    newRoot->left_child = T;
    update_balance(T);
    update_balance(newRoot);
    return newRoot;
}

Btree rotateLR(Btree T)
{//旋转就是替换传入的节点
    T->left_child = rotateRR(T->left_child); // 左旋，转换成LL类型，
    return rotateLL(T);                      // 右旋
}

Btree rotateRL(Btree T)
{
    T->right_child = rotateLL(T->right_child); // 右旋
    return rotateRR(T);                        // 左旋
}

Btree insert_tree(Btree &T, int x)
{
    if (T == NULL)
    {
        T = new treeNode;
        T->number = x;
        T->left_child = NULL;
        T->right_child = NULL;
        T->balance = 0;
        return T; // 一定要返回，否则可以执行后面的代码
    }

    if (x > T->number)
        T->right_child = insert_tree(T->right_child, x); // 插入右子树
    else if (x < T->number)
        T->left_child = insert_tree(T->left_child, x); // 插入左子树
    else
    {
        cout << "已存在，无需插入" << endl;
        return T;
    }

    update_balance(T);

    if (abs(T->balance) > 1)
    
    {

        if (T->balance == -2)
        { // 左子树失衡
            if (x < T->left_child->number)
            {
                T = rotateLL(T);
                cout << "LL旋转" << endl;
            }
            else
            {
                T = rotateLR(T);
                cout << "LR" << endl;
            }
        }

        else if (T->balance == 2)
        { // 右子树失衡
            if (x < T->right_child->number)
            {
                T = rotateRL(T);
                cout << "RL" << endl;
            }
            else
            {
                T = rotateRR(T);
                cout << "RR" << endl;
            }
        }
    }
    return T;
}

void create_Tree(Btree &T, int a[], int n)
{
    T = NULL;
    int i = 0;
    while (i < n)
    {
        insert_tree(T, a[i]);
        i++;
    }
}

Btree delete_avlNode(Btree &T,int x){
    if(T==NULL){
        return NULL;
    }
    if(x>T->number){
        T->right_child=delete_avlNode(T->right_child,x);
    }
    else if(x<T->number){
        T->left_child=delete_avlNode(T->left_child,x);
    }
    else{
        if(T->left_child==NULL&&T->right_child==NULL){
            delete T;
            T=NULL;
        }
        else if(T->left_child==NULL){
            treeNode*temp=T;
            T=T->right_child;
            delete temp;
        }
        else if(T->right_child==NULL){
            treeNode*temp=T;
            T=T->left_child;
            delete temp;
        }   
        else{
            treeNode* mintemp=find_rTree_min(T->right_child);
            T->number=mintemp->number;
            T->right_child=delete_avlNode(T->right_child,mintemp->number);
        }
    }
        if(T==NULL){
            return NULL;
        }

        update_balance(T);

        if (abs(T->balance) > 1)
        {

        if (T->balance == -2)
        { // 左子树失衡
            if (get_hight(T->left_child->left_child)>=get_hight(T->left_child->right_child))
            {
                T = rotateLL(T);
                cout << "LL旋转" << endl;
            }
            else
            {
                T = rotateLR(T);
                cout << "LR" << endl;
            }
        }

        else if (T->balance == 2)
        { // 右子树失衡
            if (get_hight(T->right_child->right_child)>=get_hight(T->right_child->left_child))
            {
                T = rotateRR(T);
                cout << "RR" << endl;
            }
            else
            {
                T = rotateRL(T);
                cout << "RL" << endl;
            }
        }
    }
   return T;
}
    


void inOrder(Btree T)
{ // 中序遍历
    if (T == NULL)
    {
        return;
    }
    inOrder(T->left_child);
    cout << T->number << "  ";
    inOrder(T->right_child);
}

int main()
{
    Btree root = NULL;
    /*insert_tree(root, 10);//插入测试
    insert_tree(root, 20);
    cout << "插入30前：";
    inOrder(root);
    cout << endl;

    insert_tree(root, 30);
    cout << "插入30后：";
    inOrder(root);
    cout << endl;*/


    int a[6] = {15, 3, 7, 10, 9, 8};//create测试
    create_Tree(root, a, 6);
    inOrder(root);

    delete_avlNode(root, 7);
    cout << "删除 7 后中序遍历：" << endl;
    inOrder(root);

    return 0;
}
