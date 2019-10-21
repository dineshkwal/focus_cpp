#include <iostream>

template<typename T>
struct Addable
{
    void add(int a) { static_cast<T&>(*this).v += a; }
};

template<typename T>
struct Scalable
{
    void scale(int a) { static_cast<T&>(*this).v *= a; }
};

template<typename T>
struct Printable
{
    void print() { std::cout << static_cast<T&>(*this).v << '\n'; }
};

template<typename T>
struct NumericalFeatures : Addable<T>, Scalable<T> // Compositing
{
};

template<template<typename> class... Features>
struct Test : Features<Test<Features...>>...
{
    int v = 0;
};

int main()
{
    Test<NumericalFeatures, Printable> t;
    t.add(5);
    t.print();
    
    t.scale(2);
    t.print();
}