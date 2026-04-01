#include<iostream>
#include<vector>
using namespace std;

int main(){
    int rows=3,cols=4;
    vector<vector<int>> arr(rows,vector<int>(cols));
    //vector<vector<int>> arr(rows,vector<int>(cols,5));
    int ** a=new int*[rows];
    for(int i=0;i<rows;i++){
        a[i]=new int[cols];
    }
    for (int i = 0; i < rows; i++) {
        delete[] a[i];
    }
        // 再释放行指针
    delete[] a;


}