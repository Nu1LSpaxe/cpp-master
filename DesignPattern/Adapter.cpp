/// Applicability
/// Use case 1:
///		When you want to use some existing class, but its 
///		interface isn’t compatible with the rest of your code
/// Use case 2:
///		When you want to reuse several existing subclasses that 
///		lack some common functionality that can’t be added to the
///		superclass

#include <string>
#include <memory>

namespace DesignPattern
{
	// The Target defiens the domain-specific interface used by 
	// client code
	class Target
	{
	public:
		virtual ~Target() = default;

		virtual std::string Request() const
		{
			return "Target";
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
	// with Target's interface
	class Adapter : public Target
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