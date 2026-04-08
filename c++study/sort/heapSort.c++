#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;



void adjustMaxHeap(vector<int>&a,int k,int length){
    int temp;
    temp=a[k];
    for(int i=k*2;i<=length;i*=2){
        if(i<length&&a[i]<a[i+1])
            i++;
        if(temp>a[i])
        break;
        else{
            a[k]=a[i];
            k=i;
        }
    }
    a[k]=temp;
}

void adjustMinHeap(vector<int>&a,int k,int length){
    int temp;
    temp=a[k];
    for(int i=k*2;i<=length;i*=2){
        if(i<length&&a[i]>a[i+1])
            i++;
        if(temp<a[i])
        break;
        else{
            a[k]=a[i];
            k=i;
        }
    }
    a[k]=temp;
}


void buildMinHeap(vector<int>&a,int length){
    for(int i=length/2;i>0;i--){
        adjustMinHeap(a,i,length);
    }
}
void buildMaxHeap(vector<int>&a,int length){
    for(int i=length/2;i>0;i--){
        adjustMaxHeap(a,i,length);
    }
}
void sortMaxHeap(vector<int>&a,int length){
    buildMaxHeap(a,length);
    for(int i=length;i>1;i--){
        swap(a[1],a[i]);
        adjustMaxHeap(a,1,i-1);
    }
   

}
void sortMinHeap(vector<int>&a,int length){
    buildMinHeap(a,length);
    for(int i=length;i>1;i--){
        swap(a[1],a[i]);
        adjustMinHeap(a,1,i-1);
    }
   
}

void insertMaxHeap(vector<int>&a,int val){
    a.push_back(val);
    int i=a.size()-1;
    while(i>1&&a[i]>a[i/2]){
        swap(a[i],a[i/2]);
        i/=2;
    }
}
void deleteMaxHeap(vector<int>& a, int pos, int& length) {
    // 用最后一个元素覆盖要删除的位置
    a[pos] = a[length];
    length--;        // 堆长度减1

    // 然后向下调整堆
    adjustMaxHeap(a, pos, length);
}

void print(vector<int>& a, int length) {
    for (int i = 1; i <= length; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
}

int main() {
    // 堆排序从下标 1 开始，下标 0 空置
    vector<int> a = {0, 5, 7, 3, 2, 8};
    vector<int> b = {0, 5, 7, 3, 2, 8};
    int length = a.size() - 1; // 有效长度 5
    buildMaxHeap(a, length);
    cout << "建堆后：";
    print(a, length);

    // 插入元素 10
    insertMaxHeap(a, 10);
    length++; // 插入后长度+1
    cout << "插入 10 后：";
    print(a, length);

    // 删除位置 3 的元素
    deleteMaxHeap(a, 3, length);
    cout << "删除下标 3 后：";
    print(a, length);

    // 排序
    sortMaxHeap(a, length);
    cout << "最终排序后：";
    print(a, length);
}