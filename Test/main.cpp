#include "../inc/regex.h"
#include <assert.h>
int main(){
    regex REG("([a-z])+axy");
    auto T = REG.matchs("09434asdeaxy");
    assert(T.size()!= 0);
}