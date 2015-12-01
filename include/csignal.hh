#ifndef CSIGNAL_DOZERG_20150817
#define CSIGNAL_DOZERG_20150817 1

#include <signal.h>     //SIG_***, SIG***, signal, raise
namespace dozerg {

    typedef int sig_atomic_t;

    using ::signal;
    using ::raise;

}//namespace dozerg

#endif
