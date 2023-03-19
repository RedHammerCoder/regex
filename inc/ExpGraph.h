#ifndef __EXPGRAPH__
#define __EXPGRAPH__
#include <vector>
#include <functional>
#include <set>
class ExpGraph;
#define LeftMove(x)  0x00000001<<(x)
enum ExpType
{
    CHR = LeftMove(0),         // 通用字符串
    SPEC_SYM = LeftMove(1),    // 转义字符串
    FELLOWCTRL = LeftMove(2),  // 流控制
    EMPTY = LeftMove(3),       // 空白
    SUB_EXPRESS = LeftMove(4), // 不一定有用 先行占位
    HEAD = LeftMove(5),        // 头结点
    Dot = LeftMove(6),         //'.' 符号 用于通配         一个字符
    SCOPE = LeftMove(7),       // 范围 用于添加范围输入
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
    std::set<char> PerfixSym; //前置node 收到内部符号则跳转到本地
    std::vector<ExpGraph*> SubNode;


    int _level; // 用于子表达式的分级支持
    ExpType Type;
    char first;

public:
    ExpGraph(ExpType);
    ~ExpGraph();
    void AddPerfix(char T)
    {
        PerfixSym.insert(T);
    }

    bool HavePerfixSym(char T)
    {
        auto ishave = this->PerfixSym.find(T);
        ishave == this->PerfixSym.end() ? false : true;
    }

    void SetStat(NodeStat);
    void SetLevel(int);
    void SetChr(char T);
    NodeStat GetStat();
    ExpType  GetType();
    {

    }



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