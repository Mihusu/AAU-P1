#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LETTERS 50 //PARAGRAPH_MAX_LETTERS_PER_WORD
#define KEYWORD_LENGTH 6 //amount of keywords in array
#define PARA_AMOUNT 5 //amount of paragraphs
#define PARA_LENGTH 8 //length of each paragraph

bool is_word_match(char word_1[], char word_2[]);
int paragraph_Weight(char Paragraph[][MAX_LETTERS], char Keywords[][MAX_LETTERS], int length);
void paragraph_Density(int Weight, int Length,double *density);

int main(void){
    char paragraph1[PARA_LENGTH][MAX_LETTERS] = {"hej","hvordan","gaar","det","asd","Jeg","Har","BSC"}; //testing, tb replace by read.c
    char buzz[KEYWORD_LENGTH][MAX_LETTERS] = {"hej","hvordan","gaar","det","med","sig"}; //testing, tb replace by read.c
    int length[PARA_AMOUNT] = {PARA_LENGTH,2,3,4,5}; //testing, tb replace by read.c
    double density_of_Paragraph[PARA_AMOUNT];
    

    for (int i = 0; i < PARA_AMOUNT; i++) //loops through all paragraphs to get each density. only the first paragraph
    {
        int weight = paragraph_Weight(paragraph1,buzz,length[i]);
        paragraph_Density(weight,length[i],&density_of_Paragraph[i]);
        printf("density of paragraph %d: %lf",i, density_of_Paragraph[i]);
    }
    return 0;
}

//calculates the density of all paragraphs and an returns the value
//void density_of_All_Paragraphs(){}

// divies paragraph weight with the same paragraphs length, to find density form 0 to 1
void paragraph_Density(int Weight, int Length, double* density){
    printf("    weight: %d, length: %d\n", Weight, Length);
    *density = ((double)Weight)/((double)Length);
}

//Checks for how many times a paragraph matches keywords
int paragraph_Weight(char Paragraph[][MAX_LETTERS], char Keywords[][MAX_LETTERS], int length){
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
        word_Match = 1;
        return(word_Match);
    }
    else if(word_Match != 0){
        word_Match = 0;
        return(word_Match);
    }
}




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