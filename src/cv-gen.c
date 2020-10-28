#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LETTERS 50 //PARAGRAPH_MAX_LETTERS_PER_WORD
#define PARA_LENGTH 0 //the array position of the length of paragraph n
#define KEYWORD_LENGTH 6 //amount of keywords in array

bool is_word_match(char word_1[], char word_2[]);
int paragraph_Weight(char Paragraph[][MAX_LETTERS], char Keywords[][MAX_LETTERS], int length[]);
double paragraph_Density(int Weight, int Length[]);

int main(void){
    char paragraph1[5][MAX_LETTERS] = {"hej","hvordan","gaar","det","asd"}; //testing, tb replace by read.c
    char buzz[KEYWORD_LENGTH][MAX_LETTERS] = {"hej","hvordan","gaar","det","med","sig"}; //testing, tb replace by read.c
    int length[5] = {5,2,3,4,5}; //testing, tb replace by read.c
    
    printf("%lf",paragraph_Density(paragraph_Weight(paragraph1,buzz,length),length)); 

    return 0;
}

// divies paragraph weight with the same paragraphs length, to fin density form 0 to 1
double paragraph_Density(int Weight, int Length[]){
    double Density = ((double)Weight)/((double)Length[PARA_LENGTH]);
    return(Density);
}

//Checks for how many times a paragraph matches keywords
int paragraph_Weight(char Paragraph[][MAX_LETTERS], char Keywords[][MAX_LETTERS], int length[]){
    int match_Weight = 0;
    for(int j = 0; j < KEYWORD_LENGTH; j++)
    {  
        int i = 0;
        for(; i < length[PARA_LENGTH]; i++)
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