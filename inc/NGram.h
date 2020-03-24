#ifndef __NGRAM__NGRAM_H__
#define __NGRAM__NGRAM_H__

#include <unordered_map>
#include <set>
#include <random>

#include "NGramState.h"
#include "Gram.h"
#include "GramHasher.h"
#include "WeightedContinuations.h"

template<typename type>
struct LookUpGram{
	int *items;
	int n; 
	LookUpGram(unsigned n) : n(n){ items = new int[n]; }
};

template<typename type, size_t n>
class NGram {
    /*shorter template type names*/
    using Gram_t = Gram<type, n>;
    using NGramState_t = NGramState<type, n>;
    using WeightedContinuations_t = WeightedContinuations<type, n>;

    std::unordered_map<Gram_t, WeightedContinuations_t, GramHasher<type, n>> map;
    std::set<type> items;

    friend NGramState_t;

public:
    explicit NGram(std::vector<type> sequence) {
		static_assert( n > 1, "n must be greater than 1" );
        for (auto i = sequence.begin(); i != sequence.end() - n ; i++) {
            map[createGram(i)].countContinuation(get_refrence_to_gram_in_map(createGram(i + 1)));
        }
    }

	const std::set<type>& getItems() const {
		return items;
	}

    NGramState_t getRandomState() const  {
		static std::random_device rd;
		static std::mt19937 gen( rd() );
		std::uniform_int_distribution<std::mt19937::result_type> dist(0, map.size()-1);
		int offset = dist(gen);

        return NGramState_t(*this, (*std::next(map.begin(), offset)).first);
    }

	std::vector<NGramState_t> getState( LookUpGram<type> search) const {
		if( search.n > n ) 
			throw std::out_of_range("lookup gram has too many items");//todo: myb custom exception
		std::vector<NGramState_t> matching_states;
		for(const auto& item : map){
			bool matches = true;
			for(int i = 0; i < search.n; i++){
				if(search.items[i] != *item.first.items[i])
					matches = false;
			}
			if(matches)
				matching_states.push_back(NGramState_t(*this, item.first));
		}
		return matching_states;
	}

private:
    Gram_t createGram(const typename std::vector<type>::iterator& it) {
        Gram_t g;
        for (int i = 0; i < n; i++) {
            g.items[i] = get_pointer_to_item_in_set(*(it + i));
        }
        return g;
	}

    const type* get_pointer_to_item_in_set(type& item) {
        auto insertion_result = items.insert(item);
        return &(*insertion_result.first);
    }

	const WeightedContinuations_t getContinuationsFor(const Gram_t& g) const {
		return map.at(g);
	}

    const Gram_t& get_refrence_to_gram_in_map(Gram_t g) {
        auto insertion = map.insert(std::make_pair(g, WeightedContinuations_t()));
        return (*insertion.first).first;
    }
};

#endif
