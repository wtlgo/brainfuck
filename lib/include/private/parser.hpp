#ifndef _PARSER_
#define _PARSER_

#include <tuple>

#include <AST.hpp>
#include <tokenizer.hpp>

struct Parser {
    typedef Tokenizer::token_list_t::const_iterator it_t;
    static wtlgo::bf::AST::const_ptr_t parse(it_t begin, it_t end);

private:
    static std::pair<std::shared_ptr<const wtlgo::bf::ASTBody>, it_t> parse_body(it_t begin, it_t end);
    static std::pair<std::shared_ptr<const wtlgo::bf::ASTAdd>, it_t> parse_add(it_t begin, it_t end);
    static std::pair<std::shared_ptr<const wtlgo::bf::ASTMov>, it_t> parse_mov(it_t begin, it_t end);
    static std::pair<std::shared_ptr<const wtlgo::bf::AST>, it_t> parse_io(it_t begin, it_t end);
    static std::pair<std::shared_ptr<const wtlgo::bf::ASTLoop>, it_t> parse_loop(it_t begin, it_t end);
};

#endif