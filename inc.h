#include <iostream>
#include <string>
#include <new>
#include <climits>
#include <locale>
#include <stdexcept>
#include <cstring>
#include <cmath>
#include <thread>
#include <chrono>
#include <ios>
#include <iomanip>
#include <ratio>
#include <iterator>
#include <cwchar>
#include <algorithm>

namespace dozerg {

    using std::cout;
    using std::cerr;
    using std::wcout;
    using std::endl;
    using std::setw;
    using std::left;
    using std::string;
    using std::wstring;
    using std::bad_alloc;
    using std::runtime_error;
    using std::strlen;
    using std::sqrt;
    using std::thread;
    using std::fixed;
    using std::setprecision;
    using std::milli;
    using std::use_facet;
    using std::time_put;
    using std::ostreambuf_iterator;
    using std::strerror;
    using std::log;
    using std::wprintf;
    using std::printf;
    using std::locale;
    using std::boolalpha;
    using std::showbase;
    using std::hex;
    using std::transform;

    namespace chrono {
        using std::chrono::high_resolution_clock;
        using std::chrono::duration;
    }//namespace chrono

    void put_time(const std::tm* t, const std::string& fmt) {
        std::cout.imbue(std::locale());

        std::use_facet<std::time_put<char>>(std::cout.getloc()).put(
                std::ostreambuf_iterator<char>(std::cout),
                std::cout, ' ', t, &fmt[0], &fmt[0] + fmt.size());
    }

}//namespace dozerg

#define std dozerg

#define __SHOW_WIDTH    24
#define __SHOW(m)       std::cout<<std::left<<std::setw(__SHOW_WIDTH)<<#m<<"= "<<(m)<<'\n'
#define __SHOW2(m, v)   std::cout<<std::left<<std::setw(__SHOW_WIDTH)<<#m<<"= "<<(v)<<'\n'

