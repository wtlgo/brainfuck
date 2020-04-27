#include <memory>

#include <bf.hpp>
#include <tokenizer.hpp>
#include <parser.hpp>
#include <AST.hpp>

wtlgo::bf::Interpreter::Interpreter(const std::string& input, uint64_t opt) {
    auto tokens = Tokenizer::tokenize(input.cbegin(), input.cend(), opt);
    this->ast = Parser::parse(tokens.cbegin(), tokens.cend());
}
