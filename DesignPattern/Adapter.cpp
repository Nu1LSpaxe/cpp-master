/// Allow objects with incompatible interfaces to collaborate

#include <string>
#include <memory>

namespace DesignPattern
{
	// The AdapterTarget defiens the domain-specific interface used by 
	// client code
	class AdapterTarget
	{
	public:
		virtual ~AdapterTarget() = default;

		virtual std::string Request() const
		{
			return "AdapterTarget";
		}
	};
	 
	// The Adaptee interface is incompatible with the existing 
	// client code
	class Adaptee
	{
	public:
		std::string Request() const
		{
			return "eetpadA";
		}
	};
	
	// The Adapter makes the Adaptee's interface compatible 
	// with AdapterTarget's interface
	class Adapter : public AdapterTarget
	{
	private:
		Adaptee* adaptee_;

	public:
		Adapter(Adaptee* adaptee) : adaptee_(adaptee) {}

		std::string Request() const override
		{
			std::string toReverse = this->adaptee_->Request();
			std::reverse(toReverse.begin(), toReverse.end());
			return toReverse;
		}
	};
}