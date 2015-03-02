#include <stdio.h>
#include <cs50.h>

int main (void) {

    float change;
    int value;
    int c = 0;
    int Convert (float x);

    do {
        printf("Hello! How much change do you need?\n");
        change = GetFloat();
    } while (change <= 0);

    value = Convert(change);    
        
    while (value >= 25) {
        value = value - 25;
        c++;
    }
    
    while (value >= 10) {
        value = value - 10;
        c++;
    }

    while (value >= 5) {
        value = value - 5;
        c++;
    }

    while (value >= 1) {
        value = value - 1;
        c++;
    }
    
    printf("%i\n", c);
}

int Convert (float x) {
    x = x * 10;
    x = x * 10;
    return x;    
}

