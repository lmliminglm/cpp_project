/*
#include<iostream>
using namespace std;


// 函数的运算符重载  成员函数+运算符重载

class Person 
{
    public:

        // //成员函数重载函数运算符+号
        // Person operator+(Person &p)
        // {
        //     Person temp;
        //     temp.m_a = this->m_a + p.m_a;
        //     temp.m_b = this->m_a + p.m_b;
        //    return temp; 
        // }

        int m_a;
        int m_b;
};

//全局函数重载函数运算符+号
Person operator+(Person &p1, Person &p2)
{
    Person p3;
    p3.m_a = p1.m_a + p2.m_a;
    p3.m_b = p1.m_b + p2.m_b;
    return p3;
}


void test01()
{
    Person p1;
    p1.m_a = 40;
    p1.m_b = 40;

    Person p2;
    p2.m_a = 20;
    p2.m_b = 20;

    Person p3;
    p3 = p2 + p1;
    cout << "p3.m_a = "<< p3.m_a << endl;
    cout << "p3.m_b = "<< p3.m_b << endl;
}

void test02()
{
    Person p1;
    p1.m_a = 50;
    p1.m_b = 1;
    Person p2;
    p2.m_a = 10;
    p2.m_b = 2;


    Person p3;
    p3 = p1 + p2;
    cout << "p3.m_a = " << p3.m_a <<endl;
    cout << "p3.m_b = " << p3.m_b <<endl;
}

int main()
{
    
    // test01();
    test02();
    
    system("pause");

    return 0;
}
*/



    
