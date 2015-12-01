#include <cinttypes.hh>
#include <cstdlib.hh>
#include "inc.h"

std::string itoa(intmax_t n, int base)
{
    std::string buf;
    std::imaxdiv_t dv{}; dv.quot = n;
    do {
        dv = std::imaxdiv(dv.quot, base);
        buf += "0123456789abcdef"[std::abs(dv.rem)];  // string literals are arrays
    } while(dv.quot);
    if(n<0) buf += '-';
    return {buf.rbegin(), buf.rend()};
}

void test_imaxdiv()
{
    std::cout << itoa(12345, 10) << '\n'
        << itoa(-12345, 10) << '\n'
        << itoa(65535, 16) << '\n';
}

void test_imaxabs()
{
    std::cout << "imaxabs(+3) = " << std::imaxabs(3) << '\n'
        << "imaxabs(-3) = " << std::imaxabs(-3) << '\n';
}

void test_strtoimax()
{
    std::string str = "helloworld";
    std::intmax_t val = std::strtoimax(str.c_str(), nullptr, 36);
    std::cout << str << " in base 36 is " << val << " in base 10\n";

    char* nptr;
    val = std::strtoimax(str.c_str(), &nptr, 30);
    if(nptr != &str[0] + str.size())
        std::cout << str << " in base 30 is invalid."
            << " The first invalid digit is " << *nptr << '\n';
}

void test_wcstoimax()
{
    std::wstring str = L"helloworld";
    std::intmax_t val = std::wcstoimax(str.c_str(), nullptr, 36);
    std::wcout << str << " in base 36 is " << val << " in base 10\n";

    wchar_t* nptr;
    val = std::wcstoimax(str.c_str(), &nptr, 30);
    if(nptr != &str[0] + str.size())
        std::wcout << str << " in base 30 is invalid."
            << " The first invalid digit is " << *nptr << '\n';
}

int main()
{
    test_imaxdiv();
    test_imaxabs();
    test_strtoimax();
    test_wcstoimax();
    return 0;
}
