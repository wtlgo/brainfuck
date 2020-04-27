#ifndef _VM_
#define _VM_

#include <iostream>
#include <memory>

#include <tape.hpp>

struct VM {
    std::unique_ptr<BasicTape> tape;
    std::ostream& out;
    std::istream& in;

    VM(int64_t opt = 0, std::ostream& out = std::cout, std::istream& in = std::cin);
};

#endif
