#include <type_traits>
#include <tuple>
#include <iostream>
template<typename ...Args>
constexpr bool AllBool(Args ... args)
{
	return (... && args); // Unary left fold
}

template<typename ...Args>
int SumInt(Args&&... args)
{
	return (args + ... + 0); // Unary right fold
}

template<typename ...Args>
struct type_list {};

// std::integral_constant wraps a static constant of specified type:
//		static constexpr T value = value_;
using thisTypeList = type_list<
	std::integral_constant<int, 1024>,
	std::integral_constant<int, 2048>,
	std::integral_constant<int, 4096>>;

template<typename ...Args>
constexpr int SumInt_TypeList(type_list<Args...>)
{
	static_assert(sizeof...(Args) > 0, "Empty type list");
	return (0 + ... + Args::value);
}

// Validator
template<typename T>
constexpr bool is_even_v = (T::value % 2 == 0);

template<typename ...Args>
constexpr int CountEven(type_list<Args...>)
{
	return (0 + ... + is_even_v<Args>);
}

template<typename ...Args>
std::tuple<Args...> UnZip(type_list<Args...>)
{
	return std::tuple<Args...>{};
}

template<typename T, typename ...Args>
constexpr T Front(type_list<T, Args...>)
{
	return T{};
}

// Recursively get first element
template<typename T, typename ...Args>
constexpr auto Back(type_list<T, Args...>)
{
	if constexpr (sizeof ...(Args) == 0)
	{
		return T{};
	}
	else
	{
		return Back(type_list<Args...>{});
	}
}

// std::enable_if
template<typename T,
typename = typename std::enable_if<std::is_integral<T>::value>::type>
constexpr T Factorial_EnableIf(T n)
{
	return n <= 1 ? 1 : n * Factorial_EnableIf(n - 1);
}

// static_assert
template<typename T>
constexpr T Factorial(T n)
{
	static_assert(std::is_integral<T>::value, "T must be an integral type");
	return n <= 1 ? 1 : n * Factorial(n - 1);
}


int main()
{
	
	// return ((true && true) && false) && false
	bool bools = AllBool(true, true, false, false);

	// return 15
	SumInt(1, 2, 3, 4, 5);
	// return 0
	SumInt();

	auto [a, b, c] = UnZip(thisTypeList{});

	std::cout << "Get first element by Unzip(): " << a << std::endl;
	std::cout << "Get last emelent by Back(): " << Back(thisTypeList{}) << std::endl;

	std::cout << "Factorial(5): " << Factorial_EnableIf(5) << std::endl;

	system("pause");
	return 0;
}