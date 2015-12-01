#ifndef CASSERT_DOZERG_20150818
#define CASSERT_DOZERG_20150818 1

#ifdef NDEBUG

#   define assert(expr)     ((void)0)

#else

#   define assert(expr)     do{ \
    if(expr)    \
        break;  \
    std::cerr<<__FILE__<<':'<<__LINE__<<": Assertion '"<< #expr <<"' failed in "<<__PRETTY_FUNCTION__<<'\n';    \
}while(0)

#endif

#endif
