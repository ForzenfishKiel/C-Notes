#pragma once
using namespace std;

//WeakPtr通常和SharedPtr一起出现
class B;
class A
{
public:
    A()
    {
        cout << "A Constructing" << '\n';
    }
    ~A()
    {
        cout << "A Destructing" << '\n';
    }
    weak_ptr<B> pb; //一个指向B的弱指针
};
class B
{
public:
    B()
    {
        cout << "B Constructing" << '\n';
    }
    ~B()
    {
        cout << "B Destructing" << '\n';
    }
    shared_ptr<A> pa;  //一个指向A的共享指针
};
