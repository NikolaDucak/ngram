#ifndef __NGRAM__WEIGHTED_CONTINUATIONS_H__

#include <map>
#include <vector>
#include <random>

#include "Gram.h"
#include "NoGramContinuationException.h"

template<typename type, size_t n>
class WeightedContinuations {
    using Gram_t = Gram<type, n>;
    std::map<const Gram_t*, size_t> continuations;

public:
    void countContinuation(const Gram_t& gram) {
        continuations[&gram]++;
    }

    const Gram_t& getWeightedContinuationGram() const {
        static std::mt19937_64 engine;
        std::vector<int> probabilities;
		
		if(continuations.size() == 0){
            throw NoGramContinuationException("gram has no continuations ");
		}else if(continuations.size() == 1){
			return *continuations.begin()->first;
		}

        for (const auto& pair : continuations) {
            probabilities.push_back(pair.second);
        }
        static std::discrete_distribution<int> dist(probabilities.begin(), probabilities.end());
        int iterator_offset = dist(engine);
		
		// selected continuation	
		auto cont_prob_pair = (std::next(continuations.begin(), iterator_offset));
        return *cont_prob_pair->first;
    }

    friend std::ostream& operator<<(std::ostream& os, const WeightedContinuations& a) {
        for (const auto& item : a.continuations) {
            os << *item.first << '\n';
        }
        return os;
    }
};

#endif
