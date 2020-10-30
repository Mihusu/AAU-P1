#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define KEYWORD_LENGTH 12 //amount of keywords in array
#define PARA_AMOUNT 6 //amount of paragraphs
#define PARA_LENGTH 12 //length of each paragraph
#define MAX_WORDS 10 //max words in the CV

typedef struct {
    double doubleVal; //density array
    int intVal; //value to be inserted into CV, to declare which to add first.
} tTuple;//defines the tuple as (x,y), where x is double val, and y is intval
  
bool is_word_match();
int paragraph_Weight();
void paragraph_Density();
void cv_Density();
void inclusion();

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
  
// Comparing tuples by comparing the first (double) value = doubleval. to be used in stdlib.qsort
int cmp_tuples(const void * a, const void * b) {
    double cmp = ((*(tTuple*)b).doubleVal - (*(tTuple*)a).doubleVal);
    // Make sure a negative double also results in returning a negative int, and likewise for positive
    if (cmp < 0.0) {return -1;}
    else if (cmp > 0.0) {return 1;}
    else {return 0;}
}

void inclusion(double *Density, char *CV[PARA_AMOUNT][PARA_LENGTH], int *length[PARA_AMOUNT], bool *include) {
    tTuple priority_array[PARA_AMOUNT]; //defining priority array as a tuple

    for (int i = 0; i < PARA_AMOUNT; i++) { //initializes the priority array with the values from density.
        priority_array[i].doubleVal = Density[i];
        priority_array[i].intVal = i;
        printf("%d doubleval: %lf, intVal: %d  ---", i, priority_array[i].doubleVal,priority_array[i].intVal); //testing
        printf("density[%d]: %lf, CV[%d]: %s, length[%d]: %d, include[%d]: %d\n",i, Density[i], i, *CV[i], i, length[i],i,include[i]); //test
    }
    qsort(priority_array, PARA_AMOUNT, sizeof(tTuple), cmp_tuples); //sorts the priority array from highest density to lowest
    printf("\n==============\n"); //test
    for (int i = 0; i < PARA_AMOUNT; i++) //test
    {
        printf("%d doubleval: %lf, intVal: %d  ---\n", i, priority_array[i].doubleVal,priority_array[i].intVal); //testing
    }

    int words = 0;
    int i = 0;
    while (words < MAX_WORDS) {  //creates the bool array with what paragraphs that needs to be included
        words += (int)length[priority_array[i].intVal];
        include[priority_array[i].intVal] = 1; 
        i++;
    } 
}

