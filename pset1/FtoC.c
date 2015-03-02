#include <stdio.h>
#include <math.h>
#include <cs50.h>

// This function converts Farenheit to Ceslsius
int main(void)
{
printf("Please enter a temperature in Farenheit: ");
float F = GetFloat();
float c = ( 5.0 / 9) * (F - 32);
printf("That value in Farenheit is equal to %.1f in Celsius.", c);
return 0;
}
