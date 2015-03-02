/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>
#include "helpers.h"
#include <math.h>

int count = 0;
void sort (int array[], int n);
int arrange (int array[], int n);
/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n) {
    int max = n - 1;
    int min = 0;
    while (max >= min) {
        int mid = (max + min) / 2;

        if (values[mid] == value) {
            return true;
        } else if (values[mid] > value) {
            max = mid - 1;
        } else {
            min = mid + 1;
        } 
    }
       return false;
}
/**
 * Sorts array of n values.
 */
void sort (int array[], int n) {
    do {
        arrange (array, n);
    } while (count > 0);
}

int arrange (int array[], int n) {
    count = 0;
    for (int i = n-1; i > 0; i--) {
            if (array[i] < array [i-1]) {
                int temp = array[i];
                array[i] = array[i-1];
                array[i-1] = temp;
                count++;
            }
    }
    return count;
}
