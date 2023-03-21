#ifndef SGN_H_INCLUDED
#define SGN_H_INCLUDED
#include "grossnum.h"
#include <string>

enum Singum{PLUS=0,MINUS=1};
class SGN : public GROSSNUM {
private:
    int sign;
    static std::string deleteSign(const char* str);
public:
    SGN():GROSSNUM() {sign = PLUS;}
    SGN(const char *);
    SGN (int);
    void prt(); // печать большого числа со знаком
    int operator > (SGN & a);
    SGN& operator += (const SGN& a) {
        GROSSNUM::operator += (a);
        return *this;
    }
};

std::string SGN::deleteSign(const char* str) {
    if (str[0] == '-') // если в начале минус
        return str+1; // неучитываем плюс
    else if (str[0] == '+') // если число началось со знаком +
        return str+1; // неучитываем плюс
    else
        return str; // преобразуем всю строку
}

SGN :: SGN(const char *str) : GROSSNUM(deleteSign(str).c_str()) {
    if (str[0] == '-') // если в начале минус
        sign = MINUS; // записываем в знак, что число отрицательно
    else if (str[0] == '+') // если число началось со знаком +
        sign = PLUS; // у числа знак +
    else
        sign = PLUS; // у числа знак +
}
SGN :: SGN(int n) : GROSSNUM((n >= 0) ? n : -n) {
    if (n >= 0)
        sign = PLUS;
    else
        sign = MINUS;
}
void SGN :: prt() {
    if (this->sign == MINUS)
        putchar('-');
    GROSSNUM::prt();
}
#endif
