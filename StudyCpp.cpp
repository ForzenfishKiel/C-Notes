#include <iostream>
#include "StudyCpp.h"
#include <vector>
using namespace std;
/*在C++中，std是一个命名空间（namespace），它包含了C++标准库的所有功能。
 *C++标准库提供了许多有用的组件，包括输入输出、字符串处理、容器（如向量、列表、集合等）、算法（如排序、查找等）、以及其他辅助功能。*/

extern int a = 0;  //声明a是一个全局变量，但不会分配内存
//使用自定义的命名空间
namespace MyNameSpace
{
    int value = 42;
}

int main(int argc, char* argv[])
{
    unique_ptr<UStudyCpp> StudyCppPtr = make_unique<UStudyCpp>();  //创建一个唯一指针指向唯一的头文件类，显式分配内存
    StudyCppPtr->UniquePtrTestFunc();
    StudyCppPtr->SharedPtrTestFunc();
    StudyCppPtr->WeakPtrTestFunc();
    StudyCppPtr->TestClassObject();
    StudyCppPtr->OperatorTest();
    StudyCppPtr->PointerArrayTest();
    StudyCppPtr->MergeStringTest();
    Singleton::GetInstance()->doSomething();
    Singleton::GetInstance()->ClearPtr();
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

void UStudyCpp::TestClassObject()
{
    cout<<MyNameSpace::value<<'\n'; //输出命名空间的语句  这是作用域解析的一种，作用域是为了防止访问名称冲突，提高代码可读性
    Outer::Inner InnerObject;  //声明对象实例，内存分配在栈区，在编译时分配，创建类中定义的嵌套类，用作用域阐述
    InnerObject.display();
    
    TestClass TestClass01;
    TestClass01.TestNum = 4;
    cout << TestClass01.TestNum << '\n';

    TestClass TestClass02;
    TestClass02.TestNum = 5;
    cout << TestClass02.TestNum << '\n';
}

//基础运算符重载
void UStudyCpp::OperatorTest()
{
    Complex TestA(3,5);
    Complex TestB(5,3);
    cout<<"重载运算符输出结果是："<<TestA + TestB<<'\n';
    if(TestA == TestB)
    {
        cout<<"比较运算符输出结果是：True"<<'\n';
    }
    else
    {
        cout<<"比较运算符输出结果是：False"<<'\n';
    }

    OutAndIn OI(5);
    cout<<"输出流输出的结果为："<<OI<<'\n';
}

//指针数组 vs 数组指针
void UStudyCpp::PointerArrayTest()
{
    int a = 5;
    int (*Ptr)[3];
    int data[3] = {1,2,3};
    Ptr = &data;
    cout<<*Ptr[1]<<'\n'; //数组指针，指向一块数组地址的指针

    int* NewPtr = &a;
    vector<int*> NewVec;
    NewVec.push_back(NewPtr);
    for(auto it = NewVec.begin(); it < NewVec.end(); ++it)
    {
        cout<<*(*it)<<'\n';  //指针指向地址，然后又解引用
    }  //指针数组，包含指针的数组

    //指针算数运算，遍历，使用Vector容器
    vector<int> vec{1, 2, 3};
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        cout << *it << "\n"; // 输出 1 2 3
    }
}

//字符串测试
void UStudyCpp::MergeStringTest()
{
    string s1 = "Hello";
    string s2 = "World";
    string s3 = s1 + s2;
    cout<<s3<<'\n';
    size_t pos =  s1.find("Hel");
    cout<<"找到的字符串的位置"<<pos<<'\n';  //查找对应字符串的起始位置

    string path = "/home/user";
    size_t pos2  = path.find_last_of('/');  //截取第一个/后面的字符
    if(pos2 != string::npos)
    {
        string filename = path.substr(pos + 1);
        cout<<"提取出的文档 ： "<<filename<<'\n';
    }

    string message = "I like apples";
    message.replace(7,6,"oranges");  //从7号开始替换六个字符
    cout<<"替换的字符为："<<message<<'\n';

    std::string data;
    data.reserve(1000); // 预分配足够内存，避免多次扩容
    for (int i = 0; i < 1000; ++i) {
        data += "x"; // 追加字符时不会触发扩容
    }
}

