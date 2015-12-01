#include <cstddef.hh>
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

void test_offsetof()
{
    struct S {
        char c;
        double d;
    };
    std::cout << "the first element is at offset " << offsetof(S, c) << '\n'
        << "the double is at offset " << offsetof(S, d) << '\n';
}

void test_size_t()
{
    const std::size_t N = 100;
    int* a = new int[N];

    for (std::size_t n = 0; n < N; ++n)
        a[n] = n;

    delete[] a;
}

void f(int* pi)
{
    std::cout << "Pointer to integer overload\n";
}

void f(double* pd)
{
    std::cout << "Pointer to double overload\n";
}

void f(std::nullptr_t nullp)
{
    std::cout << "null pointer overload\n";
}

int test_nullptr_t()
{
    int* pi; double* pd;

    f(pi);
    f(pd);
    f(nullptr);  // would be ambiguous without void f(nullptr_t)
    // f(NULL);  // ambiguous overload: all three functions are candidates
}

void test_ptrdiff_t()
{
    const std::size_t N = 100;
    int* a = new int[N];
    int* end = a + N;
    for (std::ptrdiff_t i = N; i > 0; --i)
        *(end - i) = i;
    delete[] a;
}

void test_max_align_t()
{
    std::cout << alignof(std::max_align_t) << '\n';
}

int main()
{
    test_NULL();
    test_offsetof();
    test_size_t();
    test_nullptr_t();
    test_ptrdiff_t();
    test_max_align_t();
    return 0;
}
