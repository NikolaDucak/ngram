#ifndef __NGRAM__NO_GRAM_CONTINUATION_EXCEPTION_H__
#define __NGRAM__NO_GRAM_CONTINUATION_EXCEPTION_H__

#include <exception>
#include <string>

class NoGramContinuationException : public std::exception{
	std::string msg;
public:
	NoGramContinuationException(std::string msg) : msg(msg){}
	virtual const char * what() const throw (){ return msg.c_str(); }
};

#endif
