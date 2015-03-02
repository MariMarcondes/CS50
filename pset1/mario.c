#include <stdio.h>
#include <cs50.h>

    void Hash (int i);
    void Espace (int numero, int espace);
    int numero;

int main (void) {
    
    do {
    printf("Give me an integer from 0 to 23: ");
    numero = GetInt();
    } while (numero < 0 || numero > 23);
 
    for (int i = 1; i <= numero; i++) {
        Espace(numero, i);
        Hash (i);
        printf("#\n");
     }
} 
  
    void Hash (int e) {
         for (int x = 0; x < e; x++) {
         printf("#");
         }
    } 
        
    void Espace (int n, int s) {
         int hash = n - s;
         for (int z = 0; z < hash; z++) {
         printf(" ");
         }
    }     
