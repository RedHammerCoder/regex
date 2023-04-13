#include "../inc/regex.h"
#include <iostream>
#include <random>
#include <utility>
regex::regex(std::string ss) : form(std::move(ss)), bEOF(false)
{
    std::cout<<form<<std::endl;
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
    {
        bEOF = true;
        return nullptr;
        break;
    }

    case '|':
    {
        if (CurNode->node.Bucket.tail->nodetype != Divide)
        {
            ExpGraph *Tmp = ParserNextOne();
            ExpGraph *divd = new ExpGraph(FELLOWCTRL);
            ExpGraph *lastone = CurNode->node.Bucket.tail;
            divd->Perfix = lastone->Perfix;
            CurNode->node.Bucket.tail = divd;
            divd->AddDivNext(Tmp);
            divd->AddDivNext(lastone);
        }
        else
        {
            ExpGraph *Tmp = ParserNextOne();
            ExpGraph *lastone = CurNode->node.Bucket.tail;
            assert(lastone->nodetype == Divide);
            lastone->AddDivNext(Tmp);
        }
        return ParserNextOne(   );
        break;
    }

    case '\\':
    {
        char tab = GetNextSym();
        ret = new ExpGraph(SPEC_SYM);
        ret->SetLevel(this->CurrentLevel);
        ret->SetChr(tab);

        return ParserNextOne();
        break;
    }

    case '*':
    {
        UDF;
        break;
    }

    case '+':
    {
        UDF;
        break;
    }

    case '(':
    {
        ExpGraph *Lnode = new ExpGraph(BUCKET);
        Lnode->Parent=CurNode;
        CurNode->AddBucketNext(Lnode);
        CurNode = Lnode;
        this->CurrentLevel += 1;

        return ParserNextOne();
        
    }
    case '.': // 缺少非贪婪控制 需要后续修改
    {
        char cr = GetNextSym();
        auto T = new ExpGraph(Dot);
        CurNode->AddBucketNext(T);
        return ParserNextOne();
    }
    case '[':
        // TODO 在ExpGraph中间添加对 sym——scopt 范围的 支持
        {
            UDF;
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
            auto chr = new ExpGraph(CHR);
            chr->SetChr(flag);
            CurNode->AddBucketNext(chr);
            ret= ParserNextOne();

            break;
        }
    }
        // 控制字符以及非普通字符已经在前面被处理掉了
        // 需要判断剩下的字符是否仅有
    }
    return ret;
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

#if 0
    if(tail==NULL)return;
    switch (GetNextSym())
    {
    case ('\\'):
        char tab = GetNextSym();
        auto T=new ExpGraph(SPEC_SYM);
        T->SetLevel(this->CurrentLevel);
        break;
    case ('('):

        break;
    case ('*'):
    //get last same level node  and add a next pointer to it self
        break;
    case ('+'):
    //get last same level node  and add a next pointer to it self
        break;
    case ('.'):
    auto tmp = new ExpGraph(Dot);
    tail->AddNext(tmp);
    tail=tmp;
        break;
    case ('?'):
    std::cout<<"current not support"<<std::endl;
        break;
    case ('['):
    auto *apend = new ExpGraph(SCOPE); 
    tail->AddNext(apend);
    tail=apend;
        break;
    case ('|'):
        auto tmp = GetLastNodeWithlevel(CurrentLevel);

        break;
    default:
    //控制字符以及非普通字符已经在前面被处理掉了
        break;
    }

#endif
}