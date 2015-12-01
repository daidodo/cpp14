#include <cctype.hh>
#include <clocale.hh>
#include "inc.h"

void test_isalnum()
{
    unsigned char c = '\xdf'; // German letter ÃŸ in ISO-8859-1

    std::cout << "isalnum(\'\\xdf\', default C locale) returned "
        << std::boolalpha << (bool)std::isalnum(c) << '\n';

    std::setlocale(LC_ALL, "de_DE.iso88591");
    std::cout << "isalnum(\'\\xdf\', ISO-8859-1 locale) returned "
        << std::boolalpha << (bool)std::isalnum(c) << '\n';
}

void test_isalpha()
{
    unsigned char c = '\xdf'; // German letter ß in ISO-8859-1

    std::cout << "isalpha(\'\\xdf\', default C locale) returned "
        << std::boolalpha << (bool)std::isalpha(c) << '\n';

    std::setlocale(LC_ALL, "de_DE.iso88591");
    std::cout << "isalpha(\'\\xdf\', ISO-8859-1 locale) returned "
        << std::boolalpha << (bool)std::isalpha(c) << '\n';
}

void test_islower()
{
    unsigned char c = '\xe5'; // letter å in ISO-8859-1

    std::cout << "islower(\'\\xe5\', default C locale) returned "
        << std::boolalpha << (bool)std::islower(c) << '\n';

    std::setlocale(LC_ALL, "en_GB.iso88591");
    std::cout << "islower(\'\\xe5\', ISO-8859-1 locale) returned "
        << std::boolalpha << (bool)std::islower(c) << '\n';
}

void test_isupper()
{
    unsigned char c = '\xc6'; // letter Æ in ISO-8859-1

    std::cout << "isupper(\'\\xc6\', default C locale) returned "
        << std::boolalpha << (bool)std::isupper(c) << '\n';

    std::setlocale(LC_ALL, "en_GB.iso88591");
    std::cout << "isupper(\'\\xc6\', ISO-8859-1 locale) returned "
        << std::boolalpha << (bool)std::isupper(c) << '\n';
}

void test_iscntrl()
{
    unsigned char c = '\x94'; // the control code CCH in ISO-8859-1

    std::cout << "iscntrl(\'\\x94\', default C locale) returned "
        << std::boolalpha << (bool)std::iscntrl(c) << '\n';

    std::setlocale(LC_ALL, "en_GB.iso88591");
    std::cout << "iscntrl(\'\\x94\', ISO-8859-1 locale) returned "
        << std::boolalpha << (bool)std::iscntrl(c) << '\n';
}

void test_isgraph()
{
    unsigned char c = '\xb6'; // the character ¶ in ISO-8859-1

    std::cout << "isgraph(\'\\xb6\', default C locale) returned "
        << std::boolalpha << (bool)std::isgraph(c) << '\n';

    std::setlocale(LC_ALL, "en_GB.iso88591");
    std::cout << "isgraph(\'\\xb6\', ISO-8859-1 locale) returned "
        << std::boolalpha << (bool)std::isgraph(c) << '\n';
}

void test_isprint()
{
    unsigned char c = '\xa0'; // the non-breaking space in ISO-8859-1

    std::cout << "isprint(\'\\xa0\', default C locale) returned "
        << std::boolalpha << (bool)std::isprint(c) << '\n';

    std::setlocale(LC_ALL, "en_GB.iso88591");
    std::cout << "isprint(\'\\xa0\', ISO-8859-1 locale) returned "
        << std::boolalpha << (bool)std::isprint(c) << '\n';
}

void test_ispunct()
{
    unsigned char c = '\xd7'; // the character × (multiplication sign) in ISO-8859-1

    std::cout << "ispunct(\'\\xd7\', default C locale) returned "
        << std::boolalpha << (bool)std::ispunct(c) << '\n';

    std::setlocale(LC_ALL, "en_GB.iso88591");
    std::cout << "ispunct(\'\\xd7\', ISO-8859-1 locale) returned "
        << std::boolalpha << (bool)std::ispunct(c) << '\n';
}

void test_tolower()
{
    unsigned char c = '\xb4';
    // but ´ (acute accent) in ISO-8859-1 

    std::setlocale(LC_ALL, "en_US.iso88591");
    std::cout << std::hex << std::showbase;
    std::cout << "in iso8859-1, tolower('0xb4') gives "
        << std::tolower(c) << '\n';
    std::setlocale(LC_ALL, "en_US.iso885915");
    std::cout << "in iso8859-15, tolower('0xb4') gives "
        << std::tolower(c) << '\n';
}

void test_toupper()
{
    unsigned char c = '\xb8';
    // but ¸ (cedilla) in ISO-8859-1 

    std::setlocale(LC_ALL, "en_US.iso88591");
    std::cout << std::hex << std::showbase;
    std::cout << "in iso8859-1, toupper('0xb8') gives " << std::toupper(c) << '\n';
    std::setlocale(LC_ALL, "en_US.iso885915");
    std::cout << "in iso8859-15, toupper('0xb8') gives " << std::toupper(c) << '\n';
}

int main()
{
    test_isalnum();
    test_isalpha();
    test_islower();
    test_isupper();
    test_iscntrl();
    test_isgraph();
    test_isprint();
    test_ispunct();
    test_tolower();
    test_toupper();
    return 0;
}
