#include "smart-ptr.hpp"

#include <iostream>
#include <string>
#include <memory>


int main()
{
    // Creating test.
    // Also operator*() and operator->() test.
    {
        SmartPtr<int> ptr1 = make_smart_ptr<int>(1);
        SmartPtr<std::string> ptr2 = make_smart_ptr<std::string>("s1");

        std::cerr << "Line #" << __LINE__ << ": " << *ptr1 << std::endl;
        std::cerr << "Line #" << __LINE__ << ": " << *ptr2 << std::endl;
        std::cerr << "Line #" << __LINE__ << ": "
                  << ptr2->c_str() << std::endl;

        try {
            SmartPtr<int> ptr3(nullptr);
            std::cerr << "Line #" << __LINE__ << ": " << *ptr3 << std::endl;

        } catch (const std::runtime_error& exc) {
            std::cerr << "Line #" << __LINE__ << ": "
                      << exc.what() << std::endl;
        }
    }


    // Copy test.
    {
        SmartPtr<int> ptr1 = make_smart_ptr<int>(2);

        {
            SmartPtr<int> ptr2(ptr1);
            SmartPtr<int> ptr3 = ptr1;
            std::cerr << "Line #" << __LINE__ << ": " << *ptr2 << std::endl;
            std::cerr << "Line #" << __LINE__ << ": " << *ptr3 << std::endl;
        }

        std::cerr << "Line #" << __LINE__ << ": " << *ptr1 << std::endl;
    }


    // Reset test.
    {
        SmartPtr<int> ptr = make_smart_ptr<int>(3);
        std::cerr << "Line #" << __LINE__ << ": " << *ptr << std::endl;
        
        std::shared_ptr<int> item = std::make_shared<int>(4);
        ptr.reset(item.get());
        std::cerr << "Line #" << __LINE__ << ": " << *ptr << std::endl;

        try {
            ptr.reset(nullptr);
            std::cerr << "Line #" << __LINE__ << ": " << *ptr << std::endl;

        } catch (const std::runtime_error& exc) {
            std::cerr << "Line #" << __LINE__ << ": "
                      << exc.what() << std::endl;
        }
    }


    // Swap test.
    {
        SmartPtr<int> ptr1 = make_smart_ptr<int>(5);
        SmartPtr<int> ptr2 = make_smart_ptr<int>(6);

        std::cerr << "Line #" << __LINE__ << ": " << *ptr1 << std::endl;
        std::cerr << "Line #" << __LINE__ << ": " << *ptr2 << std::endl;

        ptr1.swap(ptr2);

        std::cerr << "Line #" << __LINE__ << ": " << *ptr1 << std::endl;
        std::cerr << "Line #" << __LINE__ << ": " << *ptr2 << std::endl;
    }


    // get() test.
    {
        SmartPtr<int> ptr = make_smart_ptr<int>(7);
        int* item = ptr.get();
        std::cerr << "Line #" << __LINE__ << ": " << *ptr << std::endl;
        std::cerr << "Line #" << __LINE__ << ": " << *item << std::endl;
    }


    // Comparison test.
    {
        SmartPtr<int> ptr1 = make_smart_ptr<int>(8);
        SmartPtr<int> ptr2(ptr1);
        std::cerr << "Line #" << __LINE__ << ": "
                  << std::boolalpha
                  << (ptr1 == ptr2)
                  << std::endl;

        SmartPtr<int> ptr3 = make_smart_ptr<int>(9);
        std::cerr << "Line #" << __LINE__ << ": "
                  << std::boolalpha
                  << (ptr1 == ptr3)
                  << std::endl;
    }


    return 0;
}
