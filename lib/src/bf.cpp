#include <memory>

#include <bf.hpp>
#include <tokenizer.hpp>
#include <parser.hpp>
#include <VM.hpp>
#include <AST.hpp>

wtlgo::bf::Interpreter::Interpreter(const std::string& input, uint64_t opt) : opt { opt } {
    auto tokens = Tokenizer::tokenize(input.cbegin(), input.cend(), opt);
    this->ast = Parser::parse(tokens.cbegin(), tokens.cend());
}

void wtlgo::bf::Interpreter::compute(std::ostream& out, std::istream& input) const {
    VM vm { opt, out, input };
    ast->compute(vm);
}
