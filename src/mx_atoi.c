#include "race.h"

int mx_atoi(const char *str) {
    int i = 0;
    int sum = 0;
    int sign = 1;
    char *s = (char *)str;

    while (mx_isspace(s[i]) == true)
        i++;
    if (s[i] == '-') {
        sign = -1;
        i++;
    }
    if (s[i] == '+') {
        sign = 1;
        i++;
    }
    while (mx_isdigit(s[i]) == true) {
        sum = sum * 10 + (s[i] - '0');
        i++;
    }
    return sum * sign;
}

