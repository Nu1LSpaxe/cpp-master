/// Split into seperate hierachies (abstraction + implementation)

#include <string>
#include <memory>

namespace DesignPattern
{
	// The Implementaton interface provides primitive operations, 
	// while the BridgeAbstract defiens higher-level operations 
	// based on primitives.
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

	// The BridgeAbstract defines the interface for the "control" part of 
	// the two class hierarchies.
	class BridgeAbstract
	{
	protected:
		std::unique_ptr<BridgeImpl> impl_;
	
	public:
		BridgeAbstract(std::unique_ptr<BridgeImpl> impl)
			: impl_(std::move(impl))
		{
		}
		
		virtual ~BridgeAbstract() = default;

		virtual std::string Operation() const
		{
			return "BridgeAbstract+" + this->impl_->Operation();
		}
	};

	class ExtendedAbstr : public BridgeAbstract
	{
	public:
		ExtendedAbstr(std::unique_ptr<BridgeImpl> impl)
			: BridgeAbstract(std::move(impl))
		{
		}
		std::string Operation() const override
		{
			return "ExtendedAbstr+" + this->impl_->Operation();
		}
	};
}