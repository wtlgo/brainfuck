#include <config.hpp>

Config::Config(int argv, const char* argc[]) {
    operator[]("program") = argc[0];

    for(int i = 1; i < argv; ++i) {
        if(argc[i][0] == '-') {
            std::string key = argc[i];
            if(argv != i + 1 && argc[i + 1][0] != '-') {
                operator[](key) = argc[++i];
            }
            else {
                operator[](key) = "";
            }
        }
    }
}

bool Config::has_param(const std::string& param) const {
    return find(param) != end();
}

bool Config::has_param_val(const std::string& param) const {
    return has_param(param) && !at(param).empty();
}
