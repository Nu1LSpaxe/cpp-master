#include <iostream>
#include <wrl/client.h>


namespace DesignPattern
{
    namespace Singleton
    {
		class Eager
		{
		private:
			static Eager instance;

		protected:
			Eager(const int value) noexcept: value_(value) {};
			~Eager() = default;

			int value_;

		public:
			Eager(const Eager&) = delete;
			Eager& operator=(const Eager&) = delete;

			static Eager& Instance(const int value) noexcept
			{
				// Guaranteed to be destroyed.
				// Instantiated on first use.
				// Thread safe in C++11
				static Eager instance{value};

				return instance;
			}

			int value() const { return value_; }
		};
	}
}