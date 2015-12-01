#include <cstdlib.hh>
#include <cassert.hh>
#include <ctime.hh>
#include <clocale.hh>
#include "inc.h"

void test_NULL()
{
    struct S;
    int* p = NULL;
    int* p2 = static_cast<std::nullptr_t>(NULL);
    void(*f)(int) = NULL;
    int S::*mp = NULL;
    void(S::*mfp)(int) = NULL;
}

std::string itoa(int n, int base)
{
    std::string buf;
    std::div_t dv{}; dv.quot = n;
    do {
        dv = std::div(dv.quot, base);
        buf += "0123456789abcdef"[std::abs(dv.rem)];  // string literals are arrays
    } while(dv.quot);
    if(n<0) buf += '-';
    return {buf.rbegin(), buf.rend()};
}

void test_div()
{
    std::cout << itoa(12345, 10) << '\n'
        << itoa(-12345, 10) << '\n'
        << itoa(65535, 16) << '\n';
}

void test_size_t()
{
    const std::size_t N = 100;
    int* a = new int[N];

    for (std::size_t n = 0; n < N; ++n)
        a[n] = n;

    delete[] a;
}

void test_abs()
{
    std::cout << "abs(+3) = " << std::abs(3) << '\n'
        << "abs(-3) = " << std::abs(-3) << '\n';
}

void test_system()
{
    std::system("ls -l >test.txt");
}

void test_getenv()
{
    if(const char* env_p = std::getenv("PATH"))
        std::cout << "Your PATH is: " << env_p << '\n';
}

void test_free()
{
    int* p1 = (int*)std::malloc(10*sizeof *p1);
    std::free(p1); // every allocated pointer must be freed

    int* p2 = (int*)std::calloc(10, sizeof *p2);
    int* p3 = (int*)std::realloc(p2, 1000*sizeof *p3);
    if(p3) // p3 not null means p2 was freed by std::realloc
        std::free(p3);
    else // p3 null means p2 was not freed
        std::free(p2);
}

void test_malloc()
{
    int* p1 = (int*)std::malloc(4*sizeof(int));  // allocates enough for an array of 4 int
    int* p2 = (int*)std::malloc(sizeof(int[4])); // same, naming the type directly
    int* p3 = (int*)std::malloc(4*sizeof *p3);   // same, without repeating the type name

    if(p1) {
        for(int n=0; n<4; ++n) // populate the array
            p1[n] = n*n;
        for(int n=0; n<4; ++n) // print it back out
            std::cout << "p1[" << n << "] == " << p1[n] << '\n';
    }

    std::free(p1);
    std::free(p2);
    std::free(p3);
}

void test_calloc()
{
    int* p1 = (int*)std::calloc(4, sizeof(int)); // allocate and zero out an array of 4 int
    int* p2 = (int*)std::calloc(1, sizeof(int[4])); // same, naming the array type directly
    int* p3 = (int*)std::calloc(4, sizeof *p3);   // same, without repeating the type name

    if(p2)
        for(int n=0; n<4; ++n) // print the array
            std::cout << "p2[" << n << "] == " << p2[n] << '\n';

    std::free(p1);
    std::free(p2);
    std::free(p3);
}

class MallocDynamicBuffer
{
    char* p;
    public:
    explicit MallocDynamicBuffer(std::size_t initial = 0) : p(nullptr) {
        resize(initial);
    }
    ~MallocDynamicBuffer() { std::free(p); }
    void resize(std::size_t newSize) {
        if(newSize == 0) { // this check is not strictly needed, 
            std::free(p);  // but zero-size realloc is deprecated in C
            p = nullptr;
        } else {
            if(void* mem = std::realloc(p, newSize))
                p = static_cast<char*>(mem);
            else
                throw std::bad_alloc();
        }
    }
    char& operator[](size_t n) { return p[n]; }
    char operator[](size_t n) const { return p[n]; }
};

void test_realloc()
{
    MallocDynamicBuffer buf1(1024);
    buf1[5] = 'f';
    buf1.resize(10); // shrink
    assert(buf1[5] == 'f');
    buf1.resize(1024); // grow
    assert(buf1[5] == 'f');
}

void test_srand()
{
    std::srand(std::time(0)); //use current time as seed for random generator
    int random_variable = std::rand();
    std::cout << "Random value on [0 " << RAND_MAX << "]: " 
        << random_variable << '\n';
}

void test_rand()
{
    std::srand(std::time(0)); // use current time as seed for random generator
    int random_variable = std::rand();
    std::cout << "Random value on [0 " << RAND_MAX << "]: " 
        << random_variable << '\n';
}

void test_qsort()
{
    int a[] = {-2, 99, 0, -743, 2, INT_MIN, 4};
    constexpr std::size_t size = sizeof a / sizeof *a;

    std::qsort(a, size, sizeof *a, [](const void* a, const void* b) {
            int arg1 = *static_cast<const int*>(a);
            int arg2 = *static_cast<const int*>(b);

            if(arg1 < arg2) return -1;
            if(arg1 > arg2) return 1;
            return 0;

            // return (arg1 > arg2) - (arg1 < arg2); // possible shortcut
            // return arg1 - arg2; // erroneous shortcut (fails if INT_MIN is present)
            });

    for (int ai : a) std::cout << ai << ' ';
    std::cout<<std::endl;
}

int compare(const void *ap, const void *bp)
{
    const int *a = (int *) ap;
    const int *b = (int *) bp;
    if(*a < *b)
        return -1;
    else if(*a > *b)
        return 1;
    else
        return 0;
}

void test_bsearch()
{
    const int ARR_SIZE = 8;
    int arr[ARR_SIZE] = { 1, 2, 3, 4, 5, 6, 7, 8 };

    int key1 = 4;
    int *p1 = (int *) std::bsearch(&key1, arr, ARR_SIZE, sizeof(arr[0]), compare);
    if(p1)
        std::cout << "value " << key1 << " found at position " << (p1 - arr) << '\n';
    else
        std::cout << "value " << key1 << " not found\n";

    int key2 = 9;
    int *p2 = (int *) std::bsearch(&key2, arr, ARR_SIZE, sizeof(arr[0]), compare);
    if(p2)
        std::cout << "value " << key2 << " found at position " << (p2 - arr) << '\n';
    else
        std::cout << "value " << key2 << " not found\n";
}

void test_atoi()
{
    const char *str1 = "42";
    const char *str2 = "3.14159";
    const char *str3 = "31337 with words";
    const char *str4 = "words and 2";

    int num1 = std::atoi(str1);
    int num2 = std::atoi(str2);
    int num3 = std::atoi(str3);
    int num4 = std::atoi(str4);

    std::cout << "std::atoi(\"" << str1 << "\") is " << num1 << '\n';
    std::cout << "std::atoi(\"" << str2 << "\") is " << num2 << '\n';
    std::cout << "std::atoi(\"" << str3 << "\") is " << num3 << '\n';
    std::cout << "std::atoi(\"" << str4 << "\") is " << num4 << '\n';
}

void test_strtol()
{
    const char* p = "10 200000000000000000000000000000 30 -40";
    char *end;
    std::cout << "Parsing '" << p << "':\n";
    for (long i = std::strtol(p, &end, 10);
            p != end;
            i = std::strtol(p, &end, 10))
    {
        std::cout << "'" << std::string(p, end-p) << "' -> ";
        p = end;
        if (errno == ERANGE){
            std::cout << "range error, got ";
            errno = 0;
        }
        std::cout << i << '\n';
    }
}

void test_strtoul()
{
    const char* p = "10 200000000000000000000000000000 30 40";
    char *end;
    std::cout << "Parsing '" << p << "':\n";
    for (unsigned long i = std::strtoul(p, &end, 10);
            p != end;
            i = std::strtoul(p, &end, 10))
    {
        std::cout << "'" << std::string(p, end-p) << "' -> ";
        p = end;
        if (errno == ERANGE){
            std::cout << "range error, got ";
            errno = 0;
        }
        std::cout << i << '\n';
    }
}

void test_atof()
{
    std::cout << std::atof("0.0000000123") << "\n"
        << std::atof("0.012") << "\n"
        << std::atof("15e16") << "\n"
        << std::atof("-0x1afp-2") << "\n"
        << std::atof("inF") << "\n"
        << std::atof("Nan") << "\n";
}

void test_strtof()
{
    const char* p = "111.11 -2.22 0X1.BC70A3D70A3D7P+6  1.18973e+4932zzz";
    char* end;
    std::cout << "Parsing \"" << p << "\":\n";
    for (double f = std::strtod(p, &end); p != end; f = std::strtod(p, &end))
    {
        std::cout << "'" << std::string(p, end-p) << "' -> ";
        p = end;
        if (errno == ERANGE){
            std::cout << "range error, got ";
            errno = 0;
        }
        std::cout << f << '\n';
    }
}

// the number of characters in a multibyte string is the sum of mblen()'s
// note: the simpler approach is std::mbstowcs(NULL, s.c_str(), s.size())
std::size_t strlen_mb(const std::string& s)
{
    std::size_t result = 0;
    const char* ptr = s.data();
    const char* end = ptr + s.size();
    std::mblen(NULL, 0); // reset the conversion state
    while (ptr < end) {
        int next = std::mblen(ptr, end-ptr);
        if (next == -1) {
            throw std::runtime_error("strlen_mb(): conversion error");
        }
        ptr += next;
        ++result;
    }
    return result;
}

void test_mblen()
{
    // allow mblen() to work with UTF-8 multibyte encoding
    std::setlocale(LC_ALL, "en_US.utf8");
    // UTF-8 narrow multibyte encoding
    std::string str = u8"z\u00df\u6c34\U0001d10b";
    // or "\x7a\xc3\x9f\xe6\xb0\xb4\xf0\x9d\x84\x8b";
    std::cout << str << " is " << str.size() << " bytes, but only "
        << strlen_mb(str) << " characters\n";
}

int print_mb(const char* ptr)
{
    std::mbtowc(NULL, 0, 0); // reset the conversion state
    const char* end = ptr + std::strlen(ptr);
    int ret;
    for (wchar_t wc; (ret = std::mbtowc(&wc, ptr, end-ptr)) > 0; ptr+=ret) {
        std::wcout << wc;
    }
    std::wcout << '\n';
    return ret;
}

void test_mbtowc()
{
    std::setlocale(LC_ALL, "en_US.utf8");
    // UTF-8 narrow multibyte encoding
    const char* str = u8"z\u00df\u6c34\U0001d10b";
    // or "\x7a\xc3\x9f\xe6\xb0\xb4\xf0\x9d\x84\x8b";
    print_mb(str);
}

void print_wide(const std::wstring& wstr)
{
    bool shifts = std::wctomb(NULL, 0); // reset the conversion state
    std::cout<<"MB_CUR_MAX is "<<MB_CUR_MAX<<std::endl;
    std::cout << "shift sequences " << (shifts ? "are" : "not" ) << " used\n";
    for (wchar_t wc : wstr) {
        std::string mb(MB_CUR_MAX, '\0');
        int ret = std::wctomb(&mb[0], wc);
        std::cout << "multibyte char " << mb << " is " << ret << " bytes\n";
    }
}

void test_wctomb()
{
    std::setlocale(LC_ALL, "en_US.utf8");
    // UTF-8 narrow multibyte encoding
    std::wstring wstr = L"z\u00df\u6c34\U0001d10b";
    print_wide(wstr);
}

void test_mbstowcs()
{
    std::setlocale(LC_ALL, "en_US.utf8");
    std::wcout.imbue(std::locale("en_US.utf8"));
    const char* mbstr = u8"z\u00df\u6c34\U0001f34c";
    // or "\x7a\xc3\x9f\xe6\xb0\xb4\xf0\x9f\x8d\x8c";
    wchar_t wstr[5];
    std::mbstowcs(wstr, mbstr, 5);
    std::wcout << "wide string: " << wstr << '\n';
}

void test_wcstombs()
{
    std::setlocale(LC_ALL, "en_US.utf8");
    // UTF-8 narrow multibyte encoding
    const wchar_t* wstr = L"z\u00df\u6c34\U0001d10b";
    char mbstr[11];
    std::wcstombs(mbstr, wstr, 11);
    std::cout << "multibyte string: " << mbstr << '\n';
}

int main()
{
    test_NULL();
    test_div();
    test_size_t();
    test_abs();
    test_system();
    test_getenv();
    test_free();
    test_malloc();
    test_calloc();
    test_realloc();
    test_srand();
    test_rand();
    test_qsort();
    test_bsearch();
    test_atoi();
    test_strtol();
    test_strtoul();
    test_atof();
    test_strtof();
    test_mblen();
    test_mbtowc();
    test_wctomb();
    test_mbstowcs();
    test_wcstombs();
    return 0;
}
