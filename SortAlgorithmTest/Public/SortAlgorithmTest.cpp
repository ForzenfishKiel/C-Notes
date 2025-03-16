#include <iostream>
#include <vector>
#include <array>
#include "D:/UE_Project/StudyCpp/SortAlgorithmTest/Private/SortAlgorithmTest.h"
using namespace std;

int main(int argc, char* argv[])
{
    vector<int> BubbleSortArray = {1,2,3,4,5,6,7,8};
    BubbleSortClass::BubbleSort(BubbleSortArray,BubbleSortArray.size());
    return 0;
}

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
void BubbleSortClass::BubbleSort(vector<int>& arr, int size)
{
    
}
