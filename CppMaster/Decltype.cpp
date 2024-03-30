// std::forward
// Forwards lvalues as either lvalues or as rvalues, depending on T.

// C++ 11
// auto Add(T&& t, U&& u) -> decltype(std::forward<T>(t) + std::forward<U>(u))
// C++ 14
// decltype(auto) Add(T&& t, U&& u)

#include <iostream>
template<typename T, typename U>
decltype(auto) Add_Decl(T&& t, U&& u)
{
	return std::forward<T>(t) + std::forward<U>(u);
}

class TestClass_Decl
{
	friend TestClass_Decl operator+(const TestClass_Decl& t1, const TestClass_Decl& t2)
	{
		return TestClass_Decl{ t1.val_ + t2.val_ };
	}

public:
	TestClass_Decl(int val) : val_{ val } {}
	int GetValue() const { return val_; }

private:
	int val_;
};

int main()
{
	std::cout << "1 + 2.8 = " << Add_Decl(1, 2.8) << std::endl;
	std::cout << "3.5 + 4.8 = " << Add_Decl(3.5, 4.8) << std::endl;

	TestClass_Decl t1{ 13 };
	TestClass_Decl t2{ 27 };
	std::cout << "t1 = " << t1.GetValue()
		<< ", t2 = " << t2.GetValue() << std::endl;
	std::cout << "t1 + t2 = " << Add_Decl(t1, t2).GetValue() << std::endl;

	system("pause");
	return 0;
}