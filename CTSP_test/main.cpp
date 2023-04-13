#include "head.hpp"
#include <iostream>

class ADD:ImplDadd<ADD>
{
    public:
    void Impl(){
        std::cout<<"call impl"<<std::endl;
    }

    void print(){
        std::cout<<"call print"<<std::endl;
    }
    
};


RegisterManager<ADD> RegM;


int main()
{

}