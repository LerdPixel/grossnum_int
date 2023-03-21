#ifndef GROSSNUM_H
#define GROSSNUM_H
#include <stdio.h>//печатаем по стандарту С, это лучше
#include <string.h>//для работы со строками (без std)
#include <stdlib.h>
#define N 256 //количество блоков
#define L 6 //количество цифр 1 блока
#define MAX 1000000 //макс число в  1 блоке

class GROSSNUM
{
protected:
    int num[N]; //число
    int len; //кол-во цифр
    void swap(int i, int j); //меняет местами 2 блока
    void reverse(); //обращает массив
    int power(int base, int exponent); // возводив base в степень exponent
    static int sum_digits(int i, int j, int &flag); // модуль суммирования 2 цифр
    static int mult_digits(int i, int j, int &flag); // модуль умножения 2 цифр
    GROSSNUM add_modules(GROSSNUM &a); // модуль сложения
    GROSSNUM mult_simple(int j, int numeral); // умножение большого числа на int
    int GROSSNUMcmp(GROSSNUM&); // аналог strcmp()

public:
    GROSSNUM(); //конструктор класса для инициализации по умолчанию
    GROSSNUM(const char*); // конструктор для строки
    GROSSNUM(int); // конструктор для целого числа
//    GROSSNUM(long long); // конструктор для целого числа(long long)
    friend GROSSNUM operator + (GROSSNUM &x, GROSSNUM &y); // оператор сложения
    GROSSNUM& operator ++ (); // инкремент большого числа
    GROSSNUM& operator += (const GROSSNUM&); // оператор присваивания суммы
    friend GROSSNUM operator * (GROSSNUM &x, GROSSNUM &y); // оператор умножения
    GROSSNUM& operator *= (GROSSNUM&); // оператор *=
    GROSSNUM& operator *= (int); // оператор *=, домножает большое число на int меньший MAX
    int operator > (GROSSNUM&); // логический оператор больше, возращает 1 или 0
    int operator < (GROSSNUM&); // логический оператор меньше
    int operator == (GROSSNUM&);
    int operator != (GROSSNUM&);
    int operator >= (GROSSNUM&);
    int operator <= (GROSSNUM&);
    void prt(); //печать большого числа
};
GROSSNUM :: GROSSNUM()
{
    num[0] = 0; // приравниваем к нулю
    len = 1; // длина 1
}

GROSSNUM :: GROSSNUM(int n)
{
    int i = 0; // счётчик разрядов большого числа
    do { // в случае n = 0, его нужно записать
        num[i] = n % MAX; // записываем последние L цифры в i элемент, так они запишутся в обратном порядке
        n /= MAX;  // убираем их для повторного считывания
        ++i; // инкрементируем счётчик
    } while(n); //
    len = i; // определяем длину
}

/*GROSSNUM :: GROSSNUM(long long n)
{
    int i = 0; // счётчик разрядов большого числа
    do { // в случае n = 0, его нужно записать
        num[i] = n % MAX; // записываем последние L цифры в i элемент, так они запишутся в обратном порядке
        n /= MAX;  // убираем их для повторного считывания
        ++i; // инкрементируем счётчик
    } while(n); //
    len = i; // определяем длину
}*/
GROSSNUM :: GROSSNUM(const char* str)
{
    int l = strlen(str); // в l длина строки
    len = (l - 1) / L + 1; // определяем количесво цифр блока
    int j = l - 1; // начинаем с конца
    for(int i = 0; i < len; ++i) // после определения 1 цифры блока
    {
        num[i] = 0; // для суммирования определяем цифру блока за 1
        for( ; j >= l - L*(i+1) && j >= 0; --j)
        {
            num[i] += (str[j]-'0') * power(10, (l - j - 1 - i * L));
        }
    }
}
void GROSSNUM :: prt()// печать большого числа
{
    int n; // степень 10
    printf("%d", num[len - 1]); // печать первой цифры большого числа
    for (int i = len - 2; i >= 0; --i) // печать остальных цифр
    {
        n = MAX / 10;
        for (int j = 0; j < L-1 && n > num[i]; ++j) // если в разряде меньше L 10-чных цифр
        {
            printf("0"); // дописываем нужное число нулей
            n /= 10;
        }
        printf("%d", num[i]); // после печатаем разряд
    }
    printf("\n");
}
/*
GROSSNUMcmp сравнивает 2 больших числа
возращает 1, если первое больше второго
возращает 0, если они равны
возращает -1, если второе больше первого
*/
int GROSSNUM :: GROSSNUMcmp(GROSSNUM& x)
{
    if (x.len < this->len) // если длина первого больше второго
        return 1; // оно само больше второго
    if (x.len > this->len) // если длина второго больше первого
        return -1; // оно само больше первого
    else // если длины равны
    {
        for (int i = this->len - 1; i >= 0; --i) // сравниваем цифры начиная со старшего разряда (с конца)
        {
            if(this->num[i] > x.num[i])
                return 1;
            if(this->num[i] < x.num[i])
                return -1;
        }
    }
    return 0; // если одинаковая длина и все цифры равны, то они равны
}

/*
power() - функция степени
возращаес base в степень exponent
*/
int GROSSNUM :: power(int baze, int exponent)
{
    int res = 1; // объявляем переменную результата, присвоим 1, чтобы можно было домножать
    for (int i = 0; i < exponent; ++i) { //в результат произведение base, exponent раз
        res *= baze;
    }
    return res;
}
int GROSSNUM :: sum_digits(int i, int j, int &flag)
{
    int t = i + j + flag; // само сложение
    flag = t / MAX; // обновляем флаг
    t %= MAX; // в случае если переполнился разряд убираем последнюю цифру
    return t;
}

int GROSSNUM :: mult_digits(int i, int j, int &flag)
{
    long long res = (long long)i * (long long)j + flag;
    flag = res / MAX;
    res %= MAX;
    return (int)res;
}
GROSSNUM GROSSNUM :: add_modules(GROSSNUM &a)
{
    GROSSNUM z, x;
    x = a;
    int l, i, flag = 0;
    l = x.len > this->len ? this->len : x.len; // определяем наименьшую длину
    for (i = 0; i < l; ++i)
        z.num[i] = sum_digits(x.num[i], num[i], flag);//складываю по разрядам
    if(l == this->len) // в случае если x длиннее
        for (;i < x.len; ++i)
            z.num[i] = sum_digits(x.num[i], 0, flag); // прибавляем только x
    else if(l == x.len) // в случае если y длиннее
        for (;i < this->len; ++i)
            z.num[i] = sum_digits(num[i], 0, flag);  // прибавляем только x
    if ((i==N-1)&&(flag==1)) //отрабатываем случай возможного переполнения
    {
        puts("number overfull!");
//        system("pause");
//        exit(1);
    }
    if(flag)
    {
        z.num[i] = 1; //учитываю флаг (если он установлен)
        z.len = i + 1; // устанавливаю длину на 1 больше
    }
    else
        z.len = i; // устанавливаю обычную длину
    return z;
}
/*
mult_simple() - умножение большого числа на большое число с одной цифрой
*/
GROSSNUM GROSSNUM :: mult_simple(int j, int numeral)
{
    GROSSNUM term;
    int i = 0, flag = 0;
    for (; i < j; ++i)
        term.num[i] = 0;
    for ( ; i < len + j; ++i)
        term.num[i] = mult_digits(num[i - j], numeral, flag);
    if ((i == N - 1) && (flag > 0)) //отрабатываем случай возможного переполнения
    {
        puts("number overfull!");
//        system("pause");
//        exit(1);
    }
    if(flag)
    {
        term.num[i] = flag; //учитываю флаг (если он установлен)
        term.len = i + 1; // устанавливаю длину на 1 больше
    }
    else
        term.len = i; // устанавливаю обычную длину
    return term; // возвращаю произведение
}

GROSSNUM operator * (GROSSNUM &x, GROSSNUM &y)
{
    GROSSNUM comp(0), // сумма произведений на разряды
     a = x, b = y; // сохраняем значения переменных
    int l, i; // l - длина наименьшего числа, i - счётчик
    for (i = 0; i < a.len; ++i)
    {
        GROSSNUM d = b.mult_simple(i, a.num[i]); // находим произведение большого чусла на i разряд второго
        comp += d; // складываем их
    }
    return comp; // возращаем результат
}
GROSSNUM& GROSSNUM::operator *= (GROSSNUM &x)
{
    GROSSNUM comp(0), a = x; // сохраняем значения переменных
    int l, i; // l - длина наименьшего числа, i - счётчик
    for (i = 0; i < this->len; ++i)
    {
        GROSSNUM d = a.mult_simple(i, this->num[i]);// находим произведение большого чусла на i разряд второго
        comp += d;// складываем их
    }
    *this = comp; // присвоим произведение к данному большому числу
    return *this; // возращаем результат
}
GROSSNUM operator + (GROSSNUM &x, GROSSNUM &y) // сложение 2 больших чисел
{
    return x.add_modules(y); // возращаем сумму
}
GROSSNUM& GROSSNUM::operator *= (int n)
{
    n %= MAX;
    *this = mult_simple(0, n);
    return *this;
}
int GROSSNUM::operator > (GROSSNUM &x)
{
    if (GROSSNUMcmp(x) == 1)
        return 1;
    return 0;
}
int GROSSNUM::operator < (GROSSNUM &x)
{
    if (GROSSNUMcmp(x) == -1)
        return 1;
    return 0;
}
int GROSSNUM::operator == (GROSSNUM &x)
{
    if (!GROSSNUMcmp(x))
        return 1;
    return 0;
}
int GROSSNUM::operator != (GROSSNUM &x)
{
    if (GROSSNUMcmp(x))
        return 1;
    return 0;
}
int GROSSNUM::operator >= (GROSSNUM &x)
{
    if (GROSSNUMcmp(x) == -1)
        return 0;
    return 1;
}
int GROSSNUM::operator <= (GROSSNUM &x)
{
    if (GROSSNUMcmp(x) == 1)
        return 0;
    return 1;
}
GROSSNUM& GROSSNUM::operator ++ ()
{
    int i, flag = 0; // i - счётчик разрядов, flag - перенос
    num[0] = sum_digits(num[0], 1, flag); //наименьший разряд x c 1
    for (i = 1; i < len; ++i)  // учёт возможного переноса
        num[i] = sum_digits(num[i], 0, flag); //складываю по разрядам
    if(flag)
    {
        if ((i==N-1)) //отрабатываем случай возможного переполнения
        {
            puts("number overfull!");
    //        system("pause");
    //        exit(1);
        }
        num[i] = 1; //учитываю флаг (если он установлен)
        len = i + 1; // устанавливаю длину на 1 больше
    }
    return *this; // return reference to modified object
}
GROSSNUM& GROSSNUM::operator += (const GROSSNUM &a)
{
    GROSSNUM x = a;
    int l, i, flag = 0;// i - счётчик разрядов, flag - перенос
    l = x.len > this->len ? this->len : x.len; // определяем наименьшую длину
    for (i = 0; i < l; ++i)
        this->num[i] = sum_digits(x.num[i], this->num[i], flag);//складываю по разрядам
    if(l == this->len) // в случае если x длиннее
        for (;i < x.len; ++i)
            this->num[i] = sum_digits(x.num[i], 0, flag); // прибавляем только x
    else if(l == x.len) // в случае если y длиннее
        for (;i < this->len; ++i)
            this->num[i] = sum_digits(this->num[i], 0, flag);  // прибавляем только x
    if ((i==N-1)&&(flag==1)) //отрабатываем случай возможного переполнения
    {
        puts("number overfull!");
//        system("pause");
//        exit(1);
    }
    if(flag)
    {
        this->num[i] = 1; //учитываю флаг (если он установлен)
        this->len = i + 1; // устанавливаю длину на 1 больше
    }
    else
        this->len = i; // устанавливаю обычную длину
    return *this;
}
#endif
