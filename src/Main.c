#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "filter.c"
#include "testingRead.c" //testing to be replaced by full version

int main(void){
    printf("########  ########   #######        ## ########  ######  ########    ##     ## #### ########    ###\n##     ## ##     ## ##     ##       ## ##       ##    ##    ##       ##     ##  ##     ##      ## ##   \n##     ## ##     ## ##     ##       ## ##       ##          ##       ##     ##  ##     ##     ##   ##  \n########  ########  ##     ##       ## ######   ##          ##       ##     ##  ##     ##    ##     ## \n##        ##   ##   ##     ## ##    ## ##       ##          ##        ##   ##   ##     ##    ######### \n##        ##    ##  ##     ## ##    ## ##       ##    ##    ##         ## ##    ##     ##    ##     ## \n##        ##     ##  #######   ######  ########  ######     ##          ###    ####    ##    ##     ## \n");
    //wordsinsections tells how many words in each paragraph/section. section count is total section numbers.
    int sectionsCount, *wordsInSections, i, j;
    char *fullText, ***theSectionsOut;
    FILE *theFileIn = fopen("Hello.txt", "r");
    text_reader(theFileIn, &fullText);
    printf("\nchars total: %d\n", strlen(fullText));
    section_treater(fullText, &theSectionsOut, &sectionsCount, &wordsInSections);
    printf("Number of sections: %d\n", sectionsCount);
    //===============================================read ^^ filter vv =============================0
    char *buzz[KEYWORD_LENGTH] = {"netto","gym","C","prog","css","databaser","python","statistik","sandsynlighedsteori","machinelearning","Bsc","Software"}; //testing, tb replace by read.c

    double *density_of_paragraph = calloc(sectionsCount,sizeof(double)); //defines a density for each sections/paragraph
    calculate_cv_density(density_of_paragraph,theSectionsOut,buzz,wordsInSections,sectionsCount);
    bool *included_paragraphs = calloc(sectionsCount,sizeof(bool)); //defines an array of which paragraphs/sections should be included
    include_paragraph(density_of_paragraph,theSectionsOut,wordsInSections,included_paragraphs,sectionsCount);
    
    char *filtered_cv; //makes a dynamic variable to later be malloced to be used to dynamically change length/words in new cv
    generate_cv(&filtered_cv,included_paragraphs,theSectionsOut,sectionsCount,wordsInSections);

    printf("output: %s ", filtered_cv);
    //testing read started again, to free variables
    free(filtered_cv); //freeinng variables
    free(fullText);
    for(i = 0; i < sectionsCount; i++){
        //printf("Section: %d, words in section: %d\n", i, wordsInSections[i]);
        for(j = 0; j < wordsInSections[i]; j++){
            //printf("\n%s", theSectionsOut[i][j]);
            free(theSectionsOut[i][j]);
        }
        free(theSectionsOut[i]);
    }
    free(wordsInSections);
    free(theSectionsOut);

    return 0;
}