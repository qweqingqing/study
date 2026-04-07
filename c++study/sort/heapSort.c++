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
void buildMaxHeap(vector<int>&a,int length){
    for(int i=length/2;i>0;i--){
        adjustMaxHeap(a,i,length);
    }
}
void sortHeap(vector<int>&a,int length){
    buildMaxHeap(a,length);
    for(int i=length;i>1;i--){
        swap(a[1],a[i]);
        adjustMaxHeap(a,1,i-1);

    }
   

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
    int length = a.size() - 1; // 有效长度 5

    cout << "排序前：";
    print(a, length);

    sortHeap(a, length);

    cout << "排序后：";
    print(a, length);
}