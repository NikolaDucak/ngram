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
        for (int i = 0; i < n; i++) {
            if (left.items[i] != right.items[i])
                return false;
        }
        return true;
    }
};
#endif
