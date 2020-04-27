#include <regex>
#include <algorithm>

#include <tokenizer.hpp>
#include <bf.hpp>

std::list<token_t> Tokenizer::tokenize(std::string::const_iterator begin, std::string::const_iterator end, uint64_t opt) {
    const std::regex regex_tokenizer {
        [opt] {
            if(opt & wtlgo::bf::C_STYLE_COMMENTS)
                return std::regex { R"(\+|-|>|<|\.|,|\[|\]|\/\/.+?(?:\n|$)|\/\*(.|\n)+?\*\/)", std::regex::ECMAScript };
            else
                return std::regex { R"(\+|-|>|<|\.|,|\[|\])" };
        }()
    };

    std::list<token_t> res;
    std::transform(
        std::sregex_token_iterator { begin, end, regex_tokenizer },
        std::sregex_token_iterator {},
        std::back_inserter(res),
        [](const std::string& token) {
            return static_cast<token_t>(token.front());
        }
    );

    res.erase(std::remove(res.begin(), res.end(), token_t::COM), res.end());

    return res;
}
