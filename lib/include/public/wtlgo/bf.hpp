#ifndef _WTLGO_BF_
#define _WTLGO_BF_

#include <memory>
#include <string>

namespace wtlgo {
namespace bf {

struct AST;
class Interpreter {
    Interpreter(const std::string&);

private:
    std::shared_ptr<const AST> ast;
};

}
}

#endif
