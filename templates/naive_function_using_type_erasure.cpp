#include <iostream>
#include <memory>
#include <cassert>

template<typename>
class naive_function;

template<typename R, typename... Args>
class naive_function<R(Args...)>
{
public:
    template<typename F>
    naive_function(F fn) : callable(std::make_shared<CallableModel<F>>(fn))
    {
    }
    
    R operator()(Args... args)
    {
        assert(callable);
        return callable->Invoke(args...);
    }

private:
    class CallableConcept
    {
    public:
        virtual ~CallableConcept() = default;
        virtual R Invoke(Args...) = 0;
    };
    
    template<typename F>
    class CallableModel : public CallableConcept
    {
    public:
        CallableModel(F fn) : fn(fn) 
        {
        }
        
        R Invoke(Args... args) override
        {
            return fn(args...);
        }
        
    private:
        F fn;
    };
    
    std::shared_ptr<CallableConcept> callable;
};


int sum(int a, int b) { return a + b; }

void print(int b) { std::cout << b << '\n'; }

int main()
{
    naive_function<int(int, int)> sumFn = sum;
    naive_function<int(int, int)> mulFn = [](int a, int b) { return a * b; };
    
    std::cout << sumFn(1, 2) << '\n';
    std::cout << mulFn(3, 4) << '\n';
    
    naive_function<void(int)> printFn = print;
    printFn(4);
}