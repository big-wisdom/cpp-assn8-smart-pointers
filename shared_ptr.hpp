#include <cstdint>
#include <iostream>

namespace usu
{
    template <typename T>
    class shared_ptr
    {
        public:
            shared_ptr(T* t) : pointer(t){}

            shared_ptr(T[] t, unsigned int n) : pointer(t){}

            T* pointer;

            std::uint64_t use_count()
            {
                return count;
            }

            T* get()
            {
                return pointer;
            }

            T* operator->()
            {
                return pointer;
            }

            T& operator *()
            {
                return *pointer;
            }

        private:
            std::uint64_t count = 0;

    };

    template <typename T, typename... Args>
    shared_ptr<T> make_shared(Args&&... args)
    {
        return shared_ptr<T>(new T(std::forward<Args>(args)...));
    }

    template <typename T, unsigned int N>
    shared_ptr<T[]> make_shared_array()
    {
        return shared_ptr<T[]>(new T[N], N);
    }
}
