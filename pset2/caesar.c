#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

void convert (string original, int k);
int k;

int main (int argc, string argv[]) {
    if (argc != 2) {
        printf("You should have passed me a postive number! Try again.\n");
        return 1;
    } else {
            int k = atoi(argv[1]);
            if (k > 0) {
            string original = GetString();
            convert(original, k);
            } else {
                printf("You should have passed me a postive number! Try again.\n");
                return 1;        
            }
    }
}

void convert (string original, int k) {
            for (int i = 0; i < strlen(original); i++) { 
                char cara = original[i];
            if (isalpha(cara) && isupper(cara)) {
                char prin = ((cara - 65) + k) % 26;
                printf("%c", prin + 65);
            } else if (isalpha(cara) && islower(cara)) {
                char prin = ((cara - 97) + k) % 26;
                printf("%c", prin + 97);
            } else {
                printf("%c", cara);
            }
            }
            printf("\n");
}
