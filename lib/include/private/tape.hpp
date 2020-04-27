#ifndef _TAPE_
#define _TAPE_

#include <cell.hpp>
#include <vector>
#include <list>

class BasicTape {
protected:
    int64_t opt;
    const CellGenerator generator;

public:
    BasicTape(int64_t opt = 0);
    virtual ~BasicTape() = default;

    virtual std::unique_ptr<Cell>& get() const = 0;
    virtual void move(int64_t) = 0;
};

class StandardTape : public BasicTape {
protected:
    std::vector<std::unique_ptr<Cell>> tape;
    std::vector<std::unique_ptr<Cell>>::iterator it;

public:
    StandardTape(int64_t opt = 0);

    virtual std::unique_ptr<Cell>& get() const;
    virtual void move(int64_t);
};

class WrappingTape : public StandardTape {
public:
    virtual void move(int64_t);
};

class InfiniteTape : public BasicTape {
protected:
    std::list<std::unique_ptr<Cell>> tape;
    std::list<std::unique_ptr<Cell>>::iterator it;

public:
    InfiniteTape(int64_t opt = 0);

    virtual std::unique_ptr<Cell>& get() const;
    virtual void move(int64_t);
};

class InfiniteWrappingTape : public InfiniteTape {
    virtual void move(int64_t);
};

#endif