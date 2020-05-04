#include "race.h"

void mx_printint(int n) {
    if (n == 0) {
	mx_printchar(48);
    }
    else {
        if (n < 0) {
            n *= -1;
            mx_printchar('-');
        }
        int j = 0;
        int nn = n;
        while (n != 0) {
            n /= 10;
            j++;
        }
        int array [j];
        for (int i = j; i > 0; i--) {
             int s = nn % 10;
             array [i-1] = s;
             nn /= 10;
        }
        for (int i = 0; i < j; i++) {     
             mx_printchar(array [i] + '0');
        }
    }
} 
