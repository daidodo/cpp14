#ifndef CTIME_DOZERG_20150818
#define CTIME_DOZERG_20150818   1

#include "cstddef.hh"   //NULL, size_t
#include <time.h>       //CLOCKS_PER_SEC
#include <iterator>
#include <locale>
#include <ios>

namespace dozerg {

    using ::clock_t;
    using ::time_t;
    using ::tm;
    using ::clock;
    using ::time;
    using ::asctime;
    using ::localtime;
    using ::gmtime;
    using ::difftime;
    using ::ctime;
    using ::strftime;
    using ::wcsftime;
    using ::mktime;

}//namespace dozerg

#endif
