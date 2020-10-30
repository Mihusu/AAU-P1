#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define KEYWORD_LENGTH 12 //amount of keywords in array
#define PARA_AMOUNT 6 //amount of paragraphs
#define PARA_LENGTH 12 //length of each paragraph

bool is_word_match();
int paragraph_Weight();
void paragraph_Density();
void cv_Density();


//calculates the density of all paragraphs and returns the value into the density array
void cv_Density(double *density_of_Paragraph, char *CV[PARA_AMOUNT][PARA_LENGTH], char *keyword_List[KEYWORD_LENGTH], int length[PARA_AMOUNT]){
    for (int i = 0; i < PARA_AMOUNT; i++) //loops through all paragraphs to get each density.
    {
        int weight = paragraph_Weight(CV[i],keyword_List,length[i]);
        paragraph_Density(weight,length[i],density_of_Paragraph, i);
    }
}

// divies paragraph weight with the same paragraphs length, to find density form 0 to 1
void paragraph_Density(int Weight, int Length, double* density, int i){
    density[i] = ((double)Weight)/((double)Length);
}

//Checks for how many times a paragraph matches keywords
int paragraph_Weight(char *Paragraph[], char *Keywords[], int length){
    int match_Weight = 0;
    for(int j = 0; j < KEYWORD_LENGTH; j++)
    {
        int i = 0;
        for(; i < length; i++)
        {
            match_Weight += is_word_match(Paragraph[i],Keywords[j]);
        }
    }
    return(match_Weight);
}

//compares for string match, to see if they are the same.
bool is_word_match(char word_1[], char word_2[]){
    bool word_Match;
    word_Match = strcmp(word_1,word_2);
    //flips the bool value, since strcmp = 0 is true; strcmp = 1 is false
    if(word_Match == 0){
        return 1;
    }
    else{
        return 0;
    }
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

void inclusion(double *Density, char *CV[PARA_AMOUNT][PARA_LENGTH], int *length[PARA_AMOUNT], bool *include) {
    typedef struct {
        double doubleVal;
        int intVal;
    } tTuple;

    printf("density of 5: %lf", Density[4]);
    int biggist_density, sum = 0;
    int max_word_count_CV = 702; //change at a later stage, to the req.txt
    int j, i;

    while(sum < max_word_count_CV) {
        for(i = 0; i < max_word_count_CV; i++) {
            sum += i;

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



///*
// * Function to create an array with booleans of wether a paragraph is to be
// * included or not
// */
//void include(*importance_array, *inclusion_array){
//    *inclusion_array.i = true;// sets entries to true if they should be included
//}
//
///*
// * Function to output the plain text file with the final cv, so it can be
// * formatted
// */
//void output(long_cv, *inclusion_array){
//    for (int i = 0; i < size(long_cv); i++) {
//        if (*inclusion_array = true) {
//            print long_cv.i;
//        }
//    }
//}
//
//
