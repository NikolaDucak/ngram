#include <iostream>
#include <algorithm>
#include <fstream>

#include "../inc/NGram.h"

void sanitize(std::string& str){
	std::transform(str.begin(), str.end(), str.begin(), 
		[](char c) { return std::tolower(c); } );
	str.erase(std::remove_if(str.begin(), str.end(), 
		[](char c) { return !std::isalnum(c); } ), str.end());
}

std::vector<std::string> file_to_vector(const char* file_path){
	std::ifstream file(file_path);
	if( !file.is_open() ){
		throw std::runtime_error("cant load file");
	}

	std::vector<std::string> sequence;
	std::string word;	
	for(; !file.eof(); file >> word ){
		sanitize(word);
		sequence.push_back(word);
	}
	return sequence;
}

int file(){
	auto s = file_to_vector("sample_text.txt");
	std::cout << "file read"<<std::endl;
	static const NGram<std::string, 3> ngram(s);
	std::cout << "Distinct items: "<< ngram.getItems().size() << '\n';
	
	static auto state = ngram.getRandomState();
	for(int i = 0; i < 30; i++){
		std::cout << state[0] << ' ' << std::flush;
		if(!state.advance())
			break;
	}
	return 0;
}

int search_test(){
	std::vector<int> s{1,2,3,1,2,4,1,2,3};
	NGram<int, 3> ngram(s);
	LookUpGram<int> lg(2);
	lg.items[0] = 1;
	lg.items[1] = 2;

	auto states =  ngram.getState(lg);

	std::cout << " states: " << states.size() << '\n';

	for(const auto& state : states){
		std::cout << state << '\n';
	}

	return 0;
}

int main(){
	file();
	return 0;
}
