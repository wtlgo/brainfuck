#include <VM.hpp>

VM::VM(uint64_t opt, std::ostream& out, std::istream& in) :
    tape { TapeGenerator::generate(opt) }, out { out }, in { in } {}
