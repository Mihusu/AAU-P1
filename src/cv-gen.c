#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define KEYWORD_LENGTH 12 //amount of keywords in array
#define PARA_AMOUNT 6 //amount of paragraphs
#define PARA_LENGTH 12 //length of each paragraph

bool is_word_match();
int paragraph_Weight();
void paragraph_Density();
void cv_Density();

int main(void){
    char *CV[PARA_AMOUNT][PARA_LENGTH] = {{"Jeg","har","en","gym","uddannelse"}, //testing, tb replace by read.c
                                            {"jeg","har","arbejdet","i","netto"},
                                            {"Jeg","er","god","til","C","prog"},
                                            {"Jeg","kan","finde","ud","af","machinelearning","og","statistik","og","sandsynlighedsteori"},
                                            {"Jeg","tager","en","Bsc","i","Software"},
                                            {"Erfaring","med","C","python","css","og","databaser"}};
    
    char *buzz[KEYWORD_LENGTH] = {"netto","gym","C","prog","css","databaser","python","statistik","sandsynlighedsteori","machinelearning","Bsc","Software"}; //testing, tb replace by read.c
    int length[PARA_AMOUNT] = {5,5,6,10,6,7}; //length of each individuel paragraph //testing, tb replace by read.c
    double density_of_Paragraph[PARA_AMOUNT];
    cv_Density(density_of_Paragraph,CV,buzz,length);

    printf("\n\n1: %lf 2:%lf 3:%lf 4:%lf 5:%lf 6: %lf",density_of_Paragraph[0],density_of_Paragraph[1],density_of_Paragraph[2],density_of_Paragraph[3],density_of_Paragraph[4],density_of_Paragraph[5]);
    printf("\n\n%d",strlen(CV[0][1]));
    return 0;
}

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