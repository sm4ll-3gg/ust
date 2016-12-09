#include "ust.h"

#include <iostream>

class A
{
    int i;
public:
    A()
        :i(-1) {}

    A(int _i)
        :i(_i) {}

    int get()
    {
        return i;
    }
};

class B : public A
{
    float f;
public:
    B()
        :f(0.0) {}

    B(float _f)
        :f(_f) {}

    float get()
    {
        return f;
    }
};

int main()
{
    int i = 5;
    Ust ui(i);
    std::cout << "Засунули int: " << ui.cast<int>() << std::endl;

    A a(3);
    Ust ua(a);
    std::cout << "Засунули int, инкапсулированный в класс A" << ua.cast<A>().get() << std::endl;

    B b(2.5);
    Ust ub(b);
    std::cout << "Засунули float, инкапсулированный в класс B : public A " << ub.cast<B>().get() << std::endl;
    std::cout << "Явно вызвали A::get()" << ub.cast<B>().A::get() << std::endl;

    A* pa = new B(3.7);
    Ust upa(pa);
    std::cout << "Объектный полиморфизм " << upa.cast<A*>()->get() << std::endl;
    std::cout << "Кастанули A* к B* и вызвали гет "<< static_cast<B*> (upa.cast<A*>())->get() << std::endl;

    return 0;
}
