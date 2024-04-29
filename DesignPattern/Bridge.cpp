/// Applicability
/// Use case 1:
///		When you want to divide and organize a monolithic class that has 
///		several variants of some functionality
/// Use case 2:
///		When you need to extend a class in several orthogonal dimensions

#include <string>
#include <memory>

namespace DesignPattern
{
	// The Implementaton interface provides primitive operations, while
	// the BridgeAbstr defiens higher-level operations based on primitives.
	class BridgeImpl
	{
	public:
		virtual ~BridgeImpl() = default;
		virtual std::string Operation() const = 0;
	};

	// Each Concrete BridgeImpl corresponds to a specific platform
	class ConcreteBridgeA : public BridgeImpl
	{
	public:
		std::string Operation() const override
		{
			return "ConcreteA";
		}
	};

	class ConcreteBridgeB : public BridgeImpl
	{
	public:
		std::string Operation() const override
		{
			return "ConcreteB";
		}
	};

	// The BridgeAbstr defines the interface for the "control" part of 
	// the two class hierarchies.
	class BridgeAbstr
	{
	protected:
		std::unique_ptr<BridgeImpl> impl_;
	
	public:
		BridgeAbstr(std::unique_ptr<BridgeImpl> impl)
			: impl_(std::move(impl))
		{
		}
		
		virtual ~BridgeAbstr() = default;

		virtual std::string Operation() const
		{
			return "BridgeAbstr+" + this->impl_->Operation();
		}
	};

	class ExtendedAbstr : public BridgeAbstr
	{
	public:
		ExtendedAbstr(std::unique_ptr<BridgeImpl> impl)
			: BridgeAbstr(std::move(impl))
		{
		}
		std::string Operation() const override
		{
			return "ExtendedAbstr+" + this->impl_->Operation();
		}
	};
}