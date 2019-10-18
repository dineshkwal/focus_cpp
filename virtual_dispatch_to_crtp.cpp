#include <iostream>

namespace v1 {
    struct A
    {
        virtual ~A() = default;
        
        void bigAndSlow() const
        {
            helperfunction1(); 
            helperfunction2(); 
        }
        
        virtual void helperfunction1() const = 0;
        virtual void helperfunction2() const = 0;
    };
    
    struct B : public A
    {
        void helperfunction1() const override { std::cout << "B: helper1\n"; }
    };
    
    struct C : public B
    {
        void helperfunction2() const override  { std::cout << "C: helper2\n"; }
    };
}

namespace v2 {
    template<typename T>
    struct A
    {
        void bigAndSlow() const
        {
            static_cast<const T&>(*this).helperfunction1();
            static_cast<const T&>(*this).helperfunction2();
        }
    };
    
    template<typename T>
    struct B : public A<T>
    {
        void helperfunction1() const { std::cout << "B: helper1\n"; }
    };
    
    struct C : public B<C>
    {
        void helperfunction2() const { std::cout << "C: helper2\n"; }
    };
}

int main()
{
    v1::C c1;
    c1.bigAndSlow();
    
    v2::C c2;
    c2.bigAndSlow();
}