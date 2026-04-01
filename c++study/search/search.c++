#include <iostream>
#include <vector>
using namespace std;
//当数组不包含 target 时，最终  l和 f会分别指向首个大于、小于 target 的元素，i还是插入点
int binarySearch(vector<int> a, int target)
{
    int l = 0, r, m;
    r = a.size() - 1;
    int m = l + (r - l) / 2;
    while (l <= r)
    { // 闭区间
        if (target > a[m])
            l = m + 1;
        else if (target < a[m])
        {
            r = m - 1;
        }
        else
        {
            return m;
        }
    }
    return -1;
}
// 无重复
int binaryInsertPoint(vector<int> a, int target)
{
    int l = 0, r = a.size() - 1;
    int m = l + (r - l) / 2;
    while (l <= r)
    { // 闭区间
        if (target > a[m])
            l = m + 1;
        else if (target < a[m])
        {
            r = m - 1;
        }
        else
        {
            return m;
        }
    }
    return l; // 未查找到时，插入点是l
}
// 有重复，先找到最左边第一个重复的
int binaryInsertPoint1(vector<int> a, int target)
{
    int l = 0, r = a.size() - 1;
    int m = l + (r - l) / 2;
    while (l <= r)
    { // 闭区间
        if (target > a[m])
            l = m + 1;
        else if (target < a[m])
        {
            r = m - 1;
        }
        else
        {
            r = m - 1; /*当 nums[m] < target 或 nums[m] > target 时，说明还没有找到 target ，
                         因此采用普通二分查找的缩小区间操作，从而使指针 l和 r向 target 靠近。
                         当 nums[m] == target 时，说明小于 target 的元素在区间 [i,m-1]中，
                         因此采用 j=m-1来缩小区间，从而使指针 向小于 target 的元素靠近。*/
        }
    }
    return l; // 未查找到时，插入点是l
}