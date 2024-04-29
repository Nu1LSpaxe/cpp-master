#include "pch.h"
#include "CppUnitTest.h"
#include "../DesignPattern/Singleton_Lazy.cpp"
#include "../DesignPattern/Singleton_Eager.cpp"
#include "../DesignPattern/Prototype.cpp"
#include "../DesignPattern/Factory.cpp"
#include "../DesignPattern/AbstractFactory.cpp"
#include "../DesignPattern/Builder.cpp"
#include "../DesignPattern/Adapter.cpp"
#include "../DesignPattern/Bridge.cpp"
#include "Helper.h"
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
	private:
		float Client(PrototypeFactory& pFactory, Type type, float value)
		{
			std::unique_ptr<Prototype> prototype = pFactory.CreatePrototype(type);
			return prototype->SetField(value);
		}
	public:
		TEST_METHOD(PrototypeValue)
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
	private:
		std::string Client(const Factory& factory)
		{
			return factory.DoOperation();
		}
	public:
		TEST_METHOD(Factory1)
		{
			auto factory1 = std::make_unique<ConcreteFactory1>();

			Assert::AreEqual(Client(*factory1).compare("ConcreteProductF1"), 0);
		}
		TEST_METHOD(Factory2)
		{
			auto factory2 = std::make_unique<ConcreteFactory2>();

			Assert::AreEqual(Client(*factory2).compare("ConcreteProductF2"), 0);
		}
	};

	TEST_CLASS(AbstractFactoryTest)
	{
	private:
		std::pair<std::string, std::string> Client(const AbstractFactory& aFactory)
		{
			auto productA = aFactory.CreateProductA();
			auto productB = aFactory.CreateProductB();

			std::pair<std::string, std::string> result;
			result.first = productB->GetCodeB();
			result.second = productB->GetCodeAFromB(*productA);

			return result;
		}
	public:
		TEST_METHOD(AbstractFactory1)
		{
			std::unique_ptr<ConcreteAbstractFactory1> aFactory1 = std::make_unique<ConcreteAbstractFactory1>();
			auto result1 = Client(*aFactory1);

			Assert::AreEqual(result1.first.compare("B1"), 0);
			Assert::AreEqual(result1.second.compare("B1+A1"), 0);
		}
		TEST_METHOD(AbstractFactory2)
		{
			std::unique_ptr<ConcreteAbstractFactory2> aFactory2 = std::make_unique<ConcreteAbstractFactory2>();
			auto result2 = Client(*aFactory2);

			Assert::AreEqual(result2.first.compare("B2"), 0);
			Assert::AreEqual(result2.second.compare("B2+A2"), 0);
		}
	};

	TEST_CLASS(BuilderTest)
	{
	public:
		TEST_METHOD(BuildProduct)
		{
			Director director = Director();
			ConcreteBuilder1* builder1 = new ConcreteBuilder1();
			director.SetBuilder(builder1);

			Logger::WriteMessage("Get Minimal Viable Product: ");
			{
				director.BuildMinimalViableProduct();
				auto result = builder1->GetProduct()->ListParts();
				Logger::WriteMessage(result.data());

				Assert::AreEqual(result.compare("PartA1"), 0);
			}
			Logger::WriteMessage("\n");

			Logger::WriteMessage("Get Full Featured Products: ");
			{
				director.BuildFullFeaturedProduct();
				auto result = builder1->GetProduct()->ListParts();
				Logger::WriteMessage(result.data());

				Assert::AreEqual(result.compare("PartA1+PartB1+PartC1"), 0);
			}
			Logger::WriteMessage("\n");

			Logger::WriteMessage("Get Custom Products: ");
			{
				builder1->ProducePartB();
				builder1->ProducePartA();
				auto result = builder1->GetProduct()->ListParts();
				Logger::WriteMessage(result.data());

				Assert::AreEqual(result.compare("PartB1+PartA1"), 0);
			}
			Logger::WriteMessage("\n");
		}
	};

	TEST_CLASS(AdapterTest)
	{
	private:
		std::string Client(const Target* target)
		{
			return target->Request();
		}

	public:
		TEST_METHOD(TargetToAdaptee)
		{
			auto target = new Target();
			auto adaptee = new Adaptee();
			auto adapter = new Adapter(adaptee);

			Assert::AreEqual(Client(adapter).compare("Adaptee"), 0);
		}
	};

	TEST_CLASS(BridgeTest)
	{
	private:
		std::string Client(const BridgeAbstr& abstr)
		{
			return abstr.Operation();
		}

	public:
		TEST_METHOD(BaseTest)
		{
			auto implA = std::make_unique<ConcreteBridgeA>();
			BridgeAbstr abstr(std::move(implA));

			Assert::AreEqual(Client(abstr).compare("BridgeAbstr+ConcreteA"), 0);

			auto implB = std::make_unique<ConcreteBridgeB>();
			ExtendedAbstr extendedAbstr(std::move(implB));

			Assert::AreEqual(Client(extendedAbstr)
				.compare("ExtendedAbstr+ConcreteB"), 0);
		}
	};
}
