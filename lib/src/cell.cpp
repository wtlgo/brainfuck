#include <limits>
#include <stdexcept>

#include <bf.hpp>
#include <cell.hpp>

/* Default Cell */
int64_t Cell::max() const { return std::numeric_limits<uint8_t>::max(); }
int64_t Cell::min() const { return std::numeric_limits<uint8_t>::min(); }

int64_t& Cell::get() {
    return val;
}

void Cell::add(int64_t to) {
    val += to;
    while(val < min()) val += max() - min() + 1;
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

/* Cell Generator */
CellGenerator::CellGenerator(int64_t opt) : opt { opt } {}

std::unique_ptr<Cell> CellGenerator::operator()() const {
    using namespace wtlgo::bf;
    uint8_t ver = (opt & NON_WRAPPING_CELLS) * 2 + (opt & SIGNED_CELLS);
    switch (ver) {
        case true  * 2 + true : return std::make_unique<NonWrappingSignedCell>();
        case false * 2 + true : return std::make_unique<SignedCell>();
        case true  * 2 + false: return std::make_unique<NonWrappingCell>();
        case false * 2 + false: return std::make_unique<Cell>();

        default: throw std::runtime_error("Runtime Error: Unknown cell type.");
    }

    return nullptr;
}
