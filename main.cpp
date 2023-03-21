#include <stdio.h>
#include <string.h>
#include "str.h"


int main() {
    STR first("test"), second;
    second = first;
    first.print();
    first.print();
    second.print();
    return 0;
}
