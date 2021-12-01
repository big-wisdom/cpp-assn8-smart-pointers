#include <cstdint>
#include <iostream>

namespace usu
{
    template <typename T>
    class shared_ptr
    {
        public:
            shared_ptr(T* t) : pointer(t), count(new unsigned int(1)){}

            shared_ptr(const shared_ptr &s) : pointer(s.pointer), count(s.count)
            {
                *count += 1;
            }
            //shared_ptr(T[] t, unsigned int n) : pointer(t){}

            T* pointer;

            unsigned int use_count()
            {
                return *count;
            }

            T* get()
            {
                return pointer;
            }

            shared_ptr& operator=(shared_ptr s)
            {
                //if(this != s)
                //{
                    count = s.count;
                    pointer = s.pointer;
                //}
                return *this;
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
            unsigned int* count;

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
