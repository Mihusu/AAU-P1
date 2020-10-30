#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>



int main(void){
    bool important_text;
    int max_word_count_CV;
    double strArr_density_CV[] = {8, 32, 46, 3, 93, 43, 12, 72};
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
    inclusion(strArr_density_CV, max_word_count_CV, &important_text);
    return 0;
}
