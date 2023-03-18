#include "../inc/regex.h"
#include <iostream>
#include <random>
#include <utility>
regex::regex(std::string  ss):form(std::move(ss))
{
    trans=false;
    if(ss.size()==0)
    {
        this->head==nullptr;
        return;
    }
    this->cursor=0;
    
}

char regex::GetNextSym()
{
    if(cursor<=this->form.size())
    {
        return form[cursor++];
    }

}

ExpGraph* regex::ParserNextOne()
{
    ExpGraph  * ret=nullptr;
    int L = this->CurrentLevel;
    switch (GetNextSym())
    {
    case ('\\'):
        char tab = GetNextSym();
        ret = new ExpGraph(SPEC_SYM);
        ret->SetLevel(this->CurrentLevel);
        ret->SetChr(GetNextSym());
        return ret;
        break;
    case ('('):
    ret =  new ExpGraph(SUB_EXPRESS);
    ret->SetLevel(L);
    this->CurrentLevel+=1;
    ret->AddNext(ParserNextOne());
    return ret;
        break;


    case ('.')://缺少非贪婪控制 需要后续修改
        char cr = GetNextSym();
        ret=new ExpGraph(Dot);
        if(cr=='*' || cr=='+' )
        {
            ret->AddNext(ret);
        }

        RollBack();
        break;


    case ('['):
    // TODO 在ExpGraph中间添加对 sym——scopt 范围的 支持
    UDF;
        break;


    case (')'):// 不应该存在
    this->CurrentLevel-=1;
        break;
    default:
        // 控制字符以及非普通字符已经在前面被处理掉了
        // 需要判断剩下的字符是否仅有


        break;
    }
}


ExpGraph* regex::GetLastNodeWithlevel(int level )
{
    
}



void regex::Parser()
{
    if(this->form.size()==0)
    {
        this->head=NULL;
        this->tail=NULL;
        return;
    }
    this->head=new ExpGraph(HEAD);
    this->tail=this->head;




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