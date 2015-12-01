#ifndef CSETJMP_DOZERG_20150817
#define CSETJMP_DOZERG_20150817 1

#include <setjmp.h>     //setjmp

namespace dozerg {

    typedef ::jmp_buf jmp_buf;
    using ::longjmp;

}//namespace dozerg
#endif
