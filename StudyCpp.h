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

//自定义键的类型
class Point
{
public:
    int x ,y;
    Point(int Inx,int Iny) : x(Inx),y(Iny) {}
    bool operator<(const Point &other) const
    {
        return (x < other.x) || (x == other.x && y < other.y);  //先比x，再比y
    }
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
    void VectorTest();
    void StreamTest();
    void ListTest();
    void SetTest();
    void MapTest();

    int num = 0;

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
    ~Complex()
    {
        cout<<"Complex are Destory !!!"<<'\n';
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
//深拷贝类
class DeepCopy
{
public:
    int* data = nullptr;
    DeepCopy(int val) {data = new int(val);}
    // 深拷贝构造函数
    DeepCopy(const DeepCopy& other) {
        data = new int(*other.data); // 分配新内存并复制值，传入的参数是赋值者，这里将赋值者的成员新开辟了一块然后赋值给了this的成员变量
    }
    DeepCopy& operator=(const DeepCopy& Other)
    {
        if(this != &Other)
        {
            delete data;
            data = new int(*Other.data);  //替换
        }
        return *this;  //返回自身的指针
    }

};
/*浅拷贝（Shallow Copy）
*ShallowClass obj2 = obj1; 本质上是：
*
ShallowClass obj2(obj1);
// 默认生成的拷贝构造函数（伪代码）
//ShallowClass(const ShallowClass& other) : data(other.data) {}

/*直接复制 other.data（指针地址）到新对象的 data。

导致 obj1.data 和 obj2.data 指向同一块内存。*/


/*

定义：直接复制对象的成员值（包括指针的地址），不创建新资源。

行为：

若对象包含指针，副本和原对象指向同一块内存。

修改一个对象的资源会影响另一个。

析构时可能导致同一内存被多次释放（双重释放错误）。

触发条件：

使用编译器生成的默认拷贝构造函数或赋值运算符。

适用场景：

对象没有动态分配的资源（如仅含基本类型成员）。*/
class ShallowClass {
public:
    int* data;
    ShallowClass(int val) { data = new int(val); }
    // 使用编译器生成的浅拷贝构造函数和赋值运算符
};