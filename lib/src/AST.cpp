#include <AST.hpp>

using namespace wtlgo::bf;

ASTBody::ASTBody(body_t&& body) : body { std::move(body) } {}

ASTAdd::ASTAdd(int64_t val) : val { val } {}

ASTMov::ASTMov(int64_t step) : step { step } {}

ASTLoop::ASTLoop(body_t&& body) : ASTBody { std::move(body) } {}
ASTLoop::ASTLoop(const ASTBody& body) : ASTBody { body } {}
