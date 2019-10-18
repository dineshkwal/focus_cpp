#include <iostream>
#include <string>

namespace mixin {
	struct Name
	{
		std::string firstName;
		std::string lastName;

		void print() { std::cout << firstName << lastName << '\n'; }
	};

	template<typename T>
	struct RepeatedPrint : public T
	{
		RepeatedPrint(const T& t) : T(t) {}

		void repeat(int n) {
			while (n--)
				this->print();
		}
	};
} 

namespace crtp {
    template<typename T>
	struct RepeatedPrint
	{
	    void repeat(int n) {
			while (n--)
			{
			    static_cast<T&>(*this).print();
			}
		}
	};
	
	struct Name : RepeatedPrint<Name>
	{
		std::string firstName;
		std::string lastName;

		void print() { std::cout << firstName << lastName << '\n'; }
	};
} 

int main()
{
	mixin::Name n;
	n.firstName = "mix";
	n.lastName = "in";

	mixin::RepeatedPrint repeatPrint(n);
	repeatPrint.repeat(5);
	
	crtp::Name p;
	p.firstName = "cr";
	p.lastName = "tp";
	p.repeat(5);
}