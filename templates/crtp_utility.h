template<typename T>
struct crtp
{
	T& underlying() { return static_cast<T&>(*this); }
	const T& underlying() const { return static_cast<T&>(*this); }
};
