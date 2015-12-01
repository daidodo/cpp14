#include <ctime.hh>
#include "inc.h"

// the function f() does some time-consuming work
void f()
{
    volatile double d = 0;
    for(int n=0; n<10000; ++n)
        for(int m=0; m<10000; ++m)
            d += d*n*m;
}

void test_clock()
{
    std::clock_t c_start = std::clock();
    auto t_start = std::chrono::high_resolution_clock::now();
    std::thread t1(f);
    std::thread t2(f); // f() is called on two threads
    t1.join();
    t2.join();
    std::clock_t c_end = std::clock();
    auto t_end = std::chrono::high_resolution_clock::now();

    std::cout << std::fixed << std::setprecision(2) << "CPU time used: "
        << 1000.0 * (c_end-c_start) / CLOCKS_PER_SEC << " ms\n"
        << "Wall clock time passed: "
        << std::chrono::duration<double, std::milli>(t_end-t_start).count()
        << " ms\n";
}

void test_time()
{
    std::time_t result = std::time(nullptr);
    std::cout << std::asctime(std::localtime(&result))
        << result << " seconds since the Epoch\n";
}

void test_asctime()
{
    std::time_t result = std::time(NULL);
        std::cout << std::asctime(std::localtime(&result));
}

void test_localtime()
{
    std::time_t t = std::time(nullptr);
    std::cout << "UTC:   "; std::put_time(std::gmtime(&t), "%c %Z"); std::cout << '\n';
    std::cout << "local: "; std::put_time(std::localtime(&t), "%c %Z"); std::cout << '\n';
}

void test_difftime()
{
    std::time_t start = std::time(NULL);
    volatile double d;

    // some time-consuming operation
    for (int n=0; n<10000; ++n) {
        for (int m=0; m<10000; ++m) {
            d += d*n*m;
        }
    }

    std::cout << "Wall time passed: "
        << std::difftime(std::time(NULL), start) << " s.\n";
}

void test_ctime()
{
    std::time_t result = std::time(NULL);
    std::cout << std::ctime(&result);
}

void test_strftime()
{
    std::locale::global(std::locale("ja_JP.utf8"));
    std::time_t t = std::time(NULL);
    char mbstr[100];
    if (std::strftime(mbstr, sizeof(mbstr), "%A %c", std::localtime(&t))) {
        std::cout << mbstr << '\n';
    }
}

void test_wcsftime()
{
    std::locale::global(std::locale("ja_JP.utf8"));
    std::time_t t = std::time(NULL);
    wchar_t wstr[100];
    if(std::wcsftime(wstr, 100, L"%A %c", std::localtime(&t))) {
        std::wcout << wstr << '\n';
    }
}

void test_mktime()
{
    std::time_t t = std::time(NULL);
    std::tm tm = *std::localtime(&t);
    std::cout << "Today is           "; std::put_time(&tm, "%c %Z"); std::cout <<'\n';
    tm.tm_mon -= 100;  // tm_mon is now outside its normal range
    std::mktime(&tm);
    std::cout << "100 months ago was "; std::put_time(&tm, "%c %Z"); std::cout << '\n';
}

int main()
{
    test_clock();
    test_time();
    test_asctime();
    test_localtime();
    test_difftime();
    test_ctime();
    test_strftime();
    test_wcsftime();
    test_mktime();
    return 0;
}
