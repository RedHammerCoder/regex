#include "../inc/ExpGraph.h"
void ExpGraph::SetLevel(int T)
{
    _level=T;
}

ExpGraph::ExpGraph(ExpType T):Type(T),Stat(NonStat)
{
    if(Type==BUCKET)
    {
        this->nodetype =Bucket;
    }
    if(Type==FELLOWCTRL)
    {
        this->nodetype=Divide;
        this->node.Div.List.fill(nullptr);
    }


}

void ExpGraph::SetStat(NodeStat stat_)
{
    this->Stat=stat_;
}
NodeStat ExpGraph::GetStat()
{
    return this->Stat;
} 