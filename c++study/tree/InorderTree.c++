#include<iostream>
using namespace std;
struct Bitree {
	int data;
	Bitree* lchild, * rchild;
	Bitree(int val):data(val),lchild(nullptr),rchild(nullptr){}
};
using BiTree = Bitree*;
void inordervisit(BiTree T) {
	if (T != NULL) {
		inordervisit(T->lchild);
		cout << T->data << "  ";
		inordervisit(T->rchild);

	}

}

void createtree(BiTree &T) {
	// 构建二叉树结构：
  //        1
  //      /  \
    //   2    3
	//  / \  /
	// 4  5 6
	T= new Bitree(1);
	T->lchild = new Bitree(2);
	T->rchild = new Bitree(3);
	T->lchild->lchild = new Bitree(4);
	T->lchild->rchild = new Bitree(5);
	T->rchild->lchild = new Bitree(6);
}
void destory(BiTree &T) {
	if (T != nullptr) {
		destory(T->lchild);
		destory(T->rchild);
		delete T;
		T = nullptr;
	}
}


struct threadNode {
	int data;
	threadNode* lchild, * rchild;
	int ltag, rtag;
	threadNode(int val):data(val),lchild(nullptr),rchild(nullptr),ltag(0),rtag(0){}
};
typedef threadNode* thread;
threadNode* pre = NULL;


void visit(thread T) {

	if(T->lchild==NULL){//线索化左孩子
		T->lchild = pre;
		T->ltag = 1;
	}
	if (pre != NULL && pre->rchild == NULL) {//线索化右孩子
		pre->rchild = T;
		pre-> rtag = 1;
	}
	pre = T;
}

void inthread(thread T) {
	if (T!= NULL) {
		inthread(T->lchild);//如果是先序遍历要   if(pre->ltag==0)
		visit(T);
		inthread(T->rchild);
	}

}

void CreateThread(thread T) {
	
	if (T != NULL) {
		inthread(T);
		/*if (pre->rchild =NULL)
			pre->rtag = 1;*/
		pre->rchild = NULL;
		pre->rtag = 1;
	}

}

threadNode *select_rlchild(threadNode* T) {//查找最左节点
	if (T == NULL) return NULL;
	while (T->ltag == 0&&T!=NULL) {
		T = T->lchild;
	}
	return T;
}

threadNode* findInorderSucessor(threadNode* T) {//查找中序线索的后继
	if (T->rtag == 1)
		return T->rchild;
	else {
		return  select_rlchild(T->rchild);
	}
}


void InOrderTraverse_Thread(thread T) {
	thread p = T;
	// 1. 找到中序遍历的起点（最左节点）
	while (p != NULL && p->ltag == 0) {
		p = p->lchild;
	}
	// 2. 遍历：利用线索找后继
	while (p != NULL) {
		cout << p->data << " "; // 访问当前节点
		// 若右指针是线索（rtag=1），直接跳转到后继
		if (p->rtag == 1) {
			p = p->rchild;
		}
		else {
			// 否则，找右子树的最左节点（后继）
			p = p->rchild;
			while (p != NULL && p->ltag == 0) {
				p = p->lchild;
			}
		}
	}
}
void DestroyThreadTree(thread& T) {
	if (T == NULL) return;
	// 若ltag=0，说明是普通左子节点，递归释放
	if (T->ltag == 0) {
		DestroyThreadTree(T->lchild);
	}
	// 若rtag=0，说明是普通右子节点，递归释放
	if (T->rtag == 0) {
		DestroyThreadTree(T->rchild);
	}
	// 释放当前节点
	delete T;
	T = NULL;
}




void createtree1(thread& T) {
	// 构建二叉树结构：
  //        1
  //      /  \
    //   2    3
	//  / \  /
	// 4  5 6
	T = new threadNode(1);
	T->lchild = new threadNode(2);
	T->rchild = new threadNode(3);
	T->lchild->lchild = new threadNode(4);
	T->lchild->rchild = new threadNode(5);
	T->rchild->lchild = new threadNode(6);
	
}

int main() {
	/*BiTree root = nullptr;
	createtree(root);
	inordervisit(root);
	destory(root);*/
	thread root = nullptr;
	// 1. 构建普通二叉树
	createtree1(root);
	cout << "原始二叉树结构：\n";
	cout << "        1\n      /  \\\n     2    3\n    / \\  /\n   4  5 6\n";

	// 2. 中序线索化
	CreateThread(root);
	cout << "\n线索化后中序遍历结果：";
	InOrderTraverse_Thread(root); // 输出：4 2 5 1 6 3
	cout <<endl;
	threadNode* node4 = root->lchild->lchild;
	threadNode *p=findInorderSucessor(node4);
	cout << p->data;
	// 3. 释放内存
	DestroyThreadTree(root);

	return 0;

}
