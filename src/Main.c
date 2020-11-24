#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "filter.c"
#include "testingRead.c" //testing to be replaced by full version
//#include "format.c"

int main(void){
    printf("########  ########   #######        ## ########  ######  ########    ##     ## #### ########    ###\n##     ## ##     ## ##     ##       ## ##       ##    ##    ##       ##     ##  ##     ##      ## ##   \n##     ## ##     ## ##     ##       ## ##       ##          ##       ##     ##  ##     ##     ##   ##  \n########  ########  ##     ##       ## ######   ##          ##       ##     ##  ##     ##    ##     ## \n##        ##   ##   ##     ## ##    ## ##       ##          ##        ##   ##   ##     ##    ######### \n##        ##    ##  ##     ## ##    ## ##       ##    ##    ##         ## ##    ##     ##    ##     ## \n##        ##     ##  #######   ######  ########  ######     ##          ###    ####    ##    ##     ## \n");
    //wordsinsections tells how many words in each paragraph/section. section count is total section numbers.
    int sectionsCount, *wordsInSections, i, j;
    char *fullText, ***theSectionsOut;
    FILE *theFileIn = fopen("Long.txt", "r");
    text_reader(theFileIn, &fullText);
    printf("\nchars total: %d\n", strlen(fullText));
    section_treater(fullText, &theSectionsOut, &sectionsCount, &wordsInSections);
    printf("Number of sections: %d\n", sectionsCount);
    //===============================================read ^^ filter vv =============================0
    char *buzz[KEYWORD_LENGTH] = {"elektronik","c#","java","gym","c","prog","css","databaser","python","statistik","sandsynlighedsteori","machinelearning","bsc","software"}; //testing, tb replace by read.c

    double *density_of_paragraph = calloc(sectionsCount,sizeof(double)); //defines a density for each sections/paragraph
    calculate_cv_density(density_of_paragraph,theSectionsOut,buzz,wordsInSections,sectionsCount);
    bool *included_paragraphs = calloc(sectionsCount,sizeof(bool)); //defines an array of which paragraphs/sections should be included
    include_paragraph(density_of_paragraph,theSectionsOut,wordsInSections,included_paragraphs,sectionsCount);
    for (int i = 0; i < sectionsCount; i++){
        printf("(%d). density: %lf, include? %d\n",i,density_of_paragraph[i],included_paragraphs[i]);
    }
    
    char *filtered_cv; //makes a dynamic variable to later be malloced to be used to dynamically change length/words in new cv
    generate_cv(&filtered_cv,included_paragraphs,theSectionsOut,sectionsCount,wordsInSections);
    
    printf("\nOutput: %s\n", filtered_cv);
    FILE *fp = fopen("CV.tex", "w"); // Creates a file
   
    if (fp == NULL) { 
        printf("Cannot open file \n"); 
        exit(EXIT_FAILURE); 
    } 

    //fgets(filtered_cv, sizeof(filtered_cv), stdin);
    fprintf(fp, "output: %s\n", filtered_cv);
    fclose(fp);

    /*char received_string[20000]; 
    for (i = 0; filtered_cv[i]!='\0'; i++) {
        // Input string into the file 
        // single character at a time 
        fputc(filtered_cv[i], fp); 
    } 
    // Reading the string from file 
    fgets(received_string, 20000, fp); */

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