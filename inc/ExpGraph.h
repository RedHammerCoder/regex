#ifndef __EXPGRAPH__
#define __EXPGRAPH__
#include <vector>
#include <functional>
#include <set>
#include <assert.h>
#include <array>
class ExpGraph;
#define LeftMove(x)  0x00000001<<(x)
enum ExpType
{
    CHR = LeftMove(0),         // 通用字符串
    SPEC_SYM = LeftMove(1),    // 转义字符串
    FELLOWCTRL = LeftMove(2),  // 流控制 |
    EMPTY = LeftMove(3),       // 空白
    BUCKET = LeftMove(4), // 不一定有用 先行占位
    Dot = LeftMove(5),         //'.' 符号 用于通配         一个字符
    SCOPE = LeftMove(6),       // 范围 用于添加范围输入
};
enum NodeStat
{
    NonStat = 0,
    TERMINAL, //终结符
    Normal,
};
enum NodeType
{
    Bucket,
    Divide,
    UnDef,
};

struct NodeBucket
{   
    ExpGraph* SubnodeHead;
    ExpGraph* tail;
};

struct NodeDivide
{
    std::array<ExpGraph * , 8> List;
};

// 状态 用于标识是否是终结点
union NODE
    {
        NodeDivide Div;
        NodeBucket Bucket;
    };

class ExpGraph
{
    friend class ExpGraph;

public:
    NodeStat Stat;
    
    ExpGraph * Next; //
    ExpGraph * Perfix;
    std::set<char> PerfixSym; //前置node 收到内部符号则跳转到本地
    
    NodeType nodetype;
    
    int _level; // 用于子表达式的分级支持
    ExpType Type;
    char Content;

    int32_t LoopStat;
    int mini ; //范围控制mini
    int max;// 范围控制max

public:
    NODE node;
    ExpGraph * Parent;//用于指向父结点
     void AddNext(ExpGraph * next)
    {
        next->Perfix=this;
        Next=next;
        
    }
    // Div结点添加
    void AddDivNext(ExpGraph* subnext)
    {
        assert(this->nodetype==Divide);
        node.Div.List[node.Div.List.size()]=subnext;
        subnext->AddNext(this);

    }
    // Bucket 结点添加Node
    void AddBucketNext(ExpGraph * b_n)
    {
        assert(this->nodetype==Bucket);
        if(node.Bucket.SubnodeHead==nullptr){
            node.Bucket.SubnodeHead=b_n;
        }else
        {
            node.Bucket.tail->AddNext(b_n);
        }
        node.Bucket.tail=b_n;


    }
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
    void SetChr(char T){
        this->Content=T;
    }
    NodeStat GetStat();
    ExpType  GetType()
    {
        return this->Type;
    }

    void AddPerfix(ExpGraph *perfix)
    {
        Perfix=perfix;
    }
};

#endif