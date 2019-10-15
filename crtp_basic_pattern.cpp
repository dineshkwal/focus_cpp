#include <iostream>
 
template<class T>
class CRTPHelper
{
public:
    T& underlying() { return static_cast<T&>(*this); }
    
    const T& underlying() const { return static_cast<const T&>(*this); }
};

template<class DerivedT>
class Base : public CRTPHelper<DerivedT>
{
public:
    void foo()
    {
        std::cout << "CRTP: foo";
        this->underlying().bar();
    }
};

class Derived : public Base<Derived>
{
public:
    void bar() { std::cout << "bar\n"; }
};
 
int main()
{
  Derived d;
  d.foo();
  d.bar();
}