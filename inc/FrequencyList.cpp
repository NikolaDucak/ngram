#ifndef _FREQUENCYLIST_H_
#define _FREQUENCYLIST_H_

#include <iostream>
#include <vector>
#include <algorithm>

#include "TokenSet.cpp"

class FrequencyList{
    std::vector<
                std::pair <TokenSet, int> 
                 > words;

public:
    int size() { return words.size(); }

    bool hasWord(TokenSet word){
        for(int i = 0; i < words.size(); i ++)
            if(words[i].first == word) return true;

        return false;
    }

    void add(TokenSet word){
        if(!hasWord(word))
            words.push_back( std::pair<TokenSet, int>(word, 1));
    }

    int& getFrequencyOf(TokenSet word){
        for(int i = 0; i < words.size(); i ++)
            if(words[i].first == word)
                return words[i].second;
    }

    TokenSet& getTokenOf(int index){
        return words[index].first;
    }

    std::pair<TokenSet, int> getPairAt(int index){
        return words[index];
    }

    void sort(){
        std::sort(words.begin(), words.end(), 
                  []( const std::pair< TokenSet ,int > &a, const std::pair< TokenSet , int>& b) -> bool
                    { return (a.second > b.second); }
                 );
    }

};

#endif