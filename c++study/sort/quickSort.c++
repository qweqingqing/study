#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int   partition(vector<int>&a,int l,int r){
    int i=l,j=r;
    while(i<j){
        while(i<j&&a[j]>=a[l]){
            j--;
        }
        while(i<j&&a[i]<=a[l]){
            i++;
        }
        swap(a[i],a[j]);

    }
    swap(a[l],a[i]);
    return i;
}
void quickSort(vector<int>&a,int l,int r){
    
    if(l>=r){
        return;
    }
    int pivot=partition(a,l,r);
    quickSort(a,l,pivot-1);
    quickSort(a,pivot+1,r);

    
}

int main(){

    vector<int>a{5,7,2,4,99};
    quickSort(a,0,a.size()-1);for(int i:a){
        cout<<i<<" ";
    }
}