#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

void convert (string orginal, string argv);
bool checkWord (string s);

int main (int argc, string argv[]) {
    if (argc != 2) {
        printf("You should have given me a word! Try again.\n");
        return 1;
    } else {
        if (checkWord(argv[1])) {
            string original = GetString();
            convert(original, argv[1]);
        } else {
            printf("You should have given me a word! Try again.\n");
            return 1;
        } 
    }
}

bool checkWord (string s) {
    int count = 0;
    for (int i = 0; i < strlen(s); i++) {
        if (isalpha(s[i])) {
            count++;
        }
    }
    if (count == strlen(s)) {
    return true;
    } else {
    return false;
    }
}

void convert (string original, string k) {
            int x = strlen(k);
            int j = 0;
            for (int i = 0; i < strlen(original); i++) { 
                char cara = original[i];
            if (isupper(cara) && isupper(k[j])) {
                char prin = ((cara - 'A') + (k[j % x] - 'A')) % 26;
                printf("%c", prin + 'A');
                j++;
            } else if (islower(cara) && islower(k[j])) {
                char prin = ((cara - 'a') + (k[j % x] - 'a')) % 26;
                printf("%c", prin + 'a');
                j++;
            } else if (islower(cara) && isupper(k[j])) {
                char prin = ((cara - 'a') + (k[j % x] - 'A')) % 26;
                printf("%c", prin + 'a');
                j++;
            } else if (isupper(cara) && islower(k[j])) {
                char prin = ((cara - 'A') + (k[j % x] - 'a')) % 26;
                printf("%c", prin + 'A');
                j++;
            } else {
                printf("%c", cara);
            }
            }
            printf("\n");
}
