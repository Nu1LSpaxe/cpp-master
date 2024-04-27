#include <iostream>
#include <wrl/client.h>


namespace DesignPattern
{
	class Singleton_Eager
	{
	private:
		static Singleton_Eager instance;

	protected:
		Singleton_Eager(const int value) noexcept: value_(value) {};
		~Singleton_Eager() = default;

		int value_;

	public:
		Singleton_Eager(const Singleton_Eager&) = delete;
		Singleton_Eager& operator=(const Singleton_Eager&) = delete;

		static Singleton_Eager& Instance(const int value) noexcept
		{
			// Guaranteed to be destroyed.
			// Instantiated on first use.
			// Thread safe in C++11
			static Singleton_Eager instance{value};

			return instance;
		}

		int value() const { return value_; }
	};
}