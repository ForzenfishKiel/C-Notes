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
/*��C++�У�std��һ�������ռ䣨namespace������������C++��׼������й��ܡ�
 *C++��׼���ṩ��������õ��������������������ַ����������������������б����ϵȣ����㷨�������򡢲��ҵȣ����Լ������������ܡ�*/

extern int a = 0;  //����a��һ��ȫ�ֱ���������������ڴ�
//ʹ���Զ���������ռ�
namespace MyNameSpace
{
    int value = 42;
}

int main(int argc, char* argv[])
{
    unique_ptr<UStudyCpp> StudyCppPtr = make_unique<UStudyCpp>();  //����һ��Ψһָ��ָ��Ψһ��ͷ�ļ��࣬��ʽ�����ڴ�
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
    //StudyCppPtr->StreamTest();  //�ַ�������������

    DeepCopy NewCopy01(5);
    DeepCopy NewCopy02 = NewCopy01;

    // ʹ��ʱ��ǳ����
    ShallowClass obj1(5);
    ShallowClass obj2 = obj1; // ǳ������obj2.data �� obj1.data ָ��ͬһ��ַ
    
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
    cout<<"һ��ʼ�����ü���"<< TestSharedPtr.use_count() <<'\n';
    
    shared_ptr<SharedPtrTest> Ptr02 = TestSharedPtr;  //��������
    cout<<"������ü��� �� "<<TestSharedPtr.use_count()<<'\n';  //��ӡ���ü���

    TestSharedPtr->SharedNumber = 2;
    cout <<"SharedPtr's Number is : "<< TestSharedPtr->SharedNumber << '\n';
    Ptr02->SharedNumber = 3;
    cout << "Ptr02's Number is :"<<Ptr02->SharedNumber << '\n';
}

void UStudyCpp::WeakPtrTestFunc()
{
    shared_ptr<B> PtrB = make_shared<B>();
    cout<<"PtrB�����ü����� : "<<PtrB.use_count()<<'\n';
    shared_ptr<A> PtrA = make_shared<A>();
    cout<<"PtrA�����ü����� : "<<PtrA.use_count()<<'\n';

    PtrB->pa = PtrA;  //��PtrA��PtrB�е�pa����A��
    cout<<"��ʱPtrBҲ���ǹ���B������ü����� : "<<PtrB.use_count()<<'\n'; //����
    cout<<"��ʱPtrAҲ���ǹ���A������ü����� ��"<<PtrA.use_count()<<'\n';  //���2
    PtrA->pb = PtrB;
    cout<<"------------------------------------------------------ : "<<'\n';
    cout<<"��ʱPtrBҲ���ǹ���B������ü����� : "<<PtrB.use_count()<<'\n'; //����
    cout<<"��ʱPtrAҲ���ǹ���A������ü����� ��"<<PtrA.use_count()<<'\n';  //���2

   // ����ʱ��PtrB �� PtrA �����ü������� 1 �� ��Ϊ 1�������޷��ͷţ� ʹ����ָ�룬���ڲ��ĳ�Ա�Ͳ����ڹ����ʱ���������ü�����ȷ�������౻��������
}

void UStudyCpp::TestClassObject()
{
    cout<<MyNameSpace::value<<'\n'; //��������ռ�����  ���������������һ�֣���������Ϊ�˷�ֹ�������Ƴ�ͻ����ߴ���ɶ���
    Outer::Inner InnerObject;  //��������ʵ�����ڴ������ջ�����ڱ���ʱ���䣬�������ж����Ƕ���࣬�����������
    InnerObject.display();
    
    TestClass TestClass01;
    TestClass01.TestNum = 4;
    cout << TestClass01.TestNum << '\n';

    TestClass TestClass02;
    TestClass02.TestNum = 5;
    cout << TestClass02.TestNum << '\n';
}

//�������������
void UStudyCpp::OperatorTest()
{
    Complex TestA(3,5);
    Complex TestB(5,3);
    cout<<"����������������ǣ�"<<TestA + TestB<<'\n';
    if(TestA == TestB)
    {
        cout<<"�Ƚ�������������ǣ�True"<<'\n';
    }
    else
    {
        cout<<"�Ƚ�������������ǣ�False"<<'\n';
    }

    OutAndIn OI(5);
    cout<<"���������Ľ��Ϊ��"<<OI<<'\n';
}

//ָ������ vs ����ָ��
void UStudyCpp::PointerArrayTest()
{
    int a = 5;
    int (*Ptr)[3];
    int data[3] = {1,2,3};
    Ptr = &data;
    cout<<*Ptr[1]<<'\n'; //����ָ�룬ָ��һ�������ַ��ָ��

    int* NewPtr = &a;
    vector<int*> NewVec;
    NewVec.push_back(NewPtr);
    for(auto it = NewVec.begin(); it < NewVec.end(); ++it)
    {
        cout<<*(*it)<<'\n';  //ָ��ָ���ַ��Ȼ���ֽ�����
    }  //ָ�����飬����ָ�������

    //ָ���������㣬������ʹ��Vector����
    vector<int> vec{1, 2, 3};
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        cout << *it << "\n"; // ��� 1 2 3
    }
}

//�ַ�������
void UStudyCpp::MergeStringTest()
{
    string s1 = "Hello";
    string s2 = "World";
    string s3 = s1 + s2;
    cout<<s3<<'\n';
    size_t pos =  s1.find("Hel");
    cout<<"�ҵ����ַ�����λ��"<<pos<<'\n';  //���Ҷ�Ӧ�ַ�������ʼλ��

    string path = "/home/user";
    size_t pos2  = path.find_last_of('/');  //��ȡ��һ��/������ַ�
    if(pos2 != string::npos)
    {
        string filename = path.substr(pos + 1);
        cout<<"��ȡ�����ĵ� �� "<<filename<<'\n';
    }

    string message = "I like apples";
    message.replace(7,6,"oranges");  //��7�ſ�ʼ�滻�����ַ�
    cout<<"�滻���ַ�Ϊ��"<<message<<'\n';

    std::string data;
    data.reserve(1000); // Ԥ�����㹻�ڴ棬����������
    for (int i = 0; i < 1000; ++i) {
        data += "x"; // ׷���ַ�ʱ���ᴥ������
    }
}

//Vector����
void UStudyCpp::VectorTest()
{
    cout<<"------------------------------------------------------------------"<<'\n';
    vector<int> vec01(5,10); //���Ԫ�أ�ÿ����ʼ��Ϊ10
    vector<int> vec02 = {1,2,3}; //�������Ԫ�صĳ�Ա
    //vec02.insert(vec02.begin() + 1, 1);  //�ӿ�ͷ���ڼ���Ԫ��ǰ����Ԫ�� ����1,1,2,3
    vec02.erase(vec02.begin());  //�ӿ�ͷ���ڼ���Ԫ��ɾ��  ����2,3
    vector<int> vec03;
    vec03.reserve(10);  //Ԥ�����ڴ�
    vec01.erase(remove(vec01.begin(), vec01.end(), 10), vec01.end());  //ɾ������ֵΪ10��Ԫ��  ��ӡ�����κζ���

    for(auto it = vec02.begin(); it != vec02.end(); ++it)
    {
        cout<<"��"<<*it<<'\n';
    }
    
    //for (auto it = vec02.begin(); it != vec02.end(); ++it) {
    //if (*it % 2 == 0) {
    //vec02.erase(it); // ����erase �� it ʧЧ
    //}
    //}

    // ��ȷ������ erase �����µ�����
    for (auto it = vec02.begin(); it != vec02.end();) {
        it = vec02.erase(it); // erase ������һ����Ч������ �� ��ǰԪ�ر�ɾ���Ժ󣬼�¼��ָ��ɾ��֮ǰ����һ��Ԫ��Ϊ��ǰԪ��
    }
    cout<<vec02.size()<<'\n';

    vector<int> vec04 = {1,2,3,4};

    /*Vector�ı�����ʽ�������±�Ĵ�ͳѭ��*/
    for(size_t it = 0; it < vec04.size(); ++it)
    {
        cout<<vec04[it];
    }
    cout<<'\n';
    
    /*Vector�ķ������*/
    for(size_t it = vec04.size(); it-- > 0;)
    {
        cout<<vec04[it];
    }
    cout<<'\n';
    
    /*���ڷ�Χ�����޸ĵĻ���ɾ��const����*/
    for(const auto& it : vec04)
    {
        cout<<it;
    }
    cout<<'\n';
    
    /*ʹ�� STL�㷨���ʣ�����this��lambda ���ʽ��������ĳ�Ա�������Ա����ʱ������Ҫ���� this��*/
    for_each(vec04.begin(), vec04.end(), [](int num)
    {
        cout<<num;
    });

    cout<<"�½Ǳ���ʣ�"<<vec04[2]<<'\n';  //ֱ��ͨ���½Ǳ���ʣ�ʱ�临�Ӷ�ΪO(1) ��Ϊvector��һ������������
    cout<<"------------------------------------------------------------------"<<'\n';
}

void UStudyCpp::StreamTest()
{
    string s; //����һ��stirng���󣬴ӱ�׼�������һ���ַ��� 
    cout<<"������һ���ַ���:"<<'\n'; 
    getline(cin,s); 
    stringstream ss(s); //����һ��string����ʹ��sʵ������
    cout<<"�������ַ���Ϊ:"<<'\n'; //��string����Ķ������ 
    for(string s1;ss>>s1;cout<<s1<<'\n'); 
}

/*Listһ����������
�ײ����ݽṹ

˫������ÿ���ڵ㣨Ԫ�أ�����һ��ֵ������ָ�룬�ֱ�ָ��ǰһ���ڵ�ͺ�һ���ڵ㡣

�ڴ�ֲ���Ԫ�����ڴ��з������洢���ڵ�֮��ͨ��ָ�����ӡ�

ʱ�临�Ӷ�

����/ɾ����������λ�ò����ɾ��Ԫ�ص�ʱ�临�Ӷ�Ϊ O(1)��ֻ�����ָ�룩��

���ʣ�������ʵ�ʱ�临�Ӷ�Ϊ O(n)�������ͷ��β��������

����������

˫���������֧����ǰ��++�������--���ƶ�������֧�������Ծ���ʣ��� + 5����*/

//List˫���������
void UStudyCpp::ListTest()
{
    cout<<"------------------------------------------------------------------"<<'\n';
    //list<int>l1  ��ʼ����
    //list<int>l1 = {1,2,3}  �Զ����Ա����
    //list<int>l2(l1.begin(),l1.end())  ��Χ����
    list<int> l1(5,10);  //���Ԫ�أ���ʼֵΪ10
    l1.push_front(0); //ͷ������
    l1.push_back(2); //β������
    //l1.pop_front() ͷ��ɾ��
    //l1.pop_back()  β��ɾ��

    auto it = l1.begin();  //����������ָ��λ�������ͷ�ڵ�
    advance(it,2);  //�ƶ����������ڶ����ڵ�
    l1.insert(it,3);  //�ڵ�����λ��֮ǰ����һ��3����ʱit ָ��ָ��Ľڵ��ǰ�ڵ�����3  ʱ�临�Ӷ�ΪO(1)
    advance(it,-1);  //Ȼ�������������ƶ�����ʱit ��ָ����3
    it = l1.erase(it);  //ɾ��������ָ���Ԫ�� , erase������һ���ڵ㣬Ҳ������itָ����һ���ڵ㣬����ո���0,10,3,10��ɾ����3�Ժ󣬾���itָ����ԭ����3�����10  ʱ�临�Ӷ�ΪO(1)
    //l1.remove(99) ɾ������ֵΪ99��Ԫ��
    std::list<int> l2 = {1, 2, 3};
    std::list<int> l3 = {4, 5, 6};

    l2.sort();//  ��������
    l3.sort(); // ��������  ʱ�临�Ӷ�Ϊo(n log n)
    // �ϲ��������������ϲ��� l2 Ϊ�գ�l3 ����ȫ��Ԫ�أ�
    //l2.merge(l3);         // �豣֤ l2 �� l3 ������ �� �ϲ���l3Ϊ�յ����ᱻɾ��

    // ƴ�ӣ�splice��������һ������Ĳ��ֻ�ȫ��Ԫ���ƶ�����ǰ����
   // auto pos = l2.begin();  //��ָ��ָ��ͷ�ڵ� ���еĲ�������Ҫָ��ָ��һ��λ��
    //l2.splice(pos, l3);   // �� l2 ����Ԫ�ز��뵽 pos ǰ��l2 ��Ϊ��
    //auto pos = l2.end();//��ָ��ָ��β�ڵ� ���еĲ�������Ҫָ��ָ��һ��λ��
    //l2.splice(pos, l3);   // �� l2 ����Ԫ�ز��뵽 pos ǰ��l2 ��Ϊ��
    //auto pos = l2.begin();
    //advance(pos,2);  //��ָ��ָ������ĵ������ڵ�
    // l2.splice(pos,l3);  //����һ��������뵽ָ��λ��ǰ

    //spliceֻ�����ָ�룬��������ʱ�临�Ӷ�ΪO(1)
    //Merge��Ҫ��������Ԫ�أ�ʱ�临�Ӷ�ΪO(m + n)

    l1.sort();  //��������O(nlog n)��
    l1.unique();  //ɾ���������ظ���Ԫ��(��Ҫ������  ʱ�临�Ӷ�Ϊ(O(n + nlogn)))
    l1.reverse();  //��ת����
    l1.resize(10) ;  //��������Ĵ�С  Ĭ��ֵΪ0

    //��Χ���� ʱ�临�Ӷ�ΪO(n)
    for(auto i : l1)
    {
        cout<<i;
    }
    cout<<'\n';
    // ʹ�� cbegin() �� cend()��C++11 ��ֻ�����������������������
    for (auto i = l1. cbegin(); i != l1.cend(); ++i) {
        cout << *i << " ";
    }
    cout<<'\n';
    //���������
    for (auto i = l1.crbegin(); i != l1.crend(); ++i) {
        cout << *i << " ";
    }
    cout<<'\n';


    //�������ⲿ������ֱ�������������
    for_each(l1.begin(), l1.end(), [](auto n)
    {
       cout<<n<<" "; 
    });
    cout<<'\n';

    auto complexNum = make_unique<Complex>(6,7);
    //for_each������  �����ⲿ����
    for_each(l1.begin(), l1.end(), [&complexNum](auto i)  //ע��unique���ܱ����������Բ���Ҫ�������ã�������ֵ����Ҳ���Щ��Ч�ʸ�
    {
        complexNum->UseA+=i;
        cout << complexNum->UseA << " ";
    });
    cout<<'\n';
}

/*C++ ��׼ģ��⣨STL���е� map �� set ��������Ҫ�Ĺ���������
 *���ڼ���Key����Ч�������ݡ�����ͨ���ú����ʵ�֣�����汾�����ϣ��ʵ�֣�����汾������������ϸ������*/
void UStudyCpp::SetTest()
{
    cout<<"------------------------------------------------------"<<'\n';
    set<int> s;
    s.insert(10);  //����Ԫ��
    //s.insert(10);  //����ͬһ��Ԫ�أ����������ǣ����Ϸ��ظ���
    s.emplace(20);  //ֱ�ӹ���Ԫ�أ����ÿ�����

    //s.erase(10);  //ɾ��Ԫ��

    //�����ɾ���Ĳ���ʱ�临�Ӷȶ���O(logn)
    auto it = s.begin();
    it = s.erase(it);  //ɾ��ָ��Ԫ�ز�������һ����ЧԪ��

    auto Sfind = s.find(20); //���ص��������Ҳ�������s.end;

    for(auto iter : s)
    {
        cout<<iter<<" ";  //��ӡ��Key
    }
    cout<<'\n';
}

/*����
�Զ�����Ԫ�ذ����������У�Ĭ��ʹ�� < �Ƚϣ����Զ��壩��

�����޸ļ���Ԫ�ص�ֵ���������ɱ䣬�޸���ɾ�������²��롣

֧�ַ�Χ��ѯ������ lower_bound() �� upper_bound() �������������
��;��ȥ�ء������Լ�飬ֻ���ڲ���*/

/*Map��⣺
* 2. ����
��ֵ������ÿ����Ψһ��Ӧһ��ֵ��֧��ͨ�������ٲ���ֵ��

�Զ����ݣ������¼�ʱ�Զ������ڴ档

�±�������գ�m[key] ���������ڻ����Ĭ��ֵ�����ܲ�����Ԥ�ڡ�
 */
void UStudyCpp::MapTest()
{
    cout<<"------------------------------------------------------------------"<<'\n';
    map<string,int> m;
    m.insert(make_pair("Alice",1)); //���������Ѵ��ڼ�
    m["Bob"]=2; //����򸲸��Ѵ��ڼ�

    m.erase("Alice");  //ɾ������Ԫ��

    //int val = m.find("Alice")->second;  //���Ҷ�Ӧ��ֵ

    //�����ɾ����ʱ�临�Ӷȶ���O(log n)

    //������ʽ
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

/* `map`�ڲ�ͨ��ʹ��ƽ����������������������洢��ֵ�ԣ�
 * ÿ�β������Ҷ���Ҫ�Ӹ��ڵ㿪ʼ�Ƚϣ��������������������ƶ�����ʱ��ͻ�Ƶ�����ñȽ�������� */

