#include "../inc/regex.h"
#include "../inc/ParserLog.h"
#include <iostream>
#include <random>
#include <utility>
regex::regex(std::string ss) : form(std::move(ss)), bEOF(false)
{
    std::cout << form << std::endl;
    trans = false;
    if (form.size() == 0)
    {
        return;
    }
    this->cursor = 0;
    Parser();
}

char regex::GetNextSym()
{
    if (cursor <= this->form.size())
    {
        return form[cursor++];
    }
    else
    {
        return '\0';
    }
}

ExpGraph *regex::ParserNextOne()
{
ReExec:
    ExpGraph *ret = nullptr;
    int L = this->CurrentLevel;
    char flag = GetNextSym();
    switch (flag)
    {
    case '\0':
    { // 只有取到空符号才会直接返回  实现递归
        bEOF = true;
        return new ExpGraph(Tail);
        break;
    }
    case '|':
    {
        std::cout << "print in Div Element" << std::endl;

        auto OldNode = CurNode;
        auto Oldtail = CurNode->node.Bucket.tail; // OldTail is the first  node  under the DivNode;
        ExpGraph *HEADDIV = nullptr;
        auto T = ParserNextOne();
        auto NextOldtail = Oldtail->Next;
        if (Oldtail->nodetype == Divide) // push back to oldtail
        {
            HEADDIV = Oldtail;
            Oldtail->Next = Oldtail->Next->Next;
            HEADDIV->node.Div.List[HEADDIV->node.Div.List.size() + 1] = NextOldtail;
        }
        else // create a new node and  push back the oldnode and Nextoldnode
        {
            ExpGraph *NewDivNode = new ExpGraph(FELLOWCTRL);
            HEADDIV = NewDivNode;
            NewDivNode->node.Div.List[0] = (Oldtail);
            NewDivNode->node.Div.List[1] = (NextOldtail);
            /* code */
        }
        while (false)
        {
            std::vector<ExpGraph *> tail_push;
            for (auto &Tag : HEADDIV->node.Div.List)
            {

                if (Tag == nullptr)
                {
                    if (tail_push.size() == 0)
                        break;
                    else
                    {
                        ExpGraph *N = tail_push.front();
                    }
                }
                if (Tag->Type == FELLOWCTRL)
                {
                    auto &Lists = Tag->node.Div.List;
                    for (auto T : Lists)
                    {
                        if (T != nullptr)
                        {
                            tail_push.push_back(T);
                        }
                    }
                    Tag = nullptr;
                }
            }
        }

        for (auto Tag : HEADDIV->node.Div.List)
        {
            if (Tag == nullptr)
                break;
            if (Tag->Type == BUCKET)
            {
                std::cout << "type is Bucket" << std::endl;
            }
            if (Tag->Type == FELLOWCTRL)
            {
                std::cout << "type is Div" << std::endl;
            }
            if (Tag->Type == CHR)
            {
                std::cout << "type is char val is " << Tag->Content << std::endl;
            }
        }
        std::cout << "end of DIV" << std::endl;
        return T;

#if 0
        if (CurNode->node.Bucket.tail->nodetype != Divide)
        {
            
            ExpGraph *divd = new ExpGraph(FELLOWCTRL);
            ExpGraph *lastone = CurNode->node.Bucket.tail;
            divd->Perfix = lastone->Perfix;
            CurNode->node.Bucket.tail = divd;
            divd->AddDivNext(lastone);
            ExpGraph *Tmp = ParserNextOne();
            // 保留当前的divd结点 将divd结点的下一个结点压缩到divd节点中
            // divd->AddDivNext(Tmp);
            
        }
        else
        {
            ExpGraph *lastone = CurNode->node.Bucket.tail;
            assert(lastone->nodetype == Divide);
            ExpGraph *Tmp = ParserNextOne();
            // lastone->AddDivNext(Tmp);
        }
        break;
#endif
    }

    case '\\':
    {

        char tab = GetNextSym();
        ret = new ExpGraph(CHR);
        ret->SetLevel(this->CurrentLevel);
        ret->SetChr(EscapCharMap[tab]);
        break;
    }

    case '*':
    {
        assert(CurNode->nodetype == Bucket);
        CurNode->node.Bucket.tail->Scope.mini = 0;
        CurNode->node.Bucket.tail->Scope.max = 0xffff;
        CurNode->node.Bucket.tail->Scope.LoopType = ExpGraph::LOOPTYPE::START;
        break;
    }

    case '+':
    {
        assert(CurNode->nodetype == Bucket);
        CurNode->node.Bucket.tail->Scope.mini = 1;
        CurNode->node.Bucket.tail->Scope.max = 0xffff;
        CurNode->node.Bucket.tail->Scope.LoopType = ExpGraph::LOOPTYPE::ADDS;
        break;
    }

    case '[':
        // 以“{” 开始   将直接取道“]”
        {

            auto Node = new ExpGraph(SCOPE);
            char oldt = '\0';
            do
            {

                char t = GetNextSym();

                if (t == ']')
                    break;
                if (IsChar(t))
                {
                    Node->AsciiScope.Addelement(t);
                }
                if (t == '-')
                {
                    if (oldt == '\0')
                    {
                        // BUGREPORT
                        exit(0);
                    }
                    t = GetNextSym();
                    assert(oldt < t);
                    Node->AsciiScope.AddScope(oldt, t);
                }
                oldt = t;
            } while (1);
            CurNode->AddBucketNext(Node);

            break;
        }

    case '(':
    {
        ExpGraph *Lnode = new ExpGraph(BUCKET);
        Lnode->Parent = CurNode;
        CurNode->AddBucketNext(Lnode);
        CurNode = Lnode;
        this->CurrentLevel += 1;
        break;
    }
    case '.': // 缺少非贪婪控制 需要后续修改
    {
        CurNode->node.Bucket.tail->Scope.mini = 0;
        CurNode->node.Bucket.tail->Scope.max = 1;
        CurNode->node.Bucket.tail->Scope.LoopType = ExpGraph::LOOPTYPE::DOT;
        break;
    }
    case '{':
    { // 重复次数
        break;
    }

    case ')':
    {
        this->CurrentLevel -= 1;
        CurNode = CurNode->Parent;
        return ParserNextOne();
    }

    default:
    {
        if (IsChar(flag))
        {
            std::cout << "char flag is" << flag << std::endl;
            auto chr = new ExpGraph(CHR);
            chr->SetChr(flag);
            CurNode->AddBucketNext(chr);
            ret = ParserNextOne();

            break;
        }
    }
        // 控制字符以及非普通字符已经在前面被处理掉了
        // 需要判断剩下的字符是否仅有
    }

    return ParserNextOne();
}

void regex::Parser()
{
    if (this->form.size() == 0)
    {
        return;
    }
    CurNode = new ExpGraph(BUCKET);
    this->CurrentLevel = 0;
    CurNode->node.Bucket.SubnodeHead = nullptr;
    CurNode->node.Bucket.tail = nullptr;
    ParserNextOne();
}