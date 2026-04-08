#include <iostream>
#include <vector>
using namespace std;

struct node
{
    int val;
    node *next;
};

int main()
{
    int rows = 3, cols = 4;
    vector<vector<int>> arr(rows, vector<int>(cols));

    int **a = new int *[rows];
    for (int i = 0; i < rows; i++)
    {
        a[i] = new int[cols];
    }
    for (int i = 0; i < rows; i++)
    {
        delete[] a[i];
    }
    // 再释放行指针
    delete[] a;
    /*  a        → 指向指针数组首地址
        a+1      → 指向指针数组里的下一个指针
        *(a+1)   → 拿到第1行的地址
        *(*(a+1)+2) → [1][2]
        
        int arr[3][4];
        int **a = arr;  // ❌ 错误！
        arr 是行指针 int (*)[4]
        a 是指针的指针 int**  类型不匹配！*/

    int *b[5];   // 数组内是int*
    int (*c)[5]; /*指针指向一个数组,指向二维数组的行
                 int(*a)[4],a指向一整行,*a指向一行的数组名，又是这一行的首元素
                 (*a)  → 第 0 行第 0 个元素的地址
                 *a + 1 → 第 0 行第 1 个元素的地址
                 *(*a +1) → 第 0 行第 1 个元素的值  */
}