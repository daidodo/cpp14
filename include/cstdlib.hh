#ifndef CSTDLIB_DOZERG_201500817
#define CSTDLIB_DOZERG_201500817    1

#include "cstddef.hh"   //NULL, size_t

namespace dozerg {

#define EXIT_SUCCESS    0
#define EXIT_FAILURE    1

#define MB_CUR_MAX      8

#define RAND_MAX    0x7FFFFFFF

    struct div_t { int quot, rem; };
    struct ldiv_t { long quot, rem; };
    struct lldiv_t { long long quot, rem; };

    inline div_t div(int x, int y) { return div_t{x / y, x % y}; }
    inline ldiv_t div(long x, long y) { return ldiv_t{x / y, x % y}; }
    inline lldiv_t div(long long x, long long y) { return lldiv_t{x / y, x % y}; }
    inline ldiv_t ldiv(long x, long y) { return div(x, y); }
    inline lldiv_t lldiv(long long x, long long y) { return div(x, y); }

    inline int abs(int x){return (x < 0 ? -x : x);}
    inline long abs(long x){return (x < 0 ? -x : x);}
    inline long long abs(long long x){return (x < 0 ? -x : x);}
    inline long labs(long x){return abs(x);}
    inline long long llabs(long long x){return abs(x);}

}//namespace dozerg

#include <stdlib.h>

namespace dozerg {

    inline int atexit(void (*func)(void)) noexcept { return ::atexit(func); }
    inline int at_quick_exit(void (*func)(void)) noexcept {return ::at_quick_exit(func);}
    [[noreturn]] inline void _Exit(int code) noexcept { ::_Exit(code); }
    [[noreturn]] inline void abort() noexcept { ::abort(); }
    [[noreturn]] inline void exit(int code) { ::exit(code); }
    [[noreturn]] inline void quick_exit(int code) noexcept { ::quick_exit(code); }
    using ::system;
    using ::getenv;
    using ::malloc;
    using ::calloc;
    using ::realloc;
    using ::free;
    using ::srand;
    using ::rand;
    using ::qsort;
    using ::bsearch;
    using ::atoi;
    using ::atol;
    using ::atoll;
    using ::strtol;
    using ::strtoll;
    using ::strtoul;
    using ::atof;
    using ::strtof;
    using ::strtod;
    using ::strtold;
    using ::mblen;
    using ::mbtowc;
    using ::wctomb;
    using ::mbstowcs;
    using ::wcstombs;

}//namespace dozerg

#endif

