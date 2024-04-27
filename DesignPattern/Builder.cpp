/// Applicability
/// Use case 1:
///		To get rid of a “telescoping constructor”.
/// Use case 2:
///		When you want your code to be able to create different 
///		representations of some product
/// Use case 3:
///		To construct Composite trees or other complex objects.

#include <string>
#include <vector>

namespace DesignPattern
{
	class BuilderProduct
	{
	public:
		std::vector<std::string> parts_;

		std::string ListParts() const
		{
			std::string details;

			for (size_t i{ 0 }; i < parts_.size(); i++)
			{
				if (parts_[i] == parts_.back())
					details.append(parts_[i]);
				else
					details.append(parts_[i] + "+");
			}
			return details;
		}
	};

	// Create the different parts of the Product objects
	class Builder
	{
	public:
		virtual ~Builder() {}
		virtual void ProducePartA() const = 0;
		virtual void ProducePartB() const = 0;
		virtual void ProducePartC() const = 0;
	};

	class ConcreteBuilder1 : public Builder
	{
	private:
		BuilderProduct* product;

	public:
		ConcreteBuilder1() { this->Reset(); }
		~ConcreteBuilder1() { delete product; }

		void Reset() { this->product = new BuilderProduct(); }

		// All production steps work with the same product instance
		void ProducePartA() const override
		{
			this->product->parts_.push_back("PartA1");
		}
		void ProducePartB() const override
		{
			this->product->parts_.push_back("PartB1");
		}
		void ProducePartC() const override
		{
			this->product->parts_.push_back("PartC1");
		}

		// Concrete Builders are supposed to provide their own methods
		// for retrieving results.
		// After returning the end result to the client, a builder
		// instance is expected to be ready to start another product.
		BuilderProduct* GetProduct()
		{
			BuilderProduct* result = this->product;
			this->Reset();
			return result;
		}
	};

	// The Director is only responsible for executing the building steps
	// in particular sequence. (Optional class)
	class Director
	{
	private:
		Builder* builder_;
		
		// The Director works with any builder instances that the clients
		// passes to it.
	public:
		void SetBuilder(Builder* builder)
		{
			this->builder_ = builder;
		}

		void BuildMinimalViableProduct()
		{
			this->builder_->ProducePartA();
		}
		void BuildFullFeaturedProduct()
		{
			this->builder_->ProducePartA();
			this->builder_->ProducePartB();
			this->builder_->ProducePartC();
		}
	};
}