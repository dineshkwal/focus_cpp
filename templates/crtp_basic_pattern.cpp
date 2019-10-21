#include <iostream>

template<class T>
struct crtp
{
    T& underlying() { return static_cast<T&>(*this); }
    const T& underlying() const { return static_cast<const T&>(*this); }
};

template<class DerivedT>
struct Base : public crtp<DerivedT>
{
    void foo()
    {
        std::cout << "CRTP: foo";
        this->underlying().bar();
    }
};

struct Derived : public Base<Derived>
{
    void bar() { std::cout << "bar\n"; }
};

int main()
{
    Derived d;
    d.foo();
    d.bar();
}
