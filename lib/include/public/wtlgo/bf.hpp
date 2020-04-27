#ifndef _WTLGO_BF_
#define _WTLGO_BF_

#include <memory>
#include <string>

namespace wtlgo {
namespace bf {

enum ParserOptions {
    C_STYLE_COMMENTS = 0b1
};

enum RuntimeOptions {
    NON_WRAPPING_CELLS = 0b1,
    SIGNED_CELLS       = 0b10,
    WRAPPING_TAPE      = 0b100,
    INFINITE_TAPE      = 0b1000
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
