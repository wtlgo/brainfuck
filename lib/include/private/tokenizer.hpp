#ifndef _TOKENIZER_
#define _TOKENIZER_

#include <list>
#include <string>

enum token_t {
    ADD = '+', SUB = '-', 
    MVL = '<', MVR = '>', 
    LPS = '[', LPE = ']', 
    REA = ',', OUT = '.',
    COM = '/'
};

struct Tokenizer {
    typedef std::list<token_t> token_list_t;
    static token_list_t tokenize(std::string::const_iterator begin, std::string::const_iterator end, uint64_t opt = 0);
};

#endif
