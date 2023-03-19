#include "../inc/regex.h"
#include <iostream>
#include <random>
#include <utility>
regex::regex(std::string ss) : form(std::move(ss)), bEOF(false)
{
    trans = false;
    if (ss.size() == 0)
    {
        this->head == nullptr;
        return;
    }
    this->cursor = 0;
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

    switch (GetNextSym())
    {
    case ('\0'):
        bEOF = true;
        return;

    case ('|'):
        // TODO:实现getlast元素和当前level相同
        //

    case ('\\'):
        char tab = GetNextSym();
        ret = new ExpGraph(SPEC_SYM);
        ret->SetLevel(this->CurrentLevel);
        ret->SetChr(tab);
        tail->AddNext(ret);
        tail = ret;
        ParserNextOne();
        break;
    case ('*'):
    // * 用于处理上一个结点 实现上一个节点的重复 使用层级难以区分 所以特此修改
        // get last same level node  and add a next pointer to it self
        break;
    case ('+'):
        ExpGraph *lastnode = GetLastNodeWithlevel(CurrentLevel);
        // get last same level node  and add a next pointer to it self
        break;
    case ('('):
        this->CurrentLevel += 1;
        goto ReExec;
    case ('.'): // 缺少非贪婪控制 需要后续修改
        char cr = GetNextSym();
        ret = new ExpGraph(Dot);
        break;

    case ('['):
        // TODO 在ExpGraph中间添加对 sym——scopt 范围的 支持
        UDF;
        break;
    case (')'): // 不应该存在
        this->CurrentLevel -= 1;
        goto ReExec;
        break;
    default:
        // 控制字符以及非普通字符已经在前面被处理掉了
        // 需要判断剩下的字符是否仅有
        char sym = GetNextSym();
        if (IsChar(sym))
        {
            ret = new ExpGraph(CHR);
            ret->SetChr(sym);

            break;
        }
        return ret;
    }

    ExpGraph *regex::GetLastNodeWithlevel(int level)
    {
        //     0    1       1    0
        //   node (avx(manue)|(hellow）)*  avxhellowavxavx
        //（（avx(manue)|(hellow）*)  avxhellowavxavx
        /**TODO
         * 从avx 结点
        */
        // (avx*)   avxxxx

    }

    void regex::Parser()
    {
        if (this->form.size() == 0)
        {
            this->head = NULL;
            this->tail = NULL;
            return;
        }
        this->head = new ExpGraph(HEAD);
        this->tail = this->head;
        this->CurrentLevel = 0;
        head->AddNext(ParserNextOne());

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