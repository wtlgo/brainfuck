#include <algorithm>
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
