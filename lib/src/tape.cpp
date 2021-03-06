#include <algorithm>

#include <bf.hpp>
#include <tape.hpp>

/* Basic Tape */
BasicTape::BasicTape(int64_t opt) : opt { opt }, generator { opt } {}

/* Standard Tape */
StandardTape::StandardTape(int64_t opt) : BasicTape { opt } {
    std::generate_n(std::back_inserter(tape), 3000, generator);
    it = tape.begin();
} 

std::unique_ptr<Cell>& StandardTape::get() const {
    return *it;
}

void StandardTape::move(int64_t dir) {
    const size_t dist = std::distance(tape.begin(), it);
    if((dir < 0 && -1 * dir > dist) ||
       (dir > 0 && tape.size() - dir < dist))
       throw std::runtime_error("Runtime Error: Out of bounds.");
    
    it += dir;
}

/* Wrapping Tape */
WrappingTape::WrappingTape(int64_t opt) : StandardTape { opt } {}

void WrappingTape::move(int64_t dir) {
    int64_t dist = std::distance(tape.begin(), it) + dir;
    while(dir < 0)
        dist += tape.size();
    dist %= tape.size();
    
    it = tape.begin() + dist;
}

/* Infinite Tape */
InfiniteTape::InfiniteTape(int64_t opt) : BasicTape { opt } {
    tape.push_back(generator());
    it = tape.begin();
}

std::unique_ptr<Cell>& InfiniteTape::get() const {
    return *it;
}

void InfiniteTape::move(int64_t dir) {
    if(dir > 0) {
        while(dir--) {
            ++it;
            if(it == tape.end()) {
                tape.push_back(generator());
            }
        }
    }
    else if(dir < 0) {
        while(dir++) {
            --it;
            if(it == tape.begin() && dir != 0) {
                throw std::runtime_error("Runtime Error: Out of bounds.");
            }
        }
    }
}

/* Infinite Wrapping Tape */
InfiniteWrappingTape::InfiniteWrappingTape(int64_t opt) : InfiniteTape { opt } {}

void InfiniteWrappingTape::move(int64_t dir) {
    if(dir > 0) {
        while(dir--) {
            ++it;
            if(it == tape.end()) {
                tape.push_back(generator());
            }
        }
    }
    else if(dir < 0) {
        while(dir++) {
            --it;
            if(it == tape.begin()) {
                tape.push_front(generator());
            }
        }
    }
}

/* Tape Generator */
std::unique_ptr<BasicTape> TapeGenerator::generate(int64_t opt) {
    using namespace wtlgo::bf;
    uint8_t var = (opt & WRAPPING_TAPE) * 2 + (opt & INFINITE_TAPE);
    switch (var) {
        case true  * 2 + true : return std::make_unique<InfiniteWrappingTape>(opt);
        case true  * 2 + false: return std::make_unique<WrappingTape>(opt);
        case false * 2 + true : return std::make_unique<InfiniteTape>(opt);
        case false * 2 + false: return std::make_unique<StandardTape>(opt);
    
        default: throw std::runtime_error("Runtime Error: Unknown tape type");
    }

    return nullptr; 
}
