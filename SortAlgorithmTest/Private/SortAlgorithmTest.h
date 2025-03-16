#pragma once
using namespace std;
//冒泡排序
class SortClass
{
public:
    static void BubbleSort(vector<int>& arr, int size);  //冒泡排序
    static void SelectSort(vector<int>& arr, int size);  //选择排序
    static void InsertSort(vector<int>& arr, int size); //插入排序
    static void ShellSort(vector<int>& arr, int size);  //希尔排序
    static void MergeSort(vector<int>& arr, int left,int right);
};