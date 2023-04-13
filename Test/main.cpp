#include "../inc/regex.h"
#include <assert.h>
#include <iostream>
#include <string>
int main(){
    regex REG( std::string("(reg|malloc)axy"));
    std::cout<<"parser"<<std::endl;
    
    // auto T = REG.matchs("09434asdeaxy");
    // assert(T.size()!= 0);
    return 0;
}