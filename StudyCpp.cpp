#include <iostream>
#include <vector>
#include <sstream>
#include <list>
#include <array>
#include <set>
#include <map>
#include "StudyCpp.h"
#include <algorithm>
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
    StudyCppPtr->VectorTest();
    StudyCppPtr->ListTest();
    StudyCppPtr->SetTest();
    StudyCppPtr->MapTest();
    Singleton::GetInstance()->doSomething();
    Singleton::GetInstance()->ClearPtr();
    int a = 10;
    int* b = new int(10);
    //StudyCppPtr->StreamTest();  //字符串数据流测试

    DeepCopy NewCopy01(5);
    DeepCopy NewCopy02 = NewCopy01;

    // 使用时：浅拷贝
    ShallowClass obj1(5);
    ShallowClass obj2 = obj1; // 浅拷贝：obj2.data 和 obj1.data 指向同一地址
    
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

//Vector测试
void UStudyCpp::VectorTest()
{
    cout<<"------------------------------------------------------------------"<<'\n';
    vector<int> vec01(5,10); //五个元素，每个初始化为10
    vector<int> vec02 = {1,2,3}; //具体设计元素的成员
    //vec02.insert(vec02.begin() + 1, 1);  //从开头数第几个元素前插入元素 返回1,1,2,3
    vec02.erase(vec02.begin());  //从开头数第几个元素删除  返回2,3
    vector<int> vec03;
    vec03.reserve(10);  //预分配内存
    vec01.erase(remove(vec01.begin(), vec01.end(), 10), vec01.end());  //删除所有值为10的元素  打印不出任何东西

    for(auto it = vec02.begin(); it != vec02.end(); ++it)
    {
        cout<<"第"<<*it<<'\n';
    }
    
    //for (auto it = vec02.begin(); it != vec02.end(); ++it) {
    //if (*it % 2 == 0) {
    //vec02.erase(it); // 错误！erase 后 it 失效
    //}
    //}

    // 正确：利用 erase 返回新迭代器
    for (auto it = vec02.begin(); it != vec02.end();) {
        it = vec02.erase(it); // erase 返回下一个有效迭代器 ， 当前元素被删除以后，记录并指向删除之前的下一个元素为当前元素
    }
    cout<<vec02.size()<<'\n';

    vector<int> vec04 = {1,2,3,4};

    /*Vector的遍历方式：基于下标的传统循环*/
    for(size_t it = 0; it < vec04.size(); ++it)
    {
        cout<<vec04[it];
    }
    cout<<'\n';
    
    /*Vector的反向遍历*/
    for(size_t it = vec04.size(); it-- > 0;)
    {
        cout<<vec04[it];
    }
    cout<<'\n';
    
    /*基于范围，可修改的话，删掉const就行*/
    for(const auto& it : vec04)
    {
        cout<<it;
    }
    cout<<'\n';
    
    /*使用 STL算法访问，捕获this，lambda 表达式访问了类的成员变量或成员函数时，才需要捕获 this。*/
    for_each(vec04.begin(), vec04.end(), [](int num)
    {
        cout<<num;
    });

    cout<<"下角标访问："<<vec04[2]<<'\n';  //直接通过下角标访问，时间复杂度为O(1) 因为vector是一块连续的数组
    cout<<"------------------------------------------------------------------"<<'\n';
}

void UStudyCpp::StreamTest()
{
    string s; //定义一个stirng对象，从标准输入接受一个字符串 
    cout<<"请输入一行字符串:"<<'\n'; 
    getline(cin,s); 
    stringstream ss(s); //定义一个string流（使用s实例化）
    cout<<"处理后的字符串为:"<<'\n'; //将string流里的东西输出 
    for(string s1;ss>>s1;cout<<s1<<'\n'); 
}

/*List一、核心特性
底层数据结构

双向链表：每个节点（元素）包含一个值和两个指针，分别指向前一个节点和后一个节点。

内存分布：元素在内存中非连续存储，节点之间通过指针连接。

时间复杂度

插入/删除：在任意位置插入或删除元素的时间复杂度为 O(1)（只需调整指针）。

访问：随机访问的时间复杂度为 O(n)（必须从头或尾遍历）。

迭代器类型

双向迭代器：支持向前（++）和向后（--）移动，但不支持随机跳跃访问（如 + 5）。*/

//List双向链表测试
void UStudyCpp::ListTest()
{
    cout<<"------------------------------------------------------------------"<<'\n';
    //list<int>l1  初始构建
    //list<int>l1 = {1,2,3}  自定义成员构建
    //list<int>l2(l1.begin(),l1.end())  范围构建
    list<int> l1(5,10);  //五个元素，初始值为10
    l1.push_front(0); //头部插入
    l1.push_back(2); //尾部插入
    //l1.pop_front() 头部删除
    //l1.pop_back()  尾部删除

    auto it = l1.begin();  //创建迭代器指针位于链表的头节点
    advance(it,2);  //移动迭代器到第二个节点
    l1.insert(it,3);  //在迭代器位置之前插入一个3，此时it 指针指向的节点的前节点变成了3  时间复杂度为O(1)
    advance(it,-1);  //然后我们再往回移动，此时it 就指向了3
    it = l1.erase(it);  //删除迭代器指向的元素 , erase返回下一个节点，也就是让it指向下一个节点，例如刚刚是0,10,3,10，删除了3以后，就让it指向了原来的3后面的10  时间复杂度为O(1)
    //l1.remove(99) 删除所有值为99的元素
    std::list<int> l2 = {1, 2, 3};
    std::list<int> l3 = {4, 5, 6};

    l2.sort();//  快速排序
    l3.sort(); // 快速排序  时间复杂度为o(n log n)
    // 合并两个有序链表（合并后 l2 为空，l3 包含全部元素）
    //l2.merge(l3);         // 需保证 l2 和 l3 已排序 ， 合并后l3为空但不会被删除

    // 拼接（splice）：将另一个链表的部分或全部元素移动到当前链表
   // auto pos = l2.begin();  //让指针指向头节点 所有的操作都需要指针指向一块位置
    //l2.splice(pos, l3);   // 将 l2 所有元素插入到 pos 前，l2 变为空
    //auto pos = l2.end();//让指针指向尾节点 所有的操作都需要指针指向一块位置
    //l2.splice(pos, l3);   // 将 l2 所有元素插入到 pos 前，l2 变为空
    //auto pos = l2.begin();
    //advance(pos,2);  //让指针指向链表的第三个节点
    // l2.splice(pos,l3);  //将另一个链表插入到指针位置前

    //splice只需调整指针，整个过程时间复杂度为O(1)
    //Merge需要遍历两个元素，时间复杂度为O(m + n)

    l1.sort();  //快速排序（O(nlog n)）
    l1.unique();  //删除连续且重复的元素(需要先排序  时间复杂度为(O(n + nlogn)))
    l1.reverse();  //反转链表
    l1.resize(10) ;  //重置链表的大小  默认值为0

    //范围遍历 时间复杂度为O(n)
    for(auto i : l1)
    {
        cout<<i;
    }
    cout<<'\n';
    // 使用 cbegin() 和 cend()（C++11 起，只读迭代器）这是正向迭代器
    for (auto i = l1. cbegin(); i != l1.cend(); ++i) {
        cout << *i << " ";
    }
    cout<<'\n';
    //反向迭代器
    for (auto i = l1.crbegin(); i != l1.crend(); ++i) {
        cout << *i << " ";
    }
    cout<<'\n';


    //不捕获外部变量，直接输出迭代的数
    for_each(l1.begin(), l1.end(), [](auto n)
    {
       cout<<n<<" "; 
    });
    cout<<'\n';

    auto complexNum = make_unique<Complex>(6,7);
    //for_each迭代器  捕获外部变量
    for_each(l1.begin(), l1.end(), [&complexNum](auto i)  //注意unique不能被拷贝，所以捕获要捕获引用，且这样值传递也会快些，效率高
    {
        complexNum->UseA+=i;
        cout << complexNum->UseA << " ";
    });
    cout<<'\n';
}

/*C++ 标准模板库（STL）中的 map 和 set 是两种重要的关联容器，
 *基于键（Key）高效管理数据。它们通常用红黑树实现（有序版本）或哈希表实现（无序版本）。以下是详细解析：*/
void UStudyCpp::SetTest()
{
    cout<<"------------------------------------------------------"<<'\n';
    set<int> s;
    s.insert(10);  //插入元素
    //s.insert(10);  //插入同一个元素（键）被覆盖，集合非重复性
    s.emplace(20);  //直接构造元素（不用拷贝）

    //s.erase(10);  //删除元素

    //插入和删除的操作时间复杂度都是O(logn)
    auto it = s.begin();
    it = s.erase(it);  //删除指定元素并返还下一个有效元素

    auto Sfind = s.find(20); //返回迭代器，找不到返回s.end;

    for(auto iter : s)
    {
        cout<<iter<<" ";  //打印出Key
    }
    cout<<'\n';
}

/*特性
自动排序：元素按键升序排列（默认使用 < 比较，可自定义）。

不可修改键：元素的值（键）不可变，修改需删除后重新插入。

支持范围查询：利用 lower_bound() 和 upper_bound() 进行区间操作。
用途：去重、存在性检查，只用于查找*/

/*Map详解：
* 2. 特性
键值关联：每个键唯一对应一个值，支持通过键快速查找值。

自动扩容：插入新键时自动分配内存。

下标操作风险：m[key] 若键不存在会插入默认值，可能不符合预期。
 */
void UStudyCpp::MapTest()
{
    cout<<"------------------------------------------------------------------"<<'\n';
    map<string,int> m;
    m.insert(make_pair("Alice",1)); //插入或忽略已存在键
    m["Bob"]=2; //插入或覆盖已存在键

    m.erase("Alice");  //删除键的元素

    //int val = m.find("Alice")->second;  //查找对应的值

    //插入和删除的时间复杂度都是O(log n)

    //遍历方式
    for(const auto& it : m)
    {
        cout<<it.first<<" "<<it.second<<" ";
    }
    cout<<'\n';

    map<Point,string> PointNames;
    PointNames[{2,5}] = "Anny";
    PointNames[{6,10}] = "Vedal";
    for(const auto& PointIt : PointNames)
    {
        cout<<PointIt.first.x<<" "<<PointIt.second<<" ";
    }
    cout<<'\n';
}

/* `map`内部通常使用平衡二叉树（比如红黑树）来存储键值对，
 * 每次插入或查找都需要从根节点开始比较，决定向左还是向右子树移动，这时候就会频繁调用比较运算符。 */

