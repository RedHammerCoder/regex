#ifndef _outputMessage_
#define _outputMessage_
#include <string>
#include <iostream>
#include <utility>
#include <ostream>
using namespace std;

template<typename T>
class OPstream : public T
{
    std::string _HeadMsg;
    std::string _tail_msg;
    
    T _Localstream;
    public:
    OPstream& operator<<(string msg){
        _Localstream<<_HeadMsg<<msg<<_tail_msg;
    }



    OPstream(T & output  ):_Localstream(output) {}
    OPstream(T & output , string && head , string && tail):OPstream(output),_HeadMsg(std::move(head)),_tail_msg(sted::move(tail)){
    }
    
    private: 

};


template<typename T>
class Messages: public 
{
private:
    /* data */
    Messages(){}
public:
    void print(string S){
        T rt;
        


        
    }
    
    template<typename TT>;
    static Messages* GetInstance()
    {
        static Messages<TT> Msg;
        return &Msg;

    }

};












#endif