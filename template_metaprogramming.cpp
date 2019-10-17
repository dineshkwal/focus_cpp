#include <iostream>
#include <type_traits>

template<typename T, typename = void>
struct is_incrementable : std::false_type {};

template<typename T>
struct is_incrementable<T, std::void_t<decltype(++std::declval<T&>())>> : std::true_type {};

int main()
{
    std::cout << is_incrementable<int>::value << '\n';
}
