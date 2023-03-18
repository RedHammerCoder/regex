#include "../inc/ExpGraph.h"
void ExpGraph::SetLevel(int T)
{
    _level=T;
}

ExpGraph::ExpGraph(ExpType T):Type(T),Stat(NonStat)
{

}

void ExpGraph::SetStat(NodeStat stat_)
{
    this->Stat=stat_;
}
NodeStat ExpGraph::GetStat()
{
    return this->Stat;
}