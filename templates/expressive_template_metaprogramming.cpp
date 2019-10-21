#include <iostream>
#include <type_traits>

template<typename...>
using try_to_instantiate = void;

using disregard_this = void;
    
template<typename T>
using increment_expr = decltype(++std::declval<T&>());

template<typename U, typename V>
using assign_expr = decltype(std::declval<U&>() = std::declval<V&>());
    
namespace v1 { // Just more readable
    template<typename T, typename = void>
    struct is_incrementable : std::false_type {};
    
    template<typename T>
    struct is_incrementable<T, try_to_instantiate<increment_expr<T>>> : std::true_type {};
}

namespace v2 { // Works for single type in expression
    template<typename T, template<typename> class Expression, typename = void>
    struct is_detected : std::false_type {};
    
    template<typename T, template<typename> class Expression>
    struct is_detected<T, Expression, try_to_instantiate<Expression<T>>> : std::true_type {};
}

namespace v3 { // works for several types in expression
    template<template<typename...> class Expression, typename Attempt, typename... T>
    struct is_detected_impl : std::false_type {};
    
    template<template<typename...> class Expression, typename... T>
    struct is_detected_impl<Expression, try_to_instantiate<Expression<T...>>, T...> : std::true_type {};
    
    template<template<typename...> class Expr, typename... Ts>
    using is_detected = is_detected_impl<Expr, disregard_this, Ts...>;
    
    template<template<typename...> class Expr, typename... Ts>
    constexpr bool is_detected_v = is_detected<Expr, Ts...>::value;
}

int main()
{
    std::cout << v3::is_detected_v<increment_expr, int> << '\n';
    std::cout << v3::is_detected_v<assign_expr, int, double> << '\n';
}
