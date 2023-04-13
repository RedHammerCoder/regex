#include <iostream>

template<typename T>
class Base {
    public:
    virtual void print(){
        std::cout<<"Base print"<<std::endl;
        T* Imp = static_cast<T*>(this);
        Imp->int_print();
        
    }


};

class Ext1 : public Base<Ext1>
{
    public: 
    void int_print()  {
        std::cout<<"exec in Ext1"<<std::endl;
    }
};


class Ext2 : public Base<Ext2>
{
    public: 
    void print()override{
        std::cout<<"dir exec in Ext2"<<std::endl;
    }
    void int_print()  {
        std::cout<<"exec in Ext2"<<std::endl;
    }
};

template<typename UNI>
void UNI_print(Base<UNI> & T){
    T.print();
}





int main(){
    Ext2 T2;
    Ext1 T1;
    T1.print();
    T2.print();
    UNI_print<Ext2>(T2);
    UNI_print<Ext1>(T1);
    return 0;

}