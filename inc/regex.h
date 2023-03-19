#ifndef __REGEX__
#define __REGEX__
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include "ExpGraph.h"
#include "Putility.h"

#define UDF printf("current not support")

using STRINGS = std::vector<std::string>;

enum {
    MatchError,
    MatchOk,
    ErrorCode,
    END,
};


class regex
{
private:
    bool bEOF;
    bool trans;
    ExpGraph * head;//头结点
    ExpGraph * tail;
    std::string form;
    char GetNextSym();
    int cursor;
    void Parser();
    int CurrentLevel;
    ExpGraph* GetLastNodeWithlevel(int );
    ExpGraph* ParserNextOne();
    void RollBack()
    {
        this->cursor-=1;
    }
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