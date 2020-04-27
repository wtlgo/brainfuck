#ifndef _CONFIG_
#define _CONFIG_

#include <map>
#include <string>

class Config : public std::map<std::string, std::string> {
public:
    Config(int argv, const char* argc[]);
    
    bool has_param(const std::string&) const;
    bool has_param_val(const std::string&) const;
};

#endif
