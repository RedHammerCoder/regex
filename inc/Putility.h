#ifndef __UTILITY__
#define __UTILITY__

bool IsAlpha(char cr)
{
    if((cr>='a' && cr <='z') || (cr>='A' && cr<='Z'))
    {
        return true;
    }
    else
    {
        return false;
    }
    

}

bool IsNum(char chr)
{
    return chr>='0'&&chr<='9'?true:false;

}
bool IsChar(char chr){
    return IsAlpha(chr)||IsNum(chr);
}



#endif