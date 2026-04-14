#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

/* 获取元素 num 的第 k 位，其中 exp = 10^(k-1) */
int digit(int num, int exp) {
    // 传入 exp 而非 k 可以避免在此重复执行昂贵的次方计算
    return (num / exp) % 10;
}

/* 计数排序（根据 nums 第 k 位排序） */
void countingSortDigit(vector<int> &nums, int exp) {//基于计数排序
    // 十进制的位范围为 0~9 ，因此需要长度为 10 的桶数组
    vector<int> counter(10, 0);
    int n = nums.size();
    // 统计 0~9 各数字的出现次数
    for (int i = 0; i < n; i++) {
        int d = digit(nums[i], exp); // 获取 nums[i] 第 k 位，记为 d
        counter[d]++;                // 统计数字 d 的出现次数
    }
    // 求前缀和，将“出现个数”转换为“数组索引”
    for (int i = 1; i < 10; i++) {
        counter[i] += counter[i - 1];
    }
    // 倒序遍历，根据桶内统计结果，将各元素填入 res
    vector<int> res(n, 0);
    for (int i = n - 1; i >= 0; i--) {
        int d = digit(nums[i], exp);
        int j = counter[d] - 1; // 获取 d 在数组中的索引 j
        res[j] = nums[i];       // 将当前元素填入索引 j
        counter[d]--;           // 将 d 的数量减 1
    }
    // 使用结果覆盖原数组 nums
    for (int i = 0; i < n; i++)
        nums[i] = res[i];
}

/* 基数排序 */
void radixSort(vector<int> &nums) {
    // 获取数组的最大元素，用于判断最大位数
    int m = *max_element(nums.begin(), nums.end());
    // 按照从低位到高位的顺序遍历
    for (int exp = 1; exp <= m; exp *= 10)
        // 对数组元素的第 k 位执行计数排序
        // k = 1 -> exp = 1
        // k = 2 -> exp = 10
        // 即 exp = 10^(k-1)
        countingSortDigit(nums, exp);
}


// 队列版基数排序
void radixSortQueue(vector<int>& nums) {
    if (nums.empty()) return;

    // 10个队列，对应0~9号桶
    queue<int> bucket[10];

    // 找最大值，确定最高位
    int maxVal = *max_element(nums.begin(), nums.end());

    // 从低位到高位
    for (int exp = 1; exp <= maxVal; exp *= 10) {

        // 1. 入队：按当前位分到对应桶
        for (int x : nums) {
            int d = digit(x, exp);
            bucket[d].push(x);
        }

        // 2. 出队：按0~9顺序收集回原数组
        int idx = 0;
        for (int i = 0; i < 10; ++i) {
            while (!bucket[i].empty()) {
                nums[idx++] = bucket[i].front();
                bucket[i].pop();
            }
        }
    }
}

int main(){
    vector<int>a={7456,7543,2343,8765,3456,8765};
    radixSort(a);
    for(int i:a)
        cout<<i<<" ";

}