#ifndef __UTILITY__
#define __UTILITY__

inline bool IsAlpha(char cr)
{
    ((cr>='a' && cr<='z')||(cr>='A'&& cr<='Z'))?true :false;
}
 inline bool IsNum(char chr)
{
    return chr>='0'&&chr<='9'?true:false;

}
 inline bool IsChar(char chr){
    return IsAlpha(chr)||IsNum(chr);
}



#endif