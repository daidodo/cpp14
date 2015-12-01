#include <cwctype.hh>
#include "inc.h"

bool classify(wchar_t wc, const std::string& cat)
{
    return std::iswctype(wc, std::wctype(cat.c_str()));
}

void test_iswctype()
{
    std::setlocale(LC_ALL, "ja_JP.UTF-8");
    std::cout << "The character \u6c34 is...\n";
    for(std::string s : {"digit", "alpha", "space", "cntrl", "jkanji"})
        std::cout << s << "? " << std::boolalpha << classify(L'\u6c34', s) << '\n';
}

void test_iswalnum()
{
    wchar_t c = L'\u13ad';

    std::cout << std::hex << std::showbase << std::boolalpha;
    std::cout << "in the default locale, iswalnum(" << (std::wint_t)c << ") = "
        << (bool)std::iswalnum(c) << '\n';
    std::setlocale(LC_ALL, "en_US.utf8");
    std::cout << "in Unicode locale, iswalnum(" << (std::wint_t)c << ") = "
        << (bool)std::iswalnum(c) << '\n';
}

void test_iswalpha()
{
    wchar_t c = L'\u0b83'; // Tamil sign Visarga ('')

    std::cout << std::hex << std::showbase << std::boolalpha;
    std::cout << "in the default locale, iswalpha(" << (std::wint_t)c << ") = "
        << (bool)std::iswalpha(c) << '\n';
    std::setlocale(LC_ALL, "en_US.utf8");
    std::cout << "in Unicode locale, iswalpha(" << (std::wint_t)c << ") = "
        << (bool)std::iswalpha(c) << '\n';
}

void test_iswlower()
{
    wchar_t c = L'\u0444'; // Cyrillic small letter ef ('')

    std::cout << std::hex << std::showbase << std::boolalpha;
    std::cout << "in the default locale, iswlower(" << (std::wint_t)c << ") = "
        << (bool)std::iswlower(c) << '\n';
    std::setlocale(LC_ALL, "en_US.utf8");
    std::cout << "in Unicode locale, iswlower(" << (std::wint_t)c << ") = "
        << (bool)std::iswlower(c) << '\n';
}

void test_iswupper()
{
    wchar_t c = L'\u053d'; // Armenian capital letter xeh ('')

    std::cout << std::hex << std::showbase << std::boolalpha;
    std::cout << "in the default locale, iswupper(" << (std::wint_t)c << ") = "
        << (bool)std::iswupper(c) << '\n';
    std::setlocale(LC_ALL, "en_US.utf8");
    std::cout << "in Unicode locale, iswupper(" << (std::wint_t)c << ") = "
        << (bool)std::iswupper(c) << '\n';
}

void test(wchar_t a3, wchar_t u3, wchar_t j3)
{
    std::wcout << std::boolalpha
        << "          '" << a3 << "'   '" << u3 << "'  '" << j3  << "'\n"
        << "iswdigit "
        << (bool)std::iswdigit(a3) << "  "
        << (bool)std::iswdigit(u3) << " "
        << (bool)std::iswdigit(j3) << '\n'
        << "jdigit:  "
        << (bool)std::iswctype(a3, std::wctype("jdigit")) << ' '
        << (bool)std::iswctype(u3, std::wctype("jdigit")) << ' '
        << (bool)std::iswctype(j3, std::wctype("jdigit")) << '\n';
}

void test_iswdigit()
{
    wchar_t a3 = L'3';  // the ASCII digit 3
    wchar_t u3 = L'三'; // the CJK numeral 3
    wchar_t j3 = L'３'; // the fullwidth digit 3

    std::setlocale(LC_ALL, "en_US.utf8");
    std::wcout << "In american locale:\n";
    test(a3, u3, j3);

    std::wcout << "\nIn japanese locale:\n";
    std::setlocale(LC_ALL, "ja_JP.utf8");
    test(a3, u3, j3);
}

void test_iswgraph()
{
    wchar_t c = L'\u2602';

    std::cout << std::hex << std::showbase << std::boolalpha;
    std::cout << "in the default locale, iswgraph(" << (std::wint_t)c << ") = "
        << (bool)std::iswgraph(c) << '\n';
    std::setlocale(LC_ALL, "en_US.utf8");
    std::cout << "in Unicode locale, iswgraph(" << (std::wint_t)c << ") = "
        << (bool)std::iswgraph(c) << '\n';
}

void test_iswcntrl()
{
    wchar_t c = L'\u2028'; // the Unicode character "line separator" 

    std::cout << std::hex << std::showbase << std::boolalpha;
    std::cout << "in the default locale, iswcntrl(" << (std::wint_t)c << ") = "
        << (bool)std::iswcntrl(c) << '\n';
    std::setlocale(LC_ALL, "en_US.utf8");
    std::cout << "in Unicode locale, iswcntrl(" << (std::wint_t)c << ") = "
        << (bool)std::iswcntrl(c) << '\n';
}

void try_with(wchar_t c, const char* loc)
{
    std::setlocale(LC_ALL, loc);
    std::wcout << "isspace('" << c << "') in " << loc << " locale returned "
        << std::boolalpha << (bool)std::iswspace(c) << '\n';
}

void test_iswspace()
{
    wchar_t EM_SPACE = L'\u2003'; // Unicode character 'EM SPACE'
    try_with(EM_SPACE, "C");
    try_with(EM_SPACE, "en_US.UTF8");
}

void test_iswblank()
{
    wchar_t c = L'\u3000';

    std::cout << std::hex << std::showbase << std::boolalpha;
    std::cout << "in the default locale, iswblank(" << (std::wint_t)c << ") = "
        << (bool)std::iswblank(c) << '\n';
    std::setlocale(LC_ALL, "en_US.utf8");
    std::cout << "in Unicode locale, iswblank(" << (std::wint_t)c << ") = "
        << (bool)std::iswblank(c) << '\n';
}

void test_iswprint()
{
    wchar_t c = L'\u2002'; // en-space
    std::setlocale(LC_ALL, "en_US.utf8");
    std::cout << std::boolalpha << std::hex << std::showbase
        << "in Unicode locale,\n"
        << "iswprint('" << c << "') = "
        << (bool)std::iswprint(c) << '\n';

    c = L'\u0082'; // break permitted
    std::cout << "iswprint('" << c << "') = "
        << (bool)std::iswprint(c) << '\n';
}

void test_iswpunct()
{
    wchar_t c = L'\u2051'; // Two asterisks ('⁑')

    std::cout << std::hex << std::showbase << std::boolalpha;
    std::cout << "in the default locale, iswpunct(" << (std::wint_t)c << ") = "
        << (bool)std::iswpunct(c) << '\n';
    std::setlocale(LC_ALL, "en_US.utf8");
    std::cout << "in Unicode locale, iswpunct(" << (std::wint_t)c << ") = "
        << (bool)std::iswpunct(c) << '\n';
}

void test_towlower()
{
    wchar_t c = L'\u0190'; // Latin capital open E ('Ɛ')

    std::cout << std::hex << std::showbase;
    std::cout << "in the default locale, towlower(" << (std::wint_t)c << ") = "
        << std::towlower(c) << '\n';
    std::setlocale(LC_ALL, "en_US.utf8");
    std::cout << "in Unicode locale, towlower(" << (std::wint_t)c << ") = "
        << std::towlower(c) << '\n';
}

void test_towupper()
{
    wchar_t c = L'\u017f'; // Latin small letter Long S ('ſ')

    std::cout << std::hex << std::showbase;
    std::cout << "in the default locale, towupper(" << (std::wint_t)c << ") = "
        << std::towupper(c) << '\n';
    std::setlocale(LC_ALL, "en_US.utf8");
    std::cout << "in Unicode locale, towupper(" << (std::wint_t)c << ") = "
        << std::towupper(c) << '\n';
}

std::wstring tohira(std::wstring str)
{
    std::transform(str.begin(), str.end(), str.begin(), [](wchar_t c) {
            return std::towctrans(c, std::wctrans("tojhira"));
            });
    return str;
}

void test_towctrans()
{
    std::setlocale(LC_ALL, "ja_JP.UTF-8");
    std::wstring kana = L"ヒラガナ";
    std::wcout << "katakana characters " << kana
        << " are " << tohira(kana) << " in hiragana\n";
}

int main()
{
    test_iswalnum();
    test_iswalpha();
    test_iswlower();
    test_iswupper();
    test_iswctype();
    test_iswdigit();
    test_iswcntrl();
    test_iswgraph();
    test_iswspace();
    test_iswblank();
    test_iswprint();
    test_iswpunct();
    test_towlower();
    test_towupper();
    test_towctrans();
    return 0;
}
