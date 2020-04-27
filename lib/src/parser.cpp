#include <parser.hpp>

using namespace wtlgo::bf;

AST::const_ptr_t Parser::parse(it_t begin, it_t end) {
    auto res = parse_body(begin, end);
    if(!res.first || res.second != end)
        throw std::runtime_error("Parsing error: Impossible to parse.");
    return res.first;
}

#define NOTHING { nullptr, begin }

std::pair<std::shared_ptr<const ASTBody>, Parser::it_t>
Parser::parse_body(it_t begin, it_t end) {
    it_t it = begin;
    ASTBody::body_t res;

    while(it != end) {
        switch(*it) {
            case ADD:
            case SUB: {
                auto next = parse_add(it, end);
                if(!next.first) return NOTHING;

                res.push_back(next.first);
                it = next.second;
                break;
            }

            case MVL:
            case MVR: {
                auto next = parse_mov(it, end);
                if(!next.first) return NOTHING;

                res.push_back(next.first);
                it = next.second;
                break;
            }

            case REA:
            case OUT: {
                auto next = parse_io(it, end);

                res.push_back(next.first);
                it = next.second;
                break;
            }

            case LPS: {
                auto next = parse_loop(it, end);

                res.push_back(next.first);
                it = next.second;
                break;
            }

            default:
                return NOTHING;
        }
    }

    return { std::make_shared<ASTBody>(std::move(res)), it };
}

std::pair<std::shared_ptr<const ASTAdd>, Parser::it_t>
Parser::parse_add(it_t begin, it_t end) {
    it_t it = begin;
    if(it == end || (*it != ADD && *it != SUB)) return NOTHING;

    const int8_t inc = [type = *it] {
        if(type == ADD) return 1;
        else return -1;
    }();

    int64_t val = 0;
    while(it != end && *it == *begin) {
        val += inc;
        ++it;
    }

    return { std::make_shared<ASTAdd>(val), it };
}

std::pair<std::shared_ptr<const ASTMov>, Parser::it_t>
Parser::parse_mov(it_t begin, it_t end) {
    it_t it = begin;
    if(it == end || (*it != MVL && *it != MVR)) return NOTHING;

    const int8_t inc = [type = *it] {
        if(type == MVR) return 1;
        else return -1;
    }();

    int64_t dir = 0;
    while(it != end && *it == *begin) {
        dir += inc;
        ++it;
    }

    return { std::make_shared<ASTMov>(dir), it };
}

std::pair<std::shared_ptr<const AST>, Parser::it_t>
Parser::parse_io(it_t begin, it_t end) {
    it_t it = begin;
    if(it == end || (*it != REA && *it != OUT)) return NOTHING;

    if(*it == REA) return { std::make_shared<ASTRead>(), std::next(it) };
    return { std::make_shared<ASTPrint>(), std::next(it) };
}

std::pair<std::shared_ptr<const ASTLoop>, Parser::it_t>
Parser::parse_loop(it_t begin, it_t end) {
    it_t it = begin;
    if(it == end || *it != LPS) return NOTHING;

    ++it;

    it_t loop_end = std::find_if(it, end,
    [bcount = 1](token_t token) mutable {
        if(token == LPS) ++bcount;
        else if(token == LPE) --bcount;
        return bcount == 0;
    });
    if(loop_end == end) return NOTHING;

    auto body = parse_body(it, loop_end);
    if(!body.first) return NOTHING;

    return { std::make_shared<ASTLoop>(*body.first), std::next(loop_end) };
}
