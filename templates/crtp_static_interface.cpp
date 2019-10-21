#include <iostream>

template<class T>
class Amount
{
public:
    int value() { return static_cast<T&>(*this).value(); }
};

class Constant42 : public Amount<Constant42>
{
public:
    int value() { return 42; }
};

class Variable : public Amount<Variable>
{
public:
    Variable(int val) : v{val} {}
    int value() { return v; }
private:
    int v;
};

template<typename T>
void print_value(Amount<T>& amount)
{
    std::cout << amount.value() << '\n';
}

int main()
{
    Constant42 c;
    print_value(c);
    
    Variable v(25);
    print_value(v);
}
