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
        for (const auto& pair : continuations) {
            probabilities.push_back(pair.second);
        }
        if (probabilities.empty()) {
            throw NoGramContinuationException("gram has no continuations ");
        }

        static std::discrete_distribution<int> dist(probabilities.begin(), probabilities.end());
        int iterator_offset = dist(engine);

        return *(
			(
				*std::next(continuations.begin(), iterator_offset)
			).first
		);
    }

    friend std::ostream& operator<<(std::ostream& os, const WeightedContinuations& a) {
        for (const auto& item : a.continuations) {
            os << *item.first << '\n';
        }
        return os;
    }
};

#endif
