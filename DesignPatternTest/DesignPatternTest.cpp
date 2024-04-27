#include "pch.h"
#include "CppUnitTest.h"
#include "../DesignPattern/Singleton_Lazy.cpp"
#include "../DesignPattern/Singleton_Eager.cpp"
#include "../DesignPattern/Prototype.cpp"
#include "../DesignPattern/Factory.cpp"
#include "../DesignPattern/AbstractFactory.cpp"
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
                Singleton_Lazy* singleton = Singleton_Lazy::Instance("Yah!");
                return singleton->value();
                });

            std::future<std::string> r2 = std::async(std::launch::async, []() {
                // Emulating slow initialization.
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                Singleton_Lazy* singleton = Singleton_Lazy::Instance("NOooo");
                return singleton->value();
                });

            Assert::AreEqual(r1.get(), r2.get());
		}

        TEST_METHOD(Eager)
        {
            Singleton_Eager& eager1 = Singleton_Eager::Instance(0);
            Singleton_Eager& eager2 = Singleton_Eager::Instance(2);
            Assert::AreEqual(eager1.value(), eager2.value());
        }
	};

    TEST_CLASS(PrototypeTest)
    {
    public:
        float Client(PrototypeFactory& pFactory, 
            Type type, float value)
        {
            std::unique_ptr<Prototype> prototype =
                pFactory.CreatePrototype(type);
            return prototype->Method(value);
        }
        TEST_METHOD(Client)
        {
            PrototypeFactory* pFactory = new PrototypeFactory();
            auto prototype1 = Client(*pFactory, 
                Type::PROTOTYPE_1, 90);

            Assert::AreEqual(prototype1, 90.f);

            auto prototype2 = Client(*pFactory,
                Type::PROTOTYPE_2, 10);

            Assert::AreEqual(prototype2, 10.f);

            delete pFactory;
        }
    };

    TEST_CLASS(FactoryTest)
    {
    public:
        std::string Client(const Factory& factory)
        {
            return factory.DoOperation();
        }
        
        TEST_METHOD(Client)
        {
            Factory* factory1 = new ConcreteFactory1();
            Assert::AreEqual(Client(*factory1).compare("ConcreteProductF1"), 0);
            
            Factory* factory2 = new ConcreteFactory2();
            Assert::AreEqual(Client(*factory2).compare("ConcreteProductF2"), 0);

            delete factory1;
            delete factory2;
        }
    };

    TEST_CLASS(AbstractFactoryTest)
    {
    public:
        std::pair<std::string, std::string> Client(
                const AbstractFactory& aFactory)
        {
            const AbstractProductA* productA = aFactory.CreateProductA();
            const AbstractProductB* productB = aFactory.CreateProductB();

            std::pair<std::string, std::string> result;
            result.first = productB->GetCodeB();
            result.second = productB->GetCodeAFromB(*productA);
            
            delete productA;
            delete productB;

            return result;
        }

        TEST_METHOD(Client)
        {
            ConcreteAbstractFactory1* aFactory1 = new ConcreteAbstractFactory1();
            auto result1 = Client(*aFactory1);

            Assert::AreEqual(result1.first.compare("B1"), 0);
            Assert::AreEqual(result1.second.compare("B1+A1"), 0);

            delete aFactory1;

            ConcreteAbstractFactory2* aFactory2 = new ConcreteAbstractFactory2();
            auto result2 = Client(*aFactory2);

            Assert::AreEqual(result2.first.compare("B2"), 0);
            Assert::AreEqual(result2.second.compare("B2+A2"), 0);

            delete aFactory2;
        }
    };
}
