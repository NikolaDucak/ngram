#ifndef __NGRAM__GRAM_H__
#define __NGRAM__GRAM_H__

#include <array>

template<typename type, size_t n>
struct Gram {
    std::array<const type*, n> items;

	const type* operator[](int i){
		return items[i];
	}

    friend std::ostream& operator << (std::ostream& os, const Gram& gram) {
        for (const auto& item_ptr : gram.items) {
            os << *item_ptr;
        }
        return os;
    }

    friend bool operator==(const Gram& left, const Gram& right) {
        return left.items == right.items;
    }
};
#endif
