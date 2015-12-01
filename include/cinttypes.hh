#ifndef CINTTYPES_DOZERG_20150818
#define CINTTYPES_DOZERG_20150818

#include "cstdint.hh"
#include "cstdlib.hh"   //div, abs

#include <inttypes.h>   //for macros like PRI*** and SCN***

namespace dozerg {

    struct imaxdiv_t {
        intmax_t quot, rem;
    };

    //imaxdiv_t div(intmax_t x, intmax_t y);
    inline imaxdiv_t imaxdiv(intmax_t x, intmax_t y) {
        return imaxdiv_t{x / y, x % y};
    }

    //intmax_t abs(intmax_t x);
    inline intmax_t imaxabs(intmax_t x){return abs(x);}

    using ::strtoimax;
    using ::strtoumax;
    using ::wcstoimax;
    using ::wcstoumax;

}//namespace dozerg

#endif
