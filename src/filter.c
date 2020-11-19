#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define KEYWORD_LENGTH 12 //amount of keywords in array
#define PARA_AMOUNT 6 //amount of paragraphs
#define PARA_LENGTH 12 //length of each paragraph
#define MAX_WORDS 10 //max words in the CV
#define OUTPUT_PARA_AMOUNT 2 //amount of paragraphs in output

typedef struct {
    double doubleVal; //density array
    int intVal; //value to be inserted into cv, to declare which to add first.
} Tuple;//defines the tuple as (x,y), where x is double val, and y is intval

void include_paragraph();
bool is_word_match();
int calculate_paragraph_weight();
void calculate_paragraph_density();
void calculate_cv_density();
int cmp_tuples();
void generate_cv();

//checks if a paragraph in CV is apart of "bool included paragraphs" to add those paragraphs to "filtered_cv"
void generate_cv(char *filtered_cv[OUTPUT_PARA_AMOUNT][PARA_LENGTH], bool included_paragraphs[PARA_AMOUNT], char *cv[PARA_AMOUNT][PARA_LENGTH]){
    int j = 0;
    for(int i = 0; i < PARA_AMOUNT; i++){
        if (included_paragraphs[i] == 1)
        {
            for(int k = 0; k < PARA_LENGTH; k++){
                filtered_cv[j][k] = cv[i][k];
            }
            j++;
        }  
    }
}

//calculates the density of all paragraphs and returns the value into the density array
void calculate_cv_density(double *density_of_paragraph, char *cv[PARA_AMOUNT][PARA_LENGTH], char *keyword_List[KEYWORD_LENGTH], int length[PARA_AMOUNT]){
    for (int i = 0; i < PARA_AMOUNT; i++) //loops through all paragraphs to get each density.
    {
        int weight = calculate_paragraph_weight(cv[i],keyword_List,length[i]);
        calculate_paragraph_density(weight,length[i],density_of_paragraph, i);
    }
}

// divides paragraph weight with the same paragraphs length, to find density form 0 to 1
void calculate_paragraph_density(int Weight, int Length, double* density, int i){
    density[i] = ((double)Weight)/((double)Length);
}

//Checks for how many times a paragraph matches keywords
int calculate_paragraph_weight(char *Paragraph[], char *Keywords[], int length){
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
//returns a pointer to bool array of which paragraphs that should be included.
void include_paragraph(double *Density, char *cv[PARA_AMOUNT][PARA_LENGTH], int length[PARA_AMOUNT], bool *include) {
    Tuple priority_array[PARA_AMOUNT]; //defining priority array as a tuple

    for (int i = 0; i < PARA_AMOUNT; i++) { //initializes the priority array with the values from density.
        priority_array[i].doubleVal = Density[i];
        priority_array[i].intVal = i;
    }
    qsort(priority_array, PARA_AMOUNT, sizeof(Tuple), cmp_tuples); //sorts the priority array from highest density to lowest

    int words = 0;
    int i = 0;
    while (words < MAX_WORDS) {  //creates the bool array with what paragraphs that needs to be included
        words += (int)length[priority_array[i].intVal];
        include[priority_array[i].intVal] = 1; 
        i++;
    } 
}

// Comparing tuples by comparing the first (double) value = doubleval. to be used in stdlib.qsort
int cmp_tuples(const void * a, const void * b) {
    double cmp = ((*(Tuple*)b).doubleVal - (*(Tuple*)a).doubleVal);
    // Make sure a negative double also results in returning a negative int, and likewise for positive
    if (cmp < 0.0) {return -1;}
    else if (cmp > 0.0) {return 1;}
    else {return 0;}
}

