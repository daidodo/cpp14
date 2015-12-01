#include <clocale.hh>
#include <ctime.hh>
#include "inc.h"

void __show(const std::lconv * lc)
{
    std::cout<<"Show locale lc(@"<<lc<<")\n";
    __SHOW(lc->decimal_point);
    __SHOW(lc->thousands_sep);
    __SHOW2(lc->grouping, int(lc->grouping[0]));
    __SHOW(lc->mon_decimal_point);
    __SHOW(lc->mon_thousands_sep);
    __SHOW2(lc->mon_grouping, int(lc->grouping[0]));
    __SHOW(lc->positive_sign);
    __SHOW(lc->negative_sign);
    __SHOW(lc->currency_symbol);
    __SHOW2(lc->frac_digits, int(lc->frac_digits));
    __SHOW2(lc->p_cs_precedes, int(lc->p_cs_precedes));
    __SHOW2(lc->n_cs_precedes, int(lc->n_cs_precedes));
    __SHOW2(lc->p_sep_by_space, int(lc->p_sep_by_space));
    __SHOW2(lc->n_sep_by_space, int(lc->n_sep_by_space));
    __SHOW2(lc->p_sign_posn, int(lc->p_sign_posn));
    __SHOW2(lc->n_sign_posn, int(lc->n_sign_posn));
    __SHOW(lc->int_curr_symbol);
    __SHOW2(lc->int_frac_digits, int(lc->int_frac_digits));
    __SHOW2(lc->int_p_cs_precedes, int(lc->int_p_cs_precedes));
    __SHOW2(lc->int_n_cs_precedes, int(lc->int_n_cs_precedes));
    __SHOW2(lc->int_p_sep_by_space, int(lc->int_p_sep_by_space));
    __SHOW2(lc->int_n_sep_by_space, int(lc->int_n_sep_by_space));
    __SHOW2(lc->int_p_sign_posn, int(lc->int_p_sign_posn));
    __SHOW2(lc->int_n_sign_posn, int(lc->int_n_sign_posn));
}

void test_lconv()
{
    __show(std::localeconv());
    std::setlocale(LC_ALL, "ja_JP.UTF-8");
    __show(std::localeconv());
    std::setlocale(LC_ALL, "zh_CN.UTF-8");
    __show(std::localeconv());

    std::setlocale(LC_ALL, "ja_JP.UTF-8");
    std::lconv* lc = std::localeconv();
    std::cout << "\nJapanese currency symbol: " << lc->currency_symbol
        << '(' << lc->int_curr_symbol << ")\n";
}

void test_LC()
{
    std::setlocale(LC_ALL, "en_US.UTF-8"); // the C locale will be the UTF-8 enabled English
    std::setlocale(LC_NUMERIC, "zh_CN");   // decimal dot will be Chinese
    std::setlocale(LC_TIME, "ja_JP");      // date/time formatting will be Japanese
    wchar_t str[100];
    std::time_t t = std::time(nullptr);
    std::wcsftime(str, 100, L"%A %c", std::localtime(&t));
    std::wcout<<L"Number: "<<3.14<<L"\nDate: "<<str<<L"\n";
}

void test_setlocale()
{
    // the C locale will be UTF-8 enabled English;
    // decimal dot will be German
    // date and time formatting will be Japanese
    std::setlocale(LC_ALL, "en_US.UTF-8");
    std::setlocale(LC_NUMERIC, "de_DE");
    std::setlocale(LC_TIME, "ja_JP");

    wchar_t str[100];
    std::time_t t = std::time(NULL);
    std::wcsftime(str, 100, L"%A %c", std::localtime(&t));
    std::wprintf(L"Number: %.2f\nDate: %Ls\n", 3.14, str);
}

void test_localeconv()
{
    std::setlocale(LC_ALL, "ja_JP.UTF-8");
    std::lconv* lc = std::localeconv();
    std::cout << "Japanese currency symbol: " << lc->currency_symbol
        << '(' << lc->int_curr_symbol << ")\n";
}

int main()
{
    test_lconv();
    test_LC();
    test_setlocale();
    test_localeconv();
    return 0;
}
