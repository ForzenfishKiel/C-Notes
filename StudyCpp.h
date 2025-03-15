#pragma once
#include "UniquePtrTest.h"
#include "SharedPtrTest.h"
#include "WeakPtrTest.h"
//强类型枚举
enum class Fruit
{
    None = 0,
    Apple = 1,
    Banana = 2,
    Cherry = 3
};
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
    void TestClassObject();
    void OperatorTest();
    void PointerArrayTest();
    void MergeStringTest();

    unique_ptr<UniquePtrTest> TestUniquePtr;
    shared_ptr<SharedPtrTest> TestSharedPtr;
    Fruit AnyFruit = Fruit::None;  //强类型枚举
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

class Complex
{

public:
    int UseA = 3;
    int UseB = 5;
    Complex(int A,int B) : UseA(A), UseB(B) {}
    //自定义运算符重载
    int operator+(const Complex& OtherTestClass)
    {
        return (UseA + OtherTestClass.UseB);
    }
};
inline bool operator==(const Complex& OtherTestClass , const Complex& OtherTestClass2)
{
    return OtherTestClass.UseA == OtherTestClass2.UseA && OtherTestClass.UseB == OtherTestClass2.UseB;
}
class OutAndIn
{
public:
    int value = 0;
    OutAndIn(int InValue) : value(InValue) {}

    friend ostream& operator<<(ostream& os , const OutAndIn& OtherClass)
    {
        return os << OtherClass.value;
    }
};

//创建单例模式，全局唯一单例，避免一个类被创建多个对象然后做不同的访问和修改
//应用：配置文件时创建全局唯一配置源，防止多个实例读取和修改不同的配置
class Singleton
{
public:
    static Singleton* GetInstance()
    {
        static Singleton* instance = new Singleton;  //显式创建
        return instance;  //获取全局唯一单例
    }
    void doSomething()
    {
        cout<<"I am something"<<'\n';
    }
    void ClearPtr()
    {
        delete this;
    }
    ~Singleton()
    {
        cout<<"I am the destructor"<<'\n';
    }
private:
    Singleton() {}
    Singleton(const Singleton&) = delete;  //禁用拷贝构造
    Singleton& operator=(const Singleton&) = delete;  //禁用赋值运算符
    //删除了以后就不能创建对象了，防止在访问静态函数的时候有多个成员访问这种情况
};