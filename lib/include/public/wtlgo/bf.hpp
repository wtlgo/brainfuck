#ifndef _WTLGO_BF_
#define _WTLGO_BF_

#include <memory>
#include <iostream>
#include <string>

namespace wtlgo {
namespace bf {


enum RuntimeOptions {
    NON_WRAPPING_CELLS = 0b1,
    SIGNED_CELLS       = 0b10,
    WRAPPING_TAPE      = 0b100,
    INFINITE_TAPE      = 0b1000,

    C_STYLE_COMMENTS   = 0b10000
};

struct AST;
class Interpreter {
public:
    uint64_t opt;
    Interpreter(const std::string&, uint64_t opt = 0);

    void compute(std::ostream& out = std::cout, std::istream& input = std::cin) const;

private:
    std::shared_ptr<const AST> ast;
};

}
}

#endif
