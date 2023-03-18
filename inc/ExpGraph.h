#ifndef __EXPGRAPH__
#define __EXPGRAPH__
#include <vector>
#include <functional>

class ExpGraph;
enum ExpType
{
    CHR = 0,    // 通用字符串
    SPEC_SYM,   // 转义字符串
    FELLOWCTRL, // 流控制
    EMPTY,      // 空白
    SUB_EXPRESS,
    HEAD,
    Dot,
    SCOPE,
};

// 状态 用于标识是否是终结点
enum NodeStat
{
    NonStat = 0,
    END,
    Normal,
};

class ExpGraph
{
    friend class ExpGraph;

private:
    NodeStat Stat;
    std::vector<ExpGraph *> Next, Perfix; // 面向分支处理 ‘|’
    std::vector<char> PerfixSym;//前置node 收到内部符号则跳转到本地
    




    int _level; // 用于子表达式的分级支持
    ExpType Type;
    char first;

public:
    ExpGraph(ExpType);
    ~ExpGraph();

    void SetStat(NodeStat);
    void SetLevel(int);
    void SetChr(char T);
    NodeStat GetStat();



    void AddNext(ExpGraph *next)
    {
        Next.push_back(next);
    }
    void AddPerfix(ExpGraph *perfix)
    {
        Perfix.push_back(perfix);
    }
};

#endif