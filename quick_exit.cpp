#include <cstdlib.hh>
#include "inc.h"

class Static {
    public:

        ~Static() 
        {
            std::cout << "Static dtor\n";
        }
};

class Local {
    public:
        ~Local() 
        {
            std::cout << "Local dtor\n";
        }
};

Static static_variable; // dtor of this object will *not* be called

void atexit_handler()
{
    std::cout << "atexit handler\n";    //will *not* be called
}

void at_quick_exit_handler()
{
    std::cout << "at_quick_exit handler\n";
}

int main()
{
    Local local_variable; // dtor of this object will *not* be called
    int result = std::atexit(atexit_handler);

    if (result != 0) {
        std::cerr << "atexit registration failed\n";
        return EXIT_FAILURE;
    }

    result = std::at_quick_exit(at_quick_exit_handler); // handler will be called

    if (result != 0) {
        std::cerr << "at_quick_exit registration failed\n";
        return EXIT_FAILURE;
    }

    std::cout << "test\n";
    std::quick_exit(EXIT_FAILURE);
}
