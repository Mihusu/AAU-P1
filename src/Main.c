#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include "filter.c"
#include "levenshtein.c"
#include "read.c"
#include "format.c"

/*
This program reads the input cv and keyword and requirements, filterets it 
and outputs the new CV as a latex document.

Project done by Ming Hui Sun, David Rasmusen, Mikkel Kaa, Hans Heje
*/

int main(void){
    printf("########  ########   #######        ## ########  ######  ########    ##     ## #### ########    ###\n##     ## ##     ## ##     ##       ## ##       ##    ##    ##       ##     ##  ##     ##      ## ##   \n##     ## ##     ## ##     ##       ## ##       ##          ##       ##     ##  ##     ##     ##   ##  \n########  ########  ##     ##       ## ######   ##          ##       ##     ##  ##     ##    ##     ## \n##        ##   ##   ##     ## ##    ## ##       ##          ##        ##   ##   ##     ##    ######### \n##        ##    ##  ##     ## ##    ## ##       ##    ##    ##         ## ##    ##     ##    ##     ## \n##        ##     ##  #######   ######  ########  ######     ##          ###    ####    ##    ##     ## \n");
    //wordsinsections tells how many words in each paragraph/section. section count is total section numbers.
    int sections_count, *words_in_sections, i, j, keyword_count;
    char *full_text, **keywords, ***sections_out;
    double *density_of_section = calloc(sections_count,sizeof(double)); //defines a density for each sections/paragraph
    char *cv_filtered_freetext; //makes a dynamic variable to later be malloced to be used to dynamically change length/words in new cv
    bool *included_sections = calloc(sections_count,sizeof(bool)); //defines an array of which paragraphs/sections should be included
    
    char **keywords_pp;
    int nKeywords; // Number of keywords

    char ***itemicedSections_ppp;
    int nItemices, *nItemicedContent_p; // Number of itemices, Number of items in eatch itemices

    char ***inCVSections_ppp;
    int nSections, *nSectionContent_p; // Number of freetext sections, Number of words in eatch section

    char *cvGeneralInfo_p;
    int initialWordCount;
    start_read(&keywords_pp, &nKeywords, &itemicedSections_ppp, &nItemices, &nItemicedContent_p, &inCVSections_ppp, &nSections, &nSectionContent_p, &cvGeneralInfo_p, &initialWordCount);
    // All rest of code here
    the_ending(keywords_pp, nKeywords, itemicedSections_ppp, nItemices, nItemicedContent_p, inCVSections_ppp, nSections, nSectionContent_p, cvGeneralInfo_p);

    remove_personal_pronouns(words_in_sections,sections_count,sections_out);
    calculate_text_density(sections_out,keywords,words_in_sections,sections_count,keyword_count,density_of_section);
    include_section(density_of_section,sections_out,words_in_sections,sections_count,included_sections);
    generate_text(included_sections,sections_out,sections_count,words_in_sections,&cv_filtered_freetext);
    
    printf("\n\n%s\n", cv_filtered_freetext);
    run_pdfLaTeX(cvGeneralInfo_p, itemicedSections_ppp, nItemices, nItemicedContent_p, cv_filtered_freetext);  // SKAL BRUGES. M.I.S

    printf("keywords:");
    for (int i = 0; i < keyword_count; i++) {
        printf("%s, ",keywords[i]);
    }
    
    printf("\n\nBool value -- Section ID -- Section Density -- Section Text\n");
    for (int i = 0; i < sections_count; i++) {
        
        printf("\n[%d] (%d): %lf -- ",included_sections[i],i,density_of_section[i]);
    
        for (int j = 0; j < words_in_sections[i]; j++) {
            printf("%s ",sections_out[i][j]);
        }
    }
    
    //free variables
    free(density_of_section);
    free(included_sections);
    free(cv_filtered_freetext); //freeinng variables
    for(i = 0; i < sections_count; i++){
        //printf("Section: %d, words in section: %d\n", i, words_in_sections[i]);
        for(j = 0; j < words_in_sections[i]; j++){
            //printf("\n%s", sections_out[i][j]);
            free(sections_out[i][j]);
        }
        free(sections_out[i]);
    }
    free(words_in_sections);
    free(sections_out);
    printf("Executed program correctly");
    return 0;
}