#ifndef _WTLGO_BF_
#define _WTLGO_BF_

#include <memory>
#include <string>

namespace wtlgo {
namespace bf {

enum ParserOptions {
    C_STYLE_COMMENTS = 0b1
};

struct AST;
class Interpreter {
    Interpreter(const std::string&, uint64_t opt = 0);

private:
    std::shared_ptr<const AST> ast;
};

}
}

#endif
