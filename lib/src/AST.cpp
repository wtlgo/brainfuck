#include <AST.hpp>

using namespace wtlgo::bf;

ASTBody::ASTBody(body_t&& body) : body { std::move(body) } {}
void ASTBody::compute(VM& vm) const {
    for(const auto& term : body)
        term->compute(vm);
}

ASTAdd::ASTAdd(int64_t val) : val { val } {}
void ASTAdd::compute(VM& vm) const {
    vm.tape->get()->add(val);
}

ASTMov::ASTMov(int64_t step) : step { step } {}
void ASTMov::compute(VM& vm) const {
    vm.tape->move(step);
}

ASTLoop::ASTLoop(body_t&& body) : ASTBody { std::move(body) } {}
ASTLoop::ASTLoop(const ASTBody& body) : ASTBody { body } {}
void ASTLoop::compute(VM& vm) const {
    while(vm.tape->get()->get()) {
        ASTBody::compute(vm);
    }
}

void ASTPrint::compute(VM& vm) const {
    vm.out.put(static_cast<char>(vm.tape->get()->get()));
}

void ASTRead::compute(VM& vm) const {
    vm.tape->get()->get() = vm.in.get();
}
