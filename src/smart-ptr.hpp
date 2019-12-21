#ifndef SMARTPTR_H
#define SMARTPTR_H


#include <iostream>
#include <utility>
#include <exception>


template <class T>
class SmartPtr
{
public:
    // Constructor without arguments.
    SmartPtr()
    {
        ref_count_ = new int(0);
        ptr_ = new T;
        *ref_count_ = 1;
    }

    // Constructor with pointer argument.
    SmartPtr(T* ptr)
    {
        ref_count_ = new int(0);
        
        if (ptr != nullptr) {
            ptr_ = new T(*ptr);
            *ref_count_ = 1;
        
        } else {
            ptr_ = nullptr;
        }
    }

    // Copy constructor.
    SmartPtr(const SmartPtr<T>& other)
        : ptr_ { other.ptr_ },
          ref_count_ { other.ref_count_ }
    {
        *ref_count_ += 1;
    }

    // Destructor.
    ~SmartPtr()
    {
        *ref_count_ -= 1;
        
        // If there are some smart pointer instances yet do not delete
        // the pointer.
        if (*ref_count_ <= 0) {
            if (ptr_ != nullptr) {
                delete ptr_;
            }

            delete ref_count_;
        }
    }

    // Dereferencing operator.
    T operator*() const
    {
        // If the pointer is valid return the value or
        // throw an exception otherwise.
        if (ptr_ != nullptr) {
            return *ptr_;
        
        } else {
           throw std::runtime_error(
                "Segmentation fault, nullptr dereferencing");
        }
    }

    // An arrow operator.
    T* operator->() const
    {
        // If the pointer is valid return it or
        // throw an exception otherwise.
        if (ptr_ != nullptr) {
            return ptr_;
        
        } else {
           throw std::runtime_error(
                "Segmentation fault, nullptr dereferencing");
        }
    }

    // Reset the pointer contents by the argument pointer contents.
    void reset(T* ptr)
    {
        if (ptr != nullptr) {
            *ptr_ = *ptr;
        
        } else {
            delete ptr_;
            ptr_ = nullptr;
            *ref_count_ = 0;
        }
    }

    // Swap the contents with the other argument.
    void swap(SmartPtr<T>& other)
    {
        std::swap(*ptr_, *(other.ptr_));
    }

    // Get raw pointer.
    T* get() const
    {
        return ptr_;
    }

private:
    T* ptr_;
    int* ref_count_;
};


// Make smart pointer like std::make_shared, std::make_unique, etc.
template <class T>
SmartPtr<T> make_smart_ptr()
{
    return SmartPtr<T>();
}

template <class T>
SmartPtr<T> make_smart_ptr(T val)
{
    return SmartPtr<T>(&val);
}

// Comparising operator.
template <class T, class U>
bool operator==(const SmartPtr<T>& lhs, const SmartPtr<U>& rhs) noexcept
{
    return lhs.get() == rhs.get();
}


#endif
