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

            ~shared_ptr()
            {
                *count -= 1;
                if(*count == 0)
                    delete count;
            }

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
                *count -= 1;
                count = s.count;
                *count += 1;
                pointer = s.pointer;
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

    // getting some weird warnings
    template <typename T>
    class shared_ptr<T[]>
    {
        public:
            shared_ptr(T* t, std::size_t number) : pointer(t), count(new unsigned int(1)), thisSize(number){}
            ~shared_ptr()
            {
                *count -= 1;

                if (count == 0)
                {
                    delete[] pointer;
                    delete count;
                }
            }
            
            T& operator[](int index)
            {
                if (static_cast<std::size_t>(index) >= thisSize)
                {
                    std::cout << "Index " << index << " out of bounds" << std::endl;
                    exit(1);
                }

                return pointer[index];
            }

            std::size_t size()
            {
                return thisSize;
            }
        private:
            T* pointer;
            unsigned int* count;
            std::size_t thisSize;
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
