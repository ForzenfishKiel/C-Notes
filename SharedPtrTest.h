#pragma once
using namespace std;

class SharedPtrTest
{
public:
    SharedPtrTest()
    {
        cout << "测试的SharedPtrTest Constructor" <<'\n';
    }
    ~SharedPtrTest()
    {
        cout << "测试的SharedPtrTest Destructor" <<'\n';
    }

    int SharedNumber = 0;
};
