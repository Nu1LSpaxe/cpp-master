/// Compose objects into tree structures and work as individual

#include <string>
#include <list>

namespace DesignPattern
{
	class CompositeComponent
	{
	protected:
		CompositeComponent* parent_;

	public:
		virtual ~CompositeComponent() {}
		void SetParent(CompositeComponent* parent)
		{
			this->parent_ = parent;
		}
		CompositeComponent* GetParent() const
		{
			return this->parent_;
		}

		// Methods to manager children
		virtual void Add(CompositeComponent* component) {}
		virtual void Remove(CompositeComponent* component) {}

		virtual bool IsComposite() const
		{
			return false;
		}

		virtual std::string Operation() const = 0;
	};

	class Leaf : public CompositeComponent
	{
	public:
		std::string Operation() const override
		{
			return "Leaf";
		}
	};

	// Composite represents the complex components
	class Composite : public CompositeComponent
	{
	protected:
		std::list<CompositeComponent*> children_;

	public:
		void Add(CompositeComponent* component) override
		{
			this->children_.push_back(component);
			component->SetParent(this);
		}
		void Remove(CompositeComponent* component) override
		{
			children_.remove(component);
			component->SetParent(nullptr);
		}
		bool IsComposite() const override
		{
			return true;
		}

		std::string Operation() const override
		{
			std::string result;

			for (const CompositeComponent* c : children_)
			{
				if (c == children_.back())
				{
					result += c->Operation();
				}
				else
				{
					result += c->Operation() + "+";
				}
			}
			return "Branch(" + result + ")";
		}
	};

	std::string GetComponent(CompositeComponent* component)
	{
		return  component->Operation();
	}

	std::string GetComponents(
		CompositeComponent* component1, CompositeComponent* component2)
	{
		if (component1->IsComposite())
		{
			component1->Add(component2);
		}
		return component1->Operation();
	}
}