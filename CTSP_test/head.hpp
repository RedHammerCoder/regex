

template<typename tname>
class ImplDadd{
public:

void Impl(){
    static_cast<tname>(this).Impl();
}

void print(){
    static_cast<tname>(this).print();
}
};



template<typename T>
class RegisterManager{
    public:
    template<typename Q>
    class register {
        public:
        register( target,  jobs){


        }


    };


};

