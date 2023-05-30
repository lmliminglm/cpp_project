#include <iostream>
using namespace std;


class Person
{
    public:

    int m_a;
    int m_b;
};
//左移运算符重载
ostream & operator<<(ostream &cout, Person &p)
{
    cout <<"p.m_a = " << p.m_a << " p.m_b = " <<  p.m_b << endl;
}

void test01()
{
    Person p1;
    p1.m_a = 11;
    p1.m_b = 12;

    Person p2;
    p2.m_a = 22;
    p2.m_b = 23;

    Person p3;
    p3.m_a = p1.m_a +p2.m_a;
    p3.m_b = p1.m_b +p2.m_b;

    cout << p3 << endl;

}


int main()
{
    test01();

    system("pause");
    return 0;
}