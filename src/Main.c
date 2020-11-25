#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "filter.c"
#include "testingRead.c" //testing to be replaced by full version
#include "format.c"

int main(void){
    printf("########  ########   #######        ## ########  ######  ########    ##     ## #### ########    ###\n##     ## ##     ## ##     ##       ## ##       ##    ##    ##       ##     ##  ##     ##      ## ##   \n##     ## ##     ## ##     ##       ## ##       ##          ##       ##     ##  ##     ##     ##   ##  \n########  ########  ##     ##       ## ######   ##          ##       ##     ##  ##     ##    ##     ## \n##        ##   ##   ##     ## ##    ## ##       ##          ##        ##   ##   ##     ##    ######### \n##        ##    ##  ##     ## ##    ## ##       ##    ##    ##         ## ##    ##     ##    ##     ## \n##        ##     ##  #######   ######  ########  ######     ##          ###    ####    ##    ##     ## \n");
    //wordsinsections tells how many words in each paragraph/section. section count is total section numbers.
    int sectionsCount, *wordsInSections, i, j;
    char *fullText, ***theSectionsOut;
    char *filtered_cv; //makes a dynamic variable to later be malloced to be used to dynamically change length/words in new cv
    FILE *theFileIn = fopen("Long.txt", "r");
    FILE *CV_education_and_work_experience = fopen("LongCV.txt", "r");
    text_reader(theFileIn, &fullText);
    printf("\nchars total: %d\n", strlen(fullText));
    section_treater(fullText, &theSectionsOut, &sectionsCount, &wordsInSections);
    printf("Number of sections: %d\n", sectionsCount);
    
    /*============================ read ^^ filter vv =============================*/
    char *buzz[KEYWORD_LENGTH] = {"elektronik","c#","java","gym","c","prog","css","databaser","python","statistik","sandsynlighedsteori","machinelearning","bsc","software"}; //testing, tb replace by read.c

    double *density_of_paragraph = calloc(sectionsCount,sizeof(double)); //defines a density for each sections/paragraph
    calculate_cv_density(density_of_paragraph,theSectionsOut,buzz,wordsInSections,sectionsCount);
    bool *included_paragraphs = calloc(sectionsCount,sizeof(bool)); //defines an array of which paragraphs/sections should be included
    include_paragraph(density_of_paragraph,theSectionsOut,wordsInSections,included_paragraphs,sectionsCount);
    for (int i = 0; i < sectionsCount; i++){
        printf("(%d). density: %lf, include %d\n",i,density_of_paragraph[i],included_paragraphs[i]);
    }
    generate_cv(&filtered_cv,included_paragraphs,theSectionsOut,sectionsCount,wordsInSections);
    
    printf("\n%s\n", filtered_cv);
    output_LaTeX_free_text(filtered_cv);
    //output_LaTeX_essential_contents(general_information, education, work_experience);   // SKAL BRUGES. M.I.S

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