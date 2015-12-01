#ifndef CSTDDEF_DOZERG_20150817
#define CSTDDEF_DOZERG_20150817 1

namespace dozerg {

#ifndef NULL
#   define NULL    nullptr
#endif

#define offsetof(type, member)  (size_t(&(((type *)0)->member)))

    typedef unsigned long size_t;

    typedef decltype(nullptr) nullptr_t;

    typedef long ptrdiff_t;

    struct max_align_t {
        long long ll_;
        long double ld_;
    };

}//namespace dozerg

#endif
