#ifndef __NGRAM__NGRAM_STATE_H__
#define __NGRAM__NGRAM_STATE_H__

#include <cstddef>
#include <iostream>

#include "Gram.h"
#include "NoGramContinuationException.h"

template<typename type, size_t n>
class NGram;
template<typename type, size_t n>
class NGramState {
    const NGram<type, n>& parent;
    const Gram<type, n>* current_gram_ptr;

public:
    NGramState(const NGram<type, n>& parent, const Gram<type, n>& gram)
            : parent(parent), current_gram_ptr(&gram) {}

    NGramState(const NGramState& rh)
            : parent(rh.parent), current_gram_ptr(rh.current_gram_ptr) {}

	NGramState& operator=(const NGramState& r) {
        new(this) NGramState(r);
        return *this;
    }

    bool advance() {
		try{
			auto next = &parent.getContinuationsFor(*current_gram_ptr).getWeightedContinuationGram();
			std::cout << next << ' ';
			if((next) == decltype(next)(0x1))
				std::cout << "gotem";
			current_gram_ptr = next;
			return true;
		}catch(NoGramContinuationException){
			return false;
		}
    }

    const type& operator [] (size_t index) {
        return *(current_gram_ptr->items[index]);
    }

    friend std::ostream& operator << (std::ostream& os, const NGramState& state) {
        os << *(state.current_gram_ptr);
        return os;
    }
};

#endif
