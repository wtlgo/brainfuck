#ifndef _CELL_
#define _CELL_

#include <memory>

/*
    Default cell
    min = 0
    max = 255
    Wrapping
*/
struct Cell {
    virtual ~Cell() = default;

    virtual int64_t max() const;
    virtual int64_t min() const;

    virtual int64_t get() const;
    virtual void add(int64_t);

protected:
    int64_t val = 0;
};


/*
    Non Wrapping Cell
    min = 0
    max = 255
    Non wrapping
*/
struct NonWrappingCell : public Cell {
    virtual void add(int64_t);
};

/*
    Signed Cell
    min = -128
    max = 127
    Wrapping
*/
struct SignedCell : public Cell {
    virtual int64_t max() const;
    virtual int64_t min() const;
};

/*
    Non Wrapping Signed Cell
    min = -128
    max = 127
    Non Wrapping
*/
struct NonWrappingSignedCell : public NonWrappingCell {
    virtual int64_t max() const;
    virtual int64_t min() const;
};

/*
    Fabric method
*/
struct CellGenerator {
    int64_t opt;
    CellGenerator(int64_t opt = 0);

    std::unique_ptr<Cell> operator()() const;
};

#endif