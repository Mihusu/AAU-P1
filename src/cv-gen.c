#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void inclusion(double *a, int b, bool *c);

int main(void){
    int b;
    double strArr_density_CV[] = {8, 32, 4556, 3, 93, 43, 112, 342};
    inclusion(strArr_density_CV, b);

    return 0;
}

int cmpfunc (const void *ep1, const void *ep2) {
    double *tp1 = (double*)ep1;
    double *tp2 = (double*)ep2;
    
    if (*tp1 < *tp2) {
        return -1;
    }
    else if (*tp1 < *tp2) {
        return 1;
    }
    else {
        return 0;
    }
}

void inclusion(double *a, int max_word_count_CV = 702, bool *c) {
    typedef struct {
        char strVal;
        int intval;
    } tTuple;
    // tTuple list[702];

    int biggist_density, sum = 0;
    int max_word_count_CV = 702; //change at a later stage, to the req.txt
    int j, i; 

    while(sum < max_word_count_CV) {
        for(i = 0; i < max_word_count_CV; i++) {
            sum += i;
        
        }
        
        for(j = 0; j < biggist_density; i++)  {
                
        }
    } 
    printf("AFTER sorting\n"); 
    qsort(a, 702, sizeof(int), cmpfunc);
    // printing strings in sorted order 
    for (i= 0; i < 702; i++) {
        printf(" %s ", a); 
    }
} 

/* Første er til at vælge de vigtigste fra string arrays 
   (KOMMER FRA DESENTY FUNKTIONEN). Skal sortere og gå tilbage og sortere igen, 
   anden skal angive den maksimale længde af et CV og det tredje skal gøres ved at vælge afsnit
   og sortere dem fra ved hjælp af TRUE eller FALSE. */