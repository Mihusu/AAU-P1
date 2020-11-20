#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define KEYWORD_LENGTH 12 //amount of keywords in array
#define MAX_WORDS 100 //max words in the CV

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
void generate_cv(char **filtered_cv, bool *included_paragraphs, char ***theSectionsOut, int sectionsCount, int *wordsInSection){
    int j = 0;
    int total_chars = 1;
    int ammount_malloced = 100;
    *filtered_cv = malloc(ammount_malloced*sizeof(char));
    **filtered_cv = '\0';
    for(int i = 0; i < sectionsCount; i++){
        
        if (included_paragraphs[i])
        {
            for(int k = 0; k < wordsInSection[i]; k++){
                if (total_chars + strlen(theSectionsOut[i][k]) + 1 >= ammount_malloced){
                    ammount_malloced += 100;
                    *filtered_cv = realloc(*filtered_cv, ammount_malloced * sizeof(char));
                }
                strcat(*filtered_cv,theSectionsOut[i][k]);
                if (k != wordsInSection[i] - 1){
                    strcat(*filtered_cv," "); //puts a space after each word, if it isnt the last word
                }
            }
            strcat(*filtered_cv,"\n"); //adds newline
            j++;
        }  
    }
}

//calculates the density of all paragraphs and returns the value into the density array
void calculate_cv_density(double *density_of_paragraph, char ***theSectionsOut, char *keyword_List[KEYWORD_LENGTH], int *length, int sectionsCount){
    for (int i = 0; i < sectionsCount; i++) //loops through all paragraphs to get each density.
    {
        int weight = calculate_paragraph_weight(theSectionsOut[i],keyword_List,length[i]);
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
void include_paragraph(double *Density, char ***theSectionsOut, int *length, bool *include, int sectionsCount) {
    Tuple priority_array[sectionsCount]; //defining priority array as a tuple

    for (int i = 0; i < sectionsCount; i++) { //initializes the priority array with the values from density.
        priority_array[i].doubleVal = Density[i];
        priority_array[i].intVal = i;
    }
    qsort(priority_array, sectionsCount, sizeof(Tuple), cmp_tuples); //sorts the priority array from highest density to lowest

    int words = 0;
    int i = 0;
    while (words < MAX_WORDS && i < sectionsCount) {  //creates the bool array with what paragraphs that needs to be included
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

