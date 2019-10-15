#include <iostream>
 
template<class DerivedT>
class Base
{
public:
    void foo()
    {
        auto& d = static_cast<DerivedT&>(*this);
        std::cout << "CRTP: foo";
        d.bar();
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
