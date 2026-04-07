#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;



int mid(vector<int> &nums, int left, int mid, int right) {
    int l = nums[left], m = nums[mid], r = nums[right];
    if ((l <= m && m <= r) || (r <= m && m <= l))
        return mid; // m 在 l 和 r 之间
    if ((m <= l && l <= r) || (r <= l && l <= m))
        return left; // l 在 m 和 r 之间
    return right;
}

int   partition(vector<int>&a,int l,int r){
   int pivot=mid(a,l,(l+r)/2,r);
   swap(a[l],a[pivot]);
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


int   partition1(vector<int>&a,int l,int r){
    int pivot=a[r];
    while(l<r){
        while(l<r&&a[r]>a[pivot])
            r--;
        
        a[l]=a[r];
        while(l<r&&a[l]<=a[pivot])
            l++;
        
        a[r]=a[l];
        

    }
    a[l]=a[pivot];
    return l;
}

void quickSort(vector<int>&a,int l,int r){//
    
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