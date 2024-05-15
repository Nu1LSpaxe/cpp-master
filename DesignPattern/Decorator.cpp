/// Add new behaviors dynamically by placing in special wrapper

#include <string>

namespace DesignPattern
{
	class DecoratorComponent
	{
	public:
		virtual ~DecoratorComponent() {}
		virtual std::string Operation() const = 0;
	};

	class ConcreteComponent : public DecoratorComponent
	{
	public:
		std::string Operation() const override
		{
			return "ConcreteComponent";
		}
	};

	class Decorator : public DecoratorComponent
	{
	protected:
		DecoratorComponent* component_;

	public:
		Decorator(DecoratorComponent* component) 
			: component_(component)
		{
		}
		
		std::string Operation() const override
		{
			return this->component_->Operation();
		}
	};

	class ConcreteDecorator1 : public Decorator
	{
	public:
		ConcreteDecorator1(DecoratorComponent* component)
			: Decorator(component)
		{
		}
		std::string Operation() const override
		{
			return "ConcreteDecorator1(" + Decorator::Operation() + ")";
		}
	};

	class ConcreteDecorator2 : public Decorator
	{
	public:
		ConcreteDecorator2(DecoratorComponent* component) 
			: Decorator(component)
		{
		}

		std::string Operation() const override
		{
			return "ConcreteDecorator2(" + Decorator::Operation() + ")";
		}
	};

	std::string GetComponent(DecoratorComponent* component)
	{
		return component->Operation();
	}
}