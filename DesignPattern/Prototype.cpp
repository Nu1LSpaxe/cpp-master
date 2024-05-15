/// Copy existing objects without dependent on classes

#include <string>
#include <unordered_map>
#include <memory>

namespace DesignPattern
{
	enum Type
	{
		PROTOTYPE_1 = 0,
		PROTOTYPE_2
	};

	class Prototype
	{
	protected:
		std::string p_name_;
		float p_field_;

	public:
		Prototype() {}
		Prototype(std::string p_name) : p_name_(p_name) {}
		virtual ~Prototype() {}
		virtual std::unique_ptr<Prototype> Clone() const = 0;
		virtual float SetField(float p_field)
		{
			this->p_field_ = p_field;
			return this->p_field_;
		}

	};

	/**
	* ConcreteProtype1 is a Sub-Class of Prototype and
	* implement the Clone SetField
	*/
	class ConcretePrototype1 : public Prototype
	{
	private:
		float cp_field1_;

	public:
		ConcretePrototype1(std::string p_name, float cp_field)
			: Prototype(p_name), cp_field1_(cp_field) 
		{
		}
		
		/**
		* Clone method return a Pointer, so client has the 
		* responsability to free the memory.
		*/
		std::unique_ptr<Prototype> Clone() const override
		{
			return std::make_unique<ConcretePrototype1>(*this);
		}
	};

	class ConcretePrototype2 : public Prototype
	{
	private:
		float cp_field2_;

	public:
		ConcretePrototype2(std::string p_name, float cp_field) : Prototype(p_name), cp_field2_(cp_field)
		{
		}

		std::unique_ptr<Prototype> Clone() const override
		{
			return std::make_unique<ConcretePrototype2>(*this);
		}
	};

	class PrototypeFactory
	{
	private:
		std::unordered_map<Type, 
			std::unique_ptr<Prototype>, std::hash<int>> prototypes_;

	public:
		PrototypeFactory()
		{
			prototypes_[Type::PROTOTYPE_1] =
				std::make_unique<ConcretePrototype1>("PROTOTYPE_1", 50.f);
			prototypes_[PROTOTYPE_2] =
				std::make_unique<ConcretePrototype2>("PROTOTYPE_2", 60.f);
		}


		std::unique_ptr<Prototype> CreatePrototype(Type type)
		{
			return prototypes_[type]->Clone();
		}
	};
}