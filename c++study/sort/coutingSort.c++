#include<iostream>
#include<vector>
using namespace std;

void countingSort(vector<int>&a){//王道，可以用负数，对象结构体
    int m = a[0];
    int l=a[0];
    for (int num : a) {
        m = max(m, num);
        l = min(l, num);
    }
    int length=m-l+1;
    vector<int>b(length,0);
    for(int i=0;i<a.size();i++){
        b[a[i]-l]++;
    }
// 前缀和（王道核心）
    for(int i=1;i<length;i++){
        b[i]=b[i-1]+b[i];
    }
    vector<int>c(a.size());
   // 逆序遍历（王道核心）
    for(int n=a.size()-1;n>=0;n--){
        c[b[a[n]-l]-1]=a[n];//a[n]-l是对应的元素
        b[a[n]-l]--;
    }
    a=c;
}

void coutingSort1(vector<int>&a){//简单版，不稳定排序
    int m = 0;
    for (int num : a) m = max(m, num);
    vector<int>b(m+1,0);
    for(int i:a) b[i]++;

    int i=0;
    for(int n=0;n<m+1;n++){
        for(int j=0;j<b[n];j++,i++)
            a[i]=n;  // 你修复后是 n
    }
}

/* 计数排序 */
// 完整实现，可排序对象，并且是稳定排序
void countingSort2(vector<int> &nums) {
    // 1. 统计数组最大元素 m
    int m = 0;
    for (int num : nums) {
        m = max(m, num);
    }
    // 2. 统计各数字的出现次数
    // counter[num] 代表 num 的出现次数
    vector<int> counter(m + 1, 0);
    for (int num : nums) {
        counter[num]++;
    }
    // 3. 求 counter 的前缀和，将“出现次数”转换为“尾索引”
    // 即 counter[num]-1 是 num 在 res 中最后一次出现的索引
    for (int i = 0; i < m; i++) {
        counter[i + 1] += counter[i];
    }
    // 4. 倒序遍历 nums ，将各元素填入结果数组 res
    // 初始化数组 res 用于记录结果
    int n = nums.size();
    vector<int> res(n);
    for (int i = n - 1; i >= 0; i--) {
        int num = nums[i];
        res[counter[num] - 1] = num; // 将 num 放置到对应索引处
        counter[num]--;              // 令前缀和自减 1 ，得到下次放置 num 的索引
    }
    // 使用结果数组 res 覆盖原数组 nums
    nums = res;
}

int main(){
    vector<int>a={-1,-5,5,3,9,7};

    countingSort(a);
    for(int i:a)
    cout<<i<<" ";






}