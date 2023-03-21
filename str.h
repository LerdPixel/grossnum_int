#ifndef STR_H
#define STH_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

class STR
{
private:
    char* str;
    int len;
public:
    STR ();
    STR (const char*);
    STR (int);

    ~STR (); //деструктор
    void print();
};

STR::STR()
{
    str = (char*)malloc(1);
    *str='\0';
    len = 0;
}
STR::STR(const char * string)
{
    len = strlen(string);
    str = (char*)malloc(len + 1);
    strcpy(str, string);
}
STR::STR(STR &x)
{
    strcpy(this)
}
STR::~STR()
{
    free(str);
}
STR::print()
{
    puts(str);
}
#endif
