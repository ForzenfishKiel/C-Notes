#pragma once
#include "UniquePtrTest.h"
#include "SharedPtrTest.h"
#include "WeakPtrTest.h"
class UStudyCpp
{
public:
    UStudyCpp() : TestUniquePtr(make_unique<UniquePtrTest>()) , TestSharedPtr(make_shared<SharedPtrTest>())  {}
    ~UStudyCpp()
    {
        cout<<"This Ptr Was Delete"<<'\n';
    }
    void UniquePtrTestFunc();
    void SharedPtrTestFunc();
    void WeakPtrTestFunc();

    unique_ptr<UniquePtrTest> TestUniquePtr;
    shared_ptr<SharedPtrTest> TestSharedPtr;
};
class Outer
{
public:
    class Inner
    {
    public:
        void display() {cout<<"My Display Space Target"<<'\n';}    
    };
};
class TestClass
{
public:
    int TestNum = 0;
};