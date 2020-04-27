#ifndef _AST_
#define _AST_

#include <memory>
#include <list>

#include <VM.hpp>

namespace wtlgo {
namespace bf {

struct AST {
    typedef std::shared_ptr<AST> ptr_t;
    typedef std::shared_ptr<const AST> const_ptr_t;

    virtual ~AST() = default;
    virtual void compute(VM&) const = 0;
};

struct ASTBody : public AST {
    typedef std::shared_ptr<ASTBody> ptr_t;
    typedef std::list<AST::const_ptr_t> body_t;
    
    const body_t body;

    ASTBody(body_t&&); 
    virtual void compute(VM&) const;
};

struct ASTAdd : public AST {
    const int64_t val;

    ASTAdd(int64_t);
    virtual void compute(VM&) const;
};

struct ASTMov : public AST {
    const int64_t step;

    ASTMov(int64_t);
    virtual void compute(VM&) const;
};

struct ASTLoop : public ASTBody {
    ASTLoop(body_t&&);
    ASTLoop(const ASTBody&);
    virtual void compute(VM&) const;
};

struct ASTPrint : public AST {
    virtual void compute(VM&) const;
};

struct ASTRead : public AST {
    virtual void compute(VM&) const;
};

}
}

#endif
