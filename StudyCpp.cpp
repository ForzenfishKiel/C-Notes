#include <iostream>
#include "StudyCpp.h"
using namespace std;
namespace MyNameSpace
{
    int value = 42;
}
int main(int argc, char* argv[])
{
    unique_ptr<UStudyCpp> StudyCppPtr = make_unique<UStudyCpp>();  //创建一个唯一指针指向唯一的头文件类
    StudyCppPtr->UniquePtrTestFunc();
    StudyCppPtr->SharedPtrTestFunc();
    StudyCppPtr->WeakPtrTestFunc();
    cout<<MyNameSpace::value<<'\n'; //输出命名空间的语句  这是作用域解析的一种，作用域是为了防止访问名称冲突，提高代码可读性
    Outer::Inner InnerObject;  //声明对象实例，内存分配在栈区，在编译时分配，创建类中定义的嵌套类，用作用域阐述
    InnerObject.display();

    TestClass TestClass01;
    TestClass01.TestNum = 4;
    cout << TestClass01.TestNum << '\n';

    TestClass TestClass02;
    TestClass02.TestNum = 5;
    cout << TestClass02.TestNum << '\n';

    
    return 0;
}

void UStudyCpp::UniquePtrTestFunc()
{
    if(!TestUniquePtr) return;
    unique_ptr<UniquePtrTest> Ptr02 =  std::move(TestUniquePtr);
}

void UStudyCpp::SharedPtrTestFunc()
{
    if(!TestSharedPtr) return;
    cout<<"一开始的引用计数"<< TestSharedPtr.use_count() <<'\n';
    
    shared_ptr<SharedPtrTest> Ptr02 = TestSharedPtr;  //共享引用
    cout<<"输出引用计数 ： "<<TestSharedPtr.use_count()<<'\n';  //打印引用计数

    TestSharedPtr->SharedNumber = 2;
    cout <<"SharedPtr's Number is : "<< TestSharedPtr->SharedNumber << '\n';
    Ptr02->SharedNumber = 3;
    cout << "Ptr02's Number is :"<<Ptr02->SharedNumber << '\n';
}

void UStudyCpp::WeakPtrTestFunc()
{
    shared_ptr<B> PtrB = make_shared<B>();
    cout<<"PtrB的引用计数是 : "<<PtrB.use_count()<<'\n';
    shared_ptr<A> PtrA = make_shared<A>();
    cout<<"PtrA的引用计数是 : "<<PtrA.use_count()<<'\n';

    PtrB->pa = PtrA;  //让PtrA和PtrB中的pa共享A类
    cout<<"此时PtrB也就是共享B类的引用计数是 : "<<PtrB.use_count()<<'\n'; //不变
    cout<<"此时PtrA也就是共享A类的引用计数是 ："<<PtrA.use_count()<<'\n';  //输出2
    PtrA->pb = PtrB;
    cout<<"------------------------------------------------------ : "<<'\n';
    cout<<"此时PtrB也就是共享B类的引用计数是 : "<<PtrB.use_count()<<'\n'; //不变
    cout<<"此时PtrA也就是共享A类的引用计数是 ："<<PtrA.use_count()<<'\n';  //输出2

   // 结束时，PtrB 和 PtrA 的引用计数各减 1 → 均为 1，对象无法释放！ 使用弱指针，类内部的成员就不会在共享的时候增加引用计数，确保两个类被正常析构
}
