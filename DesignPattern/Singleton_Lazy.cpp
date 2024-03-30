/**
 * The Singleton class defines the `GetInstance` method that serves as an
 * alternative to constructor and lets clients access the same instance of this
 * class over and over.
 */

#include <iostream>
#include <mutex>

namespace DesignPattern
{
    namespace Singleton 
    {
        class Lazy
        {
            /**
             * The Singleton's constructor/destructor should always be private to
             * prevent direct construction/desctruction calls with the `new`/`delete`
             * operator.
             */

        private:
            static Lazy* pInstance_;
            static std::mutex mutex_;

        protected:
            Lazy(const std::string value) : value_(value) {}
            ~Lazy() = default;
            std::string value_;

        public:
            /**
            * Singletons shoudl not be cloneable.
            */
            Lazy(Lazy& other) = delete;
            /**
            * Singletons should not be assignable.
            */
            void operator=(const Lazy&) = delete;

            /**
            * This is the static method that controls the access to the singleton
            * instance. On the first run, it creates a singleton object and places it
            * into the static field. On subsequent runs, it returns the client existing
            * object stored in the static field.
            */
            static Lazy* Instance(const std::string& value);

            std::string value() const { return value_; }
        };
    }
}


namespace DesignPattern
{
    namespace Singleton
    {
        /**
         * Static methods should be defined outside the class.
         */
        Lazy* Lazy::pInstance_{ nullptr };
        std::mutex DesignPattern::Singleton::Lazy::mutex_;

        /**
        * The first time call Instance lock the storage location
        * and then make sure that variable is null, then set value.
        */
        Lazy* Lazy::Instance(const std::string& value)
        {
            std::lock_guard<std::mutex> lock(mutex_);
            if (pInstance_ == nullptr)
            {
                pInstance_ = new Lazy(value);
            }
            return pInstance_;
        }
    }

}