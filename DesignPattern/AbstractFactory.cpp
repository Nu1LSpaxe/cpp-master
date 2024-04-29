/// Applicability
/// Use case 1:
///		When your code needs to work with various families of related products,
///		but you don’t want it to depend on the concrete classes of those products
/// Use case 2:
///		When you have a class with a set of Factory Methods that blur its 
///		primary responsibility

#include <string>
#include <memory>

namespace DesignPattern
{
	class AbstractProductA
	{
	public:
		virtual ~AbstractProductA() = default;
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
		virtual ~AbstractProductB() = default;
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
		virtual std::unique_ptr<AbstractProductA> CreateProductA() const = 0;
		virtual std::unique_ptr<AbstractProductB> CreateProductB() const = 0;
	};

	class ConcreteAbstractFactory1 : public AbstractFactory
	{
	public:
		std::unique_ptr<AbstractProductA> CreateProductA() const override
		{
			return std::make_unique<ConcreteProductA1>();
		}
		std::unique_ptr<AbstractProductB> CreateProductB() const override
		{
			return std::make_unique<ConcreteProductB1>();
		}
	};
	
	class ConcreteAbstractFactory2 : public AbstractFactory
	{
	public:
		std::unique_ptr<AbstractProductA> CreateProductA() const override
		{
			return std::make_unique<ConcreteProductA2>();
		}
		std::unique_ptr<AbstractProductB> CreateProductB() const override
		{
			return std::make_unique<ConcreteProductB2>();
		}
	};
}