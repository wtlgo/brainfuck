#include <iostream>
#include <fstream>

#include <utility.hpp>
#include <config.hpp>

#include <wtlgo/bf.hpp>

int main(int argv, const char* argc[]) {
    using namespace wtlgo::bf;
    Config conf { argv, argc };

    if(conf.has_param("--help")) {
        std::clog << help() << std::endl;
        return 0;
    }

    uint64_t opt = 0;
    if(conf.has_param("--infinite-tape")) {
        opt |= INFINITE_TAPE;
    }
    if(conf.has_param("--wrapped-tape")) {
        opt |= WRAPPING_TAPE;
    }
    if(conf.has_param("--signed-cells")) {
        opt |= SIGNED_CELLS;
    }
    if(conf.has_param("--unwrapped-cells")) {
        opt |= NON_WRAPPING_CELLS;
    }
    if(conf.has_param("--comments")) {
        opt |= C_STYLE_COMMENTS;
    }

    try {
        Interpreter bf {
            [&conf]{
                if(conf.has_param_val("-c")) {
                    return conf["-c"];
                }
                if(conf.has_param_val("-s")) {
                    std::ifstream ifs { conf["-s"] };
                    std::string res;

                    std::copy(std::istreambuf_iterator<char> { ifs },
                              std::istreambuf_iterator<char> {},
                              std::back_inserter(res));
                    return res;
                }

                throw std::runtime_error("Error: Source is not specified.");
            }(),
            opt
        };

        if(conf.has_param_val("-i") && conf.has_param_val("-o")) {
            std::ifstream ifs { conf["-i"] };
            std::ofstream ofs { conf["-o"] };

            bf.compute(ofs, ifs);
        }
        else if(conf.has_param_val("-o")) {
            std::ofstream ofs { conf["-o"] };

            bf.compute(ofs);
        }
        else if(conf.has_param_val("-i")) {
            std::ifstream ifs { conf["-i"] };

            bf.compute(std::cout, ifs);
        }
        else {
            bf.compute();
        }
    }
    catch(const std::exception& exp) {
        std::cerr << exp.what() << std::endl;
        return 1;
    }
    
    return 0;
}
