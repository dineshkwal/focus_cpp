#include <iostream>

template<class DerivedT>
class NumericFunctions
{
public:
    DerivedT& underlying() { return static_cast<DerivedT&>(*this); }
    
    void scale(double x)
    {
        auto val = underlying().get() * x;
        underlying().set(val);
    }
    
    void square()
    {
        auto val = underlying().get() * underlying().get();
        underlying().set(val);
    }
    
    void setToOpposite() { scale(-1); }
};

class Sensitivity : public NumericFunctions<Sensitivity>
{
public:
    double get() const { return value; }
    void set(double v) { value = v; }
    
    // These are common functionalities, which can be used with other classes as well
    // so creating a crtp classs which extends the functionality.
    // void scale(double x) { value *= x; }
    // void square(double x) { value = value * value; }
    // void setToOpposite() { scale(-1); }
    
private:
    double value {};
};

int main()
{
    Sensitivity s;
    s.set(5);
    s.square();
    std::cout << s.get();
}
