#ifndef __NGRAM__GRAM_HASHER_H__
#define __NGRAM__GRAM_HASHER_H__

#include "Gram.h"

#include <cstddef>
#include <functional>

template <typename type, size_t n>
struct GramHasher {
    size_t operator()(const Gram<type, n>& g) const {
        size_t result = 0;
        for (int i = 0; i < n; i++)
            result ^= std::hash<type*> {}(const_cast<type*>(g.items[i]));
        return result;
    }
};

#endif
