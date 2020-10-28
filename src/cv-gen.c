#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int CV_LENGTH = 5;
int KEYWORD_LENGTH = 5;
int max_word_count = 700;
int min_word_count = 500;  //change at a later stage, to the req.txt

bool is_word_match(char word_1[], char word_2[]);
int paragraph_Matches(char Paragraph[][50], char Keywords[][50]);
int paragraph_Length(char paragraph[][50]);
int paragraph_Importance(char paragraph[][]);


int main(void){
    char cv[4][50] = {"hej","hvordan","gaar","det"};
    char buzz[3][50] = {"hej","hvordan","gaar"};
    printf("%d",paragraph_Matches(cv,buzz));
    return 0;
}

//Checks for how many times a paragraph matches keywords
int paragraph_Matches(char Paragraph[][50], char Keywords[][50]){    
    int match_Weight = 0;
    for(int j = 0; j < 3; j++)  //need sizeof command instead of 3 //buzz length
    {  
        int i = 0;
        for(; i < 4; i++) //need sizeof instead of 4, length of cv
        {
            printf("cv[%d]: %s, buzz[%d]: %s\n ",i,Paragraph[i],j,Keywords[j]);
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
        printf("-----is_Word_Match end, T: %d-----\n\n",word_Match); //debug
        return(word_Match);
    }
    else if(word_Match != 0){
        word_Match = 0;
        printf("-----is_Word_Match end, T: %d-----\n\n",word_Match); //debug
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