#include <cstdio.hh>
#include "inc.h"

void test_size_t()
{
    const std::size_t N = 100;
    int* a = new int[N];

    for (std::size_t n = 0; n < N; ++n)
        a[n] = n;

    delete[] a;
}

void test_NULL()
{
    class S;
    int* p = NULL;
    int* p2 = static_cast<std::nullptr_t>(NULL);
    void(*f)(int) = NULL;
    int S::*mp = NULL;
    void(S::*mfp)(int) = NULL;
}

int main()
{
    test_size_t();
    test_NULL();
    return 0;
}
