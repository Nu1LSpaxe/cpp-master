/// Applicability
/// Use case 1:
///     When a class in your program should have just a single instance 
///     available to all clients
/// Use case 2:
///     When you need stricter control over global variables

#include <iostream>
#include <mutex>

namespace DesignPattern
{
    class Singleton_Lazy
    {
        // The Singleton's constructor/destructor should always be 
        // private to prevent direct construction/desctruction calls 
        // with the `new`/`delete` operator.

    private:
        static Singleton_Lazy* pInstance_;
        static std::mutex mutex_;

    protected:
        Singleton_Lazy(const std::string value) : value_(value) {}
        ~Singleton_Lazy() = default;
        std::string value_;

    public:
        // Singletons shoudl not be cloneable
        Singleton_Lazy(Singleton_Lazy& other) = delete;
        // Singletons should not be assignable
        void operator=(const Singleton_Lazy&) = delete;


        // This is the static method that controls the access to the 
        // singleton instance.
        // On the first run, it creates a singleton object and places it 
        // into the static field. On subsequent runs, it returns the client 
        // existing object stored in the static field.
        static Singleton_Lazy* Instance(const std::string& value);

        std::string value() const { return value_; }
    };
}


namespace DesignPattern
{
    // Static methods should be defined outside the class.
    Singleton_Lazy* Singleton_Lazy::pInstance_{ nullptr };
    std::mutex DesignPattern::Singleton_Lazy::mutex_;

    // The first time call Instance lock the storage location and then
    // make sure that variable is null, then set value.
    Singleton_Lazy* Singleton_Lazy::Instance(const std::string& value)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        if (pInstance_ == nullptr)
        {
            pInstance_ = new Singleton_Lazy(value);
        }
        return pInstance_;
    }
}