#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

void merge(vector<int>&a,int l,int mid,int r){
    vector<int>c;
    c.reserve(a.size());
    c.insert(c.end(),a.begin(),a.end());
    int i,j,k;
    for( i=l,j=mid+1,k=i;i<=mid&&j<=r;k++){
        if(c[i]<c[j]){
            a[k]=c[i++];
            
        }
        else{
            a[k]=c[j++];
        }
            
    }
    while (i<=mid) a[k++]=c[i++];
    while (j<=r)a[k++]=c[j++];

}

void mergeSort(vector<int>&a,int l,int r){
    if(l<r){
        int mid=(l+r)/2;
        mergeSort(a,l,mid);
        mergeSort(a,mid+1,r);
        merge(a,l,mid,r);

    }
}
int main() {
    vector<int> arr = {5, 2, 9, 1, 3, 7};

    cout << "排序前：";
    for (int num : arr) cout << num << " ";
    cout << endl;

    mergeSort(arr, 0, arr.size() - 1);  // 右边界是 size-1！

    cout << "排序后：";
    for (int num : arr) cout << num << " ";
    cout << endl;

    return 0;
}