#include <iostream>

template<class T, typename CRTPTag>
struct crtp
{
    T& underlying() { return static_cast<T&>(*this); }
    const T& underlying() const { return static_cast<const T&>(*this); }
};

template<class T>
struct Square : crtp<T, class SquareCRTP>
{
    void scale(double x)
    {
        auto val = this->underlying().get() * x;
        this->underlying().set(val);
    }
};

template<class T>
struct Scale : crtp<T, class ScaleCRTP>
{
    void square()
    {
        auto val = this->underlying().get() * this->underlying().get();
        this->underlying().set(val);
    }
};

class Sensitivity : public Square<Sensitivity>, public Scale<Sensitivity>
{
public:
    double get() const { return value; }
    void set(double v) { value = v; }
    
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
