#include <iostream>
#include <vector>
#include <array>
#include "D:/UE_Project/StudyCpp/SortAlgorithmTest/Private/SortAlgorithmTest.h"
#include <algorithm>
using namespace std;


//冒泡排序思路：
/*
* 核心思路分步拆解
遍历数组
从数组的第一个元素开始，依次比较每一对相邻元素（arr[j]和arr[j+1]）。

交换逆序对
如果当前元素 arr[j] > arr[j+1]（逆序），则交换它们的位置，确保较大的元素“右移”。

一轮冒泡完成
每完成一轮遍历，最大的未排序元素会被推到当前未排序区间的末尾，因此下一轮遍历可以减少一次比较。

提前终止优化
如果某一轮遍历中没有发生任何交换，说明数组已经有序，直接终止排序。
 */
void SortClass::BubbleSort(vector<int>& arr, int size)
{
    for(int it = 0;it < size - 1;it++)
    {
        for(int it2 = it +1;it2 < size;it2++)
        {
            if(arr[it] > arr[it2])
            {
                swap(arr[it] , arr[it2]);  //交换左右
                //内层循环会一直更改指向的位置，然后会不断更新外层循环指向的位置，这样到内层循环结束时，能保证最小的数在开头
            }
        }
    }
    for(auto Rit : arr)
    {
        cout<<Rit<<" ";
    }
    cout<<'\n';
}

/*冒泡排序，时间复杂度通常是O(n^2)（要写嵌套循环）*/

/*选择排序：
* 核心思路分步拆解
划分两个区间

已排序区间：初始为空，位于数组左端

未排序区间：初始为整个数组，位于右端

寻找最小值
每一轮遍历未排序区间，找到其中最小的元素。

交换位置
将找到的最小元素与未排序区间的第一个元素交换位置，使其加入已排序区间。

区间收缩
每完成一轮操作，已排序区间长度+1，未排序区间长度-1。

手动模拟示例
以数组 [29, 10, 14, 37, 13] 为例：

第一轮（未排序区间：全部元素）：

找到最小值 10（索引1）

与第一个元素 29 交换 → [10, 29, 14, 37, 13]

第二轮（未排序区间：索引1-4）：

找到最小值 13（索引4）

与第二个元素 29 交换 → [10, 13, 14, 37, 29]

第三轮（未排序区间：索引2-4）：

找到最小值 14（索引2）

无需交换 → [10, 13, 14, 37, 29]

第四轮（未排序区间：索引3-4）：

找到最小值 29（索引4）

与第四个元素 37 交换 → [10, 13, 14, 29, 37]

相当于每完成一次排序，缩小搜索的范围
难点在于如何找到最小的数，窗口要划定找到最小数的次数
 */
void SortClass::SelectSort(vector<int>& arr, int size)
{
    for(int it = 0; it < size - 1; it++)
    {
        int index = it;
        int min_num = arr[it];  //最小的数
        for(int it2 = it + 1; it2 < size; it2++)
        {
            if(arr[it2] < min_num)
            {
                min_num = arr[it2];
                index = it2;  //找到并记录最小的数的索引
            }
        }
        swap(arr[it] , arr[index]);  //然后最后与it个数进行交换
    }
    for(auto Rit : arr)
    {
        cout<<Rit<<" ";
    }
    cout<<'\n';
}

/*选择排序，核心操作：扫描最小，单次交换，交换次数最多是n - 1次也就是都要交换的情况
 * 时间复杂度最佳情况为O(n ^ 2)相较于冒泡排序，冒泡排序最优可达到O(n)
* 为什么选择排序不稳定？
示例：排序 [5, 3, 5, 2] 时，第一个 5 会和 2 交换，导致两个 5 的相对顺序改变。
 */


/*插入排序
* 核心思路分步拆解
划分两个区间

已排序区间：初始为第一个元素（单个元素天然有序）

未排序区间：从第二个元素到末尾

抓取元素
每次从未排序区间取出第一个元素（记为key）。

逆向扫描定位
在已排序区间中从后向前扫描，找到第一个不大于key的元素。

插入元素
将key插入到该位置后方，过程中将比key大的元素逐个后移腾出空位。

手动模拟示例
以数组 [12, 11, 13, 5, 6] 为例：

初始状态：已排序区间 [12]，未排序区间 [11,13,5,6]

取出11，向前比较12 → 后移 → 插入 → [11,12 | 13,5,6]

第二轮：已排序区间 [11,12]，未排序 [13,5,6]

取出13，比12大 → 直接保留 → [11,12,13 | 5,6]

第三轮：取出5

依次与13,12,11比较 → 全部后移 → 插入头部 → [5,11,12,13 | 6]

第四轮：取出6

与13,12,11比较后插入到5后 → [5,6,11,12,13]

总结：先找到最小，然后再和已排序比较,小就往前往前往前插，大就往后插
 */
// 标准插入排序实现（原地排序，时间复杂度 O(n²)）
void SortClass::InsertSort(vector<int>& arr, int size)
{
    for (int i = 1; i < arr.size(); i++) {
        int key = arr[i];  //记录当前指向的数据 作为待插入数据
        int j = i - 1;  //永远指向i的前一个，初始化的时候，就是已排序区间
        // 将 key 插入到已排序部分的正确位置
        //把已插入的区间移动
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];  //把后一个数据也就是待插入的数据顶掉，然后回退，如果还小就顶掉，此时第一次顶掉的数被后面的数给顶掉了，
            //为什么可以顶掉因为i数据被记录了且因为是待插入所以可以看成空位
            //比如2,3,1,6 此时待插入是i a[j] 是3
            //2,3,3,6 a[j+1] = a[j] 前一个数占据了空位，然后指针后移
            //2,2,3,6
            //最后修正：1,2,3,6
            //直接在原始数组操作，减少额外的内存开辟，另外时间复杂度是平均为O(n^2)
            j--;
        }
        arr[j + 1] = key;  //最后修正数据
    }
    for(auto Rit : arr)
    {
        cout<<Rit<<" ";
    }
    cout<<'\n';
}


/*希尔排序：
* 核心思路分步拆解
定义间隔序列（Gap）
确定一个递减的间隔序列（如初始间隔为 n/2，之后每次折半），用于将数组划分为多个子序列。

分组插入排序
对每个间隔划分出的子序列独立进行插入排序，使数组逐渐变得“基本有序”。

缩小间隔重复操作
逐步缩小间隔直至为1（此时等同于标准的插入排序），最终完成整体排序。


手动模拟示例
以数组 [9, 8, 3, 7, 5, 6, 4, 1] 为例，初始间隔 gap=4：

第一轮（gap=4）：
划分为4个子序列（间隔4的元素为一组）：

[9,5] → 排序后 [5,9]

[8,6] → 排序后 [6,8]

[3,4] → 排序后 [3,4]

[7,1] → 排序后 [1,7]
→ 数组变为 [5,6,3,1,9,8,4,7]

第二轮（gap=2）：
划分为2个子序列：

[5,3,9,4] → 插入排序 → [3,4,5,9]

[6,1,8,7] → 插入排序 → [1,6,7,8]
→ 数组变为 [3,1,4,6,5,7,9,8]

第三轮（gap=1）：
等同于标准插入排序，最终得到 [1,3,4,5,6,7,8,9]
 */
void SortClass::ShellSort(vector<int>& arr, int size)
{
    // 初始间隔为n/2，逐步折半直至gap=1
    for (int gap = size/2; gap > 0; gap /= 2) {
        // 对每个子序列进行插入排序
        for (int i = gap; i < size; i++) {
            int temp = arr[i];          // 当前待插入元素
            int j;
            // 在子序列中逆向扫描并移动元素
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];  // 大元素后移
            }
            arr[j] = temp;              // 插入正确位置
        }
    }
}

/*特性分析
特性	说明
时间复杂度	取决于间隔序列，最佳可达到 O(n log²n)，平均优于插入排序
空间复杂度	O(1)（原地排序）
稳定性	不稳定（分组可能导致相等元素跨组交换）
适用场景	中等规模数据、需要避免高递归开销的场景*/





/*归并排序
 *
* 核心思路分步拆解
分（Divide）
将数组不断二分，直到每个子数组只剩0或1个元素（天然有序）。

治（Conquer）
从最底层开始，将两个有序子数组合并成一个更大的有序数组，逐层向上合并。

合并（Merge）
合并过程通过双指针遍历两个子数组，按序选取较小元素填入临时空间，最终回写原数组。
 */

//时间复杂度 O(nlogn)

// 合并两个有序数组 [left..mid] 和 [mid+1..right]
void Arraymerge(vector<int>& arr, int left, int mid, int right) {
    // 计算左右子数组的长度
    int leftLen = mid - left + 1;
    int rightLen = right - mid;

    // 创建临时数组（动态内存申请）
    int* L = new int[leftLen];
    int* R = new int[rightLen];

    // 拷贝数据到临时数组
    for (int i = 0; i < leftLen; i++) L[i] = arr[left + i];
    for (int j = 0; j < rightLen; j++) R[j] = arr[mid + 1 + j];

    // 双指针合并
    int i = 0, j = 0, k = left;  // i指向L，j指向R，k指向原数组
    while (i < leftLen && j < rightLen) {
        if (L[i] <= R[j]) arr[k++] = L[i++];  // 取较小的元素，然后替换
        else arr[k++] = R[j++];
    }

    // 处理剩余元素
    while (i < leftLen) arr[k++] = L[i++];
    while (j < rightLen) arr[k++] = R[j++];

    // 释放临时内存
    delete[] L;
    delete[] R;
}


//主函数递归入口
void SortClass::MergeSort(vector<int>& arr,int left,int right)
{
    if (left >= right) return;  // 递归终止条件：子数组只剩0或1个元素

    int mid = left + (right - left) / 2;  // 计算中点（防溢出写法） 对于左边，mid是尾部，对于右边，mid是头部
    MergeSort(arr, left, mid);      // 递归排序左半部分
    MergeSort(arr, mid + 1, right); // 递归排序右半部分
    Arraymerge(arr, left, mid, right);   // 合并两个有序部分
}

// 包装函数（调用更简单）使用函数重载，编译的时候确定，根据导入的参数数量
void mergeSort(vector<int>& arr, int n) {
    SortClass::MergeSort(arr, 0, n - 1);  //导入数组的索引位置，一个指向开头，一个指向结尾
}


// 双指针分区函数：返回基准的最终位置
//左边找大，右边找小
int partition(vector<int>& arr, int left, int right) {
    int pivot = arr[1 + (right - left) / 2]; // 选中间元素为基准（避免最坏情况）
    int i = left;    // 左指针（找大的）
    int j = right;   // 右指针（找小的）

    while (true) {
        while (arr[i] < pivot) {++i;} // 左指针右移，直到找到 >=pivot 的元素
        while (arr[j] > pivot) {--j;} // 右指针左移，直到找到 <=pivot 的元素

        if (i >= j) return j; // 指针相遇时，分区完成

        //指针没相遇但是左边找到了大右边找到了小则会交换
        swap(arr[i], arr[j]); // 交换逆序对
    }
}
//快速排序
/*快速排序是一种非常常用的排序方法，它在1962由C. A. R. Hoare（霍尔）提的一种二叉树结构的交换排序方法，
 *故因此它又被称为霍尔划分，它基于分治的思想，所以整体思路是递归进行的。
* 双指针法像两把梳子从两端向中间梳理：

左梳子专抓大元素

右梳子专抓小元素

抓到后互相交换，直到梳子相遇
 */
// 递归排序函数
void quickSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int p = partition(arr, left, right); // 获取分区点
        quickSort(arr, left, p);    // 处理左半部分，以分区点为右闭区间
        quickSort(arr, p + 1, right); // 处理右半部分，以分区点+1为左闭区间
    }
}


void SortClass::QuickSort(vector<int>& arr, int left, int right)
{
    //递归入口
    quickSort(arr, left, right);
}


int main(int argc, char* argv[])
{
    vector<int> BubbleSortArray = {8,1,3,4,7,6,9,10};
    SortClass::BubbleSort(BubbleSortArray,BubbleSortArray.size());
    
    vector<int> SelectSortArray = {9,6,7,1,3,5,4,2};
    SortClass::SelectSort(SelectSortArray,SelectSortArray.size());

    vector<int> InsertSortArray = {2,3,1,6};
    SortClass::InsertSort(InsertSortArray,InsertSortArray.size());

    vector<int> MergeSortArray = {2,3,1,6,10,14,11,8,4};
    mergeSort(MergeSortArray,MergeSortArray.size());

    vector<int> QuickSortArray = {2,1,0,8};
    SortClass::QuickSort(QuickSortArray,0,QuickSortArray.size() - 1);
    
    return 0;
}


