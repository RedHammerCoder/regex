#ifndef __REGEX__
#define __REGEX__
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
using STRINGS = std::vector<std::string>;

enum {
    MatchError,
    MatchOk,
    ErrorCode
};


class regex
{
private:
    /* data */
public:
    //regex 参数用于构建NFA
    regex(std::string );
    //用于根据参数转换 NFA
    bool init(std::string);
    ~regex();
    STRINGS matchs(char* );
    STRINGS matchs(std::string);  
};
int64_t ERROR;


#endif