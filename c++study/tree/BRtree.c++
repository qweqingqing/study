#include<iostream>

using namespace std;

#define RED 1    // 红色
#define BLACK 0  // 黑色
struct treeNode{
    int color;
    int number;
    treeNode *r_child,*l_child,*parent;
    
};
typedef treeNode * Btree;



Btree searchNode(Btree T, int x){
    while(T!=NULL && T->number!=x){
        if(x > T->number) T = T->r_child;
        else T = T->l_child;
    }
    return T; // 找到返回节点，没找到返回NULL
}

// ==============================================
// 左旋函数（对节点 x 进行左旋）
// 作用：让 x 的右孩子 y 上位，x 变成 y 的左孩子
// ==============================================
void leftRotate(Btree &root, Btree x) {
    Btree y = x->r_child;        // 1. 把 y 设为 x 的右孩子（旋转后新的父节点）

    x->r_child = y->l_child;     // 2. 将 y 的左子树 挂到 x 的右孩子位置

    if (y->l_child != NULL)      // 3. 如果 y 有左孩子
        y->l_child->parent = x;  // 4. 把这个孩子的父节点设为 x（维护指针）

    y->parent = x->parent;       // 5. y 继承 x 原来的父节点

    // 6. 让 x 的父节点指向 y（关键！必须判断 x 是左/右/根）
    if (x->parent == NULL)       // 如果 x 是整棵树的根节点
        root = y;                // 旋转后 y 变成新根
    else if (x == x->parent->l_child)  // 如果 x 是父节点的左孩子
        x->parent->l_child = y;        // 父节点的左孩子改为 y
    else                        // 如果 x 是父节点的右孩子
        x->parent->r_child = y;        // 父节点的右孩子改为 y

    y->l_child = x;             // 7. x 变成 y 的左孩子
    x->parent = y;              // 8. x 的父节点设为 y（完成旋转）
}

// ==============================================
// 右旋函数（对节点 x 进行右旋）
// 作用：让 x 的左孩子 y 上位，x 变成 y 的右孩子
// ==============================================
void rightRotate(Btree &root, Btree x) {
    Btree y = x->l_child;        // 1. 把 y 设为 x 的左孩子（旋转后新的父节点）

    x->l_child = y->r_child;     // 2. 将 y 的右子树 挂到 x 的左孩子位置

    if (y->r_child != NULL)      // 3. 如果 y 有右孩子
        y->r_child->parent = x;  // 4. 把这个孩子的父节点设为 x（维护指针）

    y->parent = x->parent;       // 5. y 继承 x 原来的父节点

    // 6. 让 x 的父节点指向 y（关键！必须判断 x 是左/右/根）
    if (x->parent == NULL)       // 如果 x 是整棵树的根节点
        root = y;                // 旋转后 y 变成新根
    else if (x == x->parent->l_child)  // 如果 x 是父节点的左孩子
        x->parent->l_child = y;        // 父节点的左孩子改为 y
    else                        // 如果 x 是父节点的右孩子
        x->parent->r_child = y;        // 父节点的右孩子改为 y

    y->r_child = x;             // 7. x 变成 y 的右孩子
    x->parent = y;              // 8. x 的父节点设为 y（完成旋转）
}
// ==============================================
// 红黑树插入修复（解决双红冲突）
// 口诀：红叔染色，黑叔旋转
// ==============================================
void insertFixUp(Btree &root, Btree z) {
    // 循环条件：父节点存在 且 父节点是红色 → 出现双红，需要修复
    while (z->parent != NULL && z->parent->color == RED) {
        Btree p = z->parent;     // p = z 的父节点
        Btree g = p->parent;     // g = z 的祖父节点（一定存在）

        // ======================
        // 父节点是祖父的左孩子
        // ======================
        if (p == g->l_child) {
            Btree uncle = g->r_child;  // 叔叔节点 = 祖父的右孩子

            // ----------------------
            // 情况1：叔叔是红色 → 只染色
            // ----------------------
            if (uncle != NULL && uncle->color == RED) {
                p->color = BLACK;      // 父变黑
                uncle->color = BLACK;  // 叔叔变黑
                g->color = RED;        // 祖父变红
                z = g;                 // z 上移到祖父，继续检查
            }

            // ----------------------
            // 情况2：叔叔是黑色 → 旋转+染色
            // ----------------------
            else {
                // LR 型：z 是右孩子 → 先左旋父节点
                if (z == p->r_child) {
                    z = p;
                    leftRotate(root, z);
                    p = z->parent;   // 旋转后更新父节点
                    g = p->parent;   // 旋转后更新祖父节点
                }

                // LL 型：右旋祖父节点
                rightRotate(root, g);
                p->color = BLACK;    // 父节点变黑
                g->color = RED;      // 祖父节点变红
            }
        }

        // ======================
        // 父节点是祖父的右孩子（对称逻辑）
        // ======================
        else {
            Btree uncle = g->l_child;  // 叔叔节点 = 祖父的左孩子

            // ----------------------
            // 情况1：叔叔是红色 → 只染色
            // ----------------------
            if (uncle != NULL && uncle->color == RED) {
                p->color = BLACK;
                uncle->color = BLACK;
                g->color = RED;
                z = g;
            }

            // ----------------------
            // 情况2：叔叔是黑色 → 旋转+染色
            // ----------------------
            else {
                // RL 型：z 是左孩子 → 先右旋父节点
                if (z == p->l_child) {
                    z = p;
                    rightRotate(root, z);
                    p = z->parent;
                    g = p->parent;
                }

                // RR 型：左旋祖父节点
                leftRotate(root, g);
                p->color = BLACK;
                g->color = RED;
            }
        }
    }

    root->color = BLACK;  // 根节点永远强制为黑色
}

// ==============================================
// 红黑树插入节点（二叉搜索树插入 + 修复）
// ==============================================
Btree insertNode(Btree &root, int key) {
    Btree z = new treeNode;    // 创建新节点
    z->number = key;           // 赋值
    z->l_child = z->r_child = NULL;
    z->parent = NULL;
    z->color = RED;            // 新节点一定是红色

    Btree y = NULL;   // y 保存插入位置的父节点
    Btree x = root;   // x 用来遍历查找

    // 1. 找到插入位置
    while (x != NULL) {
        y = x;
        if (key == x->number) return NULL;  // 重复值不插入
        if (key < x->number) x = x->l_child;
        else x = x->r_child;
    }

    z->parent = y;  // 设置父节点

    // 2. 将节点 z 接入树
    if (y == NULL)        // 空树，z 是根
        root = z;
    else if (key < y->number)
        y->l_child = z;
    else
        y->r_child = z;

    insertFixUp(root, z); // 3. 插入后修复红黑树规则
    return z;
}
// 中序遍历（验证：输出 节点值(颜色)）
void inOrder(Btree T) {
    if (!T) return;
    inOrder(T->l_child);
    cout << T->number << "(" << (T->color ? "红":"黑") << ") ";
    inOrder(T->r_child);
}

// 测试主函数
int main() {
    Btree root = NULL;
    insertNode(root, 10);
    insertNode(root, 20);
    insertNode(root, 5);
    insertNode(root, 15);
    insertNode(root, 25);
    insertNode(root, 30);

    inOrder(root);
    return 0;
}