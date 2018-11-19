#include <iostream>
#include <fstream>
#include <random>

#include "../inc/FrequencyList.cpp"


bool notAccepted(int c){
    
    return (c == ' ' || c == '\t' || c == '\n' || ispunct(c) || c =='\'' || c== '"'||  !isascii(c));
}


TokenSet* tokenize_data(std::ifstream& in){
    TokenSet* tokens = new TokenSet();
    int c;
    int token_counter = 0;
    tokens->tokens.push_back("");
    bool added_to_token = false;

    while( (c=in.get()) != EOF){
        c= tolower(c);
        if( notAccepted(c) ){ 
            if(added_to_token){
                token_counter++;
                tokens->tokens.push_back("");
                added_to_token= false;
            }
        } else {
            tokens->tokens[token_counter].push_back(c);
            added_to_token = true;
        }
        if (token_counter > 100000) break;

    }

    return tokens;

}

int main(){
    std::ifstream in;

    in.open("text.txt");

    if(!in.is_open()){
        puts("error opening data file");
        return -1;
    }

    TokenSet* words = tokenize_data(in);

    // n gram;
    FrequencyList f2;
    std::string key;

    for(int i=0; i< words->tokens.size() -1 ; i++){
        TokenSet t;
        t.tokens.push_back(words->tokens[i]);
        t.tokens.push_back(words->tokens[i+1]);

        if( f2.hasWord(t) )
            f2.getFrequencyOf(t)++;
        else
            f2.add(t);
    }

    //f2.sort();

    std::string start_word = words->tokens[100];
    std::string current_word = start_word;

    TokenSet max;
    int max_index;

    int cnt = 0;
    std::cout << current_word << " ";


    //random wars
    std::random_device rd;
    std::mt19937_64 mt(rd());

    std::string result(" ");

    do{
        int max_freq = -1;
        std::vector<
                std::pair<TokenSet, int> 
                    > chosen_pairs;

        for(int i = 0; i < f2.size() ; i++){
            if( !f2.getPairAt(i).first.tokens[0].compare(current_word) ){
                chosen_pairs.push_back(f2.getPairAt(i));
            }
        }

        //get weighted random from chosen tokens;
        std::uniform_real_distribution<float> distribution(0, chosen_pairs.size());
        max_index = (int)distribution(mt);

        std::cout << "pair - "<< chosen_pairs[max_index].first.tokens[0] << " - " << chosen_pairs[max_index].first.tokens[1] << std::endl;
        current_word = chosen_pairs[max_index].first.tokens[1];
        result.append(current_word);
        result.append(" ");
        cnt++;

    }while(cnt < 30);  

    std::cout << result;
}