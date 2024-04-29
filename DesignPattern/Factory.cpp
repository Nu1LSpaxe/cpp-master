/// Applicability
/// Use case 1:
///		When you don’t know beforehand the exact types and dependencies
///		of the objects your code should work with
/// Use case 2:
///		When you want to provide users of your library or framework with
///		a way to extend its internal components
/// Use case 3:
///		When you want to save system resources by reusing existing objects 
///		instead of rebuilding them each time

#include <string>
#include <memory>

namespace DesignPattern
{
	class FactoryProduct
	{
	public:
		virtual ~FactoryProduct() {}
		virtual std::string Operation() const = 0;
	};

	/**
	* Implementations of the FactoryProduct interface
	*/
	class ConcreteProductF1 : public FactoryProduct
	{
	public:
		std::string Operation() const override
		{
			return "ConcreteProductF1";
		}
	};
	class ConcreteProductF2 : public FactoryProduct
	{
	public:
		std::string Operation() const override
		{
			return "ConcreteProductF2";
		}
	};

	// Factory class declares the factory method and return a 
	// FactoryProduct class.
	// Factory's sublcasses provide the implementation methods.
	class Factory
	{
	public:
		virtual ~Factory() = default;
		virtual std::unique_ptr<FactoryProduct> Implementation() const = 0;

		// It usually contains core business logic that relies on 
		// FactoryProduct objects, returned by the factory method.
		// Subclasses can indirectly change the business logic by 
		// overriding, and return a different type of product.
		std::string DoOperation() const
		{
			return this->Implementation()->Operation();
		}
	};

	class ConcreteFactory1 : public Factory
	{
	public:
		std::unique_ptr<FactoryProduct> Implementation() const override
		{
			return std::make_unique<ConcreteProductF1>();
		}
	};

	class ConcreteFactory2 : public Factory
	{
	public:
		std::unique_ptr<FactoryProduct> Implementation() const override
		{
			return std::make_unique<ConcreteProductF2>();
		}
	};
}