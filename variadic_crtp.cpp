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

template<template<typename> class... Features>
struct Test : Features<Test<Features...>>...
{
    int v = 0;
};

int main()
{
    Test<Addable, Scalable> t;
    t.add(5);
    std::cout << t.v << '\n';
    
    t.scale(2);
    std::cout << t.v << '\n';
}