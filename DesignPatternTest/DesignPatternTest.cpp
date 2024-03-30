#include "pch.h"
#include "CppUnitTest.h"
#include "../DesignPattern/Singleton_Lazy.cpp"
#include "../DesignPattern/Singleton_Eager.cpp"
#include <future>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DesignPattern
{
	TEST_CLASS(SingletonTest)
	{
	public:
		TEST_METHOD(Lazy)
		{
            std::future<std::string> r1 = std::async(std::launch::async, []() {
                // Emulating slow initialization.
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                Singleton::Lazy* singleton = Singleton::Lazy::Instance("Yah!");
                return singleton->value();
                });

            std::future<std::string> r2 = std::async(std::launch::async, []() {
                // Emulating slow initialization.
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                Singleton::Lazy* singleton = Singleton::Lazy::Instance("NOooo");
                return singleton->value();
                });

            Assert::AreEqual(r1.get(), r2.get());
		}

        TEST_METHOD(Eager)
        {
            Singleton::Eager& eager1 = Singleton::Eager::Instance(0);
            Singleton::Eager& eager2 = Singleton::Eager::Instance(2);
            Assert::AreEqual(eager1.value(), eager2.value());
        }
	};
}
