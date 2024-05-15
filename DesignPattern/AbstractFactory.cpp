/// Produce related objects without specifying concrete classes

#include <string>

namespace DesignPattern
{
	class AbstractProductA
	{
	public:
		virtual ~AbstractProductA() {};
		virtual std::string GetCodeA() const = 0;
	};

	class ConcreteProductA1 : public AbstractProductA
	{
	public:
		std::string GetCodeA() const override
		{
			return "A1";
		}
	};

	class ConcreteProductA2 : public AbstractProductA
	{
	public:
		std::string GetCodeA() const override
		{
			return "A2";
		}
	};

	class AbstractProductB
	{
	public:
		virtual ~AbstractProductB() {};
		virtual std::string GetCodeB() const = 0;

		// Also can collaborate with other product
		virtual std::string GetCodeAFromB(const AbstractProductA& collaborator)
			const = 0;
	};

	class ConcreteProductB1 : public AbstractProductB
	{
	public:
		std::string GetCodeB() const override
		{
			return "B1";
		}

		std::string GetCodeAFromB(const AbstractProductA& collaborator)
			const override
		{
			return "B1+" + collaborator.GetCodeA();
		}
	};

	class ConcreteProductB2 : public AbstractProductB
	{
	public:
		std::string GetCodeB() const override
		{
			return "B2";
		}

		std::string GetCodeAFromB(const AbstractProductA& collaborator)
			const override
		{
			return "B2+" + collaborator.GetCodeA();
		}
	};

	class AbstractFactory
	{
	public:
		virtual AbstractProductA* CreateProductA() const = 0;
		virtual AbstractProductB* CreateProductB() const = 0;
	};

	class ConcreteAbstractFactory1 : public AbstractFactory
	{
	public:
		AbstractProductA* CreateProductA() const override
		{
			return new ConcreteProductA1();
		}
		AbstractProductB* CreateProductB() const override
		{
			return new ConcreteProductB1();
		}
	};

	class ConcreteAbstractFactory2 : public AbstractFactory
	{
	public:
		AbstractProductA* CreateProductA() const override
		{
			return new ConcreteProductA2();
		}
		AbstractProductB* CreateProductB() const override
		{
			return new ConcreteProductB2();
		}
	};
}