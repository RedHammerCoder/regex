#pragma once
#include <iostream>
#include <vector>
extern std::array<char , 256> EscapCharMap;
struct BitSet {
    private: 
    std::vector<bool> CORE ;//CORE 是Bitset的点集
    public:
    BitSet():CORE(false)
    {
        CORE.resize(256);
        CORE={false};
    }
    BitSet(char C){
        BitSet();
        CORE[C]=1;
    }
    BitSet(char beg , char end)
    {
        BitSet();
        for(int i=beg ; i<=end ; i++)
        {
            CORE[i]=true;
        }
    }
    void AddScope(char beg , char end){
        for(int i=beg ; i<=end ; i++)
        {
            CORE[i]=true;
        }

    }


    bool Addelement(char C)
    {
        if (CORE[C] == true)
        {
            return false;
        }
        else
        {
            CORE[C]=true;
            return true;
        }
        
    }

    bool InScope(char C){
        return CORE[C];
    }
    void Clear(char C){
        CORE[C]=false;
    }

};