#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "filter.c"

int main(void){
    printf("########  ########   #######        ## ########  ######  ########    ##     ## #### ########    ###\n##     ## ##     ## ##     ##       ## ##       ##    ##    ##       ##     ##  ##     ##      ## ##   \n##     ## ##     ## ##     ##       ## ##       ##          ##       ##     ##  ##     ##     ##   ##  \n########  ########  ##     ##       ## ######   ##          ##       ##     ##  ##     ##    ##     ## \n##        ##   ##   ##     ## ##    ## ##       ##          ##        ##   ##   ##     ##    ######### \n##        ##    ##  ##     ## ##    ## ##       ##    ##    ##         ## ##    ##     ##    ##     ## \n##        ##     ##  #######   ######  ########  ######     ##          ###    ####    ##    ##     ## \n");
    char *cv[PARA_AMOUNT][PARA_LENGTH] = {{"Jeg","har","en","gym","uddannelse"}, //testing, tb replace by read.c
                                            {"jeg","har","arbejdet","i","netto"},
                                            {"Jeg","er","god","til","C","prog"},
                                            {"Jeg","kan","finde","ud","af","machinelearning","og","statistik","og","sandsynlighedsteori"},
                                            {"Jeg","tager","en","Bsc","i","software"},
                                            {"Erfaring","med","C","python","css","og","databaser"}};
    char *buzz[KEYWORD_LENGTH] = {"netto","gym","C","prog","css","databaser","python","statistik","sandsynlighedsteori","machinelearning","Bsc","Software"}; //testing, tb replace by read.c
    int length[PARA_AMOUNT] = {5,5,6,10,6,7}; //length of each individuel paragraph //testing, tb replace by read.c
    double density_of_paragraph[PARA_AMOUNT] = {};
    calculate_cv_density(density_of_paragraph,cv,buzz,length);
    bool included_paragraphs[PARA_AMOUNT] = {};
    include_paragraph(density_of_paragraph,cv,length,included_paragraphs);
    char *filtered_cv[OUTPUT_PARA_AMOUNT][PARA_LENGTH] = {};
    generate_cv(filtered_cv,included_paragraphs,cv);

    //testing started
    for(int i = 0; i < PARA_AMOUNT; i++){
        printf("(%d) density: %lf included?: %d \n",i+1,density_of_paragraph[i],included_paragraphs[i]); //testing
    }
    printf("\n");
    for (int i = 0; i < PARA_AMOUNT; i++) //print input cv.
    {
        printf("input CV paragraph [%d] ",i+1);
        for (int j = 0; j < PARA_LENGTH; j++)
        {
            printf("%s ", cv[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    for (int i = 0; i < OUTPUT_PARA_AMOUNT; i++) //print output cv.
    {
        printf("output CV paragraph [%d] ",i+1);
        for (int j = 0; j < PARA_LENGTH; j++)
        {
            printf("%s ", filtered_cv[i][j]);
        }
        printf("\n");
    }
    //testing ended
    return 0;
}
