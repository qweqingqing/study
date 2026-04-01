#include<iostream>
#include<vector>

using namespace std;

void selectionSort(vector<int> a){
    int n=a.size();
    for(int i=0;i<n-1;i++){
        int min=i;
        for(int j=i+1;j<n;j++){
            if(a[j]<a[min]){
                min=j;
            }
        }
        int temp;
        temp=a[i];
        a[i]=a[min];
        a[min]=temp;
    }
    for (auto i:a){
        cout<<i<<" ";
    }

}


int main(){

vector<int> a{5,7,3,2,8};
selectionSort(a);
}