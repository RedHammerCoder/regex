/**
 * @file EscapeCharacter.cpp
 * @author your name (you@domain.com)
 * @brief 提供转义字符串的翻译
 * @version 0.1
 * @date 2023-04-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <array>


std::array<char , 256> EscapCharMap;
struct EscapeCharReg
{
    EscapeCharReg()//使用构造函数初始化
    {
        EscapCharMap.fill(0);
        EscapCharMap['a']='\a';
        EscapCharMap['b']='\b';
        EscapCharMap['f']='\f';
        EscapCharMap['r']='\f';
        EscapCharMap['n']='\n';
        EscapCharMap['t']='\t';
        EscapCharMap['v']='\v';
        EscapCharMap['\\']='\\';
        EscapCharMap['\'']='\'';
        EscapCharMap['0']='\0';
        EscapCharMap['\"']='\"';
    }
    /* data */
}EscapeCharRegister;
