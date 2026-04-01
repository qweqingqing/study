#include<iostream>
#include<vector>

using namespace std;

void insertSort(int *a,int n){
for(int i=1;i<n;i++){
       
            int j;
            int temp;  
            temp=a[i];
            for( j=i-1;j>=0&&a[j]>temp;j--){
                a[j+1]=a[j];
            } 
            a[j+1]=temp;
        
    }
    
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout<<endl;
}


void  XRSort( int *a,int n){
int d;
    for(d=n/2;d>=1;d=d/2){
        for(int i=d;i<n;i++){
            int j,temp;
                temp=a[i];
                for(j=i-d;j>=0&&a[j]>temp;j-=d){
                    a[j+d]=a[j];
                }
            a[j+d]=temp;
            
        }

    }
for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
cout<<endl;
}

void bubleSort(int* a,int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n-i-1;j++){
            int temp;
            if(a[j+1]<a[j]){
                temp=a[j];
                a[j]=a[j+1];
                a[j+1]=temp;
            }
        }

    }
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }

cout<<endl;
}



int main(){

    int a[]={5,7,9,4,6};
    int n=5;
    
    insertSort(a,n);
    int b[]={5,7,9,4,6};
    XRSort(b,n);
    int c[]={5,7,9,4,6};
    bubleSort(c,n);
}