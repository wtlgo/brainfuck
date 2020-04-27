#include <limits>
#include <stdexcept>
#include <cell.hpp>

/* Default Cell */
int64_t Cell::max() const { return std::numeric_limits<uint8_t>::max(); }
int64_t Cell::min() const { return std::numeric_limits<uint8_t>::min(); }

int64_t Cell::get() const {
    return val;
}

void Cell::add(int64_t to) {
    val += to;
    while(to < min()) val += max() - min() + 1;
    val = (val - min()) % (max() - min() + 1) + min();
}

/* Non Wrapping Cell */
void NonWrappingCell::add(int64_t to) {
    val += to;
    if(to < min() || to > max())
        throw std::runtime_error("Runtime Error: Cell overflow.");
}

/* Signed Cell */
int64_t SignedCell::max() const { return std::numeric_limits<int8_t>::max(); }
int64_t SignedCell::min() const { return std::numeric_limits<int8_t>::min(); }

/* Non Wrapping Signed Cell */
int64_t NonWrappingSignedCell::max() const { return std::numeric_limits<int8_t>::max(); }
int64_t NonWrappingSignedCell::min() const { return std::numeric_limits<int8_t>::min(); }
