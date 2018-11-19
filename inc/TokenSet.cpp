#ifndef _TOKENSET_H
#define _TOKENSET_H

#include <iostream>
#include <vector>


class TokenSet{

public:
    std::vector<std::string> tokens;

    bool operator == (const TokenSet& a){
        if( tokens.size() != a.tokens.size() ) return false;
        
        for(int i = 0 ; i < a.tokens.size(); i++)
            if(tokens[i] != a.tokens[i]) return false;
        
        return true;
    };

    friend std::ostream& operator << ( std::ostream& os, const TokenSet t){
        for(int i = 0; i < t.tokens.size(); i++)
            os << t.tokens[i] << " ";

        os << "\n";
        return os;
    }

};




#endif