#include <VM.hpp>

VM::VM(int64_t opt, std::ostream& out, std::istream& in) :
    tape { TapeGenerator::generate(opt) }, out { out }, in { in } {}
