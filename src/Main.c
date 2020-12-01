#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include "filter.c"
#include "levenshtein.c"
#include "testingRead.c" //testing to be replaced by full version
//#include "format.c"

/*
This program reads the input cv and keyword and requirements, filterets it 
and outputs the new CV as a latex document.

Project done by Ming Sun, David Rasmusen, Mikkel Kaa, Hans Heje
*/

int main(void){
    printf("########  ########   #######        ## ########  ######  ########    ##     ## #### ########    ###\n##     ## ##     ## ##     ##       ## ##       ##    ##    ##       ##     ##  ##     ##      ## ##   \n##     ## ##     ## ##     ##       ## ##       ##          ##       ##     ##  ##     ##     ##   ##  \n########  ########  ##     ##       ## ######   ##          ##       ##     ##  ##     ##    ##     ## \n##        ##   ##   ##     ## ##    ## ##       ##          ##        ##   ##   ##     ##    ######### \n##        ##    ##  ##     ## ##    ## ##       ##    ##    ##         ## ##    ##     ##    ##     ## \n##        ##     ##  #######   ######  ########  ######     ##          ###    ####    ##    ##     ## \n");
    //wordsinsections tells how many words in each paragraph/section. section count is total section numbers.
    int sections_count, *words_in_sections, i, j, keyword_count;
    char *full_text, **keywords, ***sections_out;
    FILE *freetext_file_in = fopen("Long.txt", "r");
    FILE *keyword_file_in = fopen("Keywords.txt", "r");
    text_reader(freetext_file_in, &full_text);
    section_treater(full_text, &sections_out, &sections_count, &words_in_sections);
    free(full_text);
    text_reader(keyword_file_in, &full_text);
    worder(full_text,&keywords,&keyword_count);
    free(full_text);
    double *density_of_section = calloc(sections_count,sizeof(double)); //defines a density for each sections/paragraph
    char *filtered_cv; //makes a dynamic variable to later be malloced to be used to dynamically change length/words in new cv
    bool *included_sections = calloc(sections_count,sizeof(bool)); //defines an array of which paragraphs/sections should be included

    remove_personal_pronouns(words_in_sections,sections_count,sections_out);
    calculate_text_density(sections_out,keywords,words_in_sections,sections_count,keyword_count,density_of_section);
    include_section(density_of_section,sections_out,words_in_sections,sections_count,included_sections);
    generate_text(included_sections,sections_out,sections_count,words_in_sections,&filtered_cv);
    
    printf("\n\n%s\n", filtered_cv);
    //run_pdfLaTeX(filtered_cv);
    //output_LaTeX_essential_contents(general_information, education, work_experience);   // SKAL BRUGES. M.I.S

    printf("keywords:");
    for (int i = 0; i < keyword_count; i++)
    {
        printf("%s, ",keywords[i]);
    }
    
    printf("\n\nBool value -- Section ID -- Section Density -- Section Text\n");
    for (int i = 0; i < sections_count; i++)
    {
        
        printf("\n[%d] (%d): %lf -- ",included_sections[i],i,density_of_section[i]);
    
            for (int j = 0; j < words_in_sections[i]; j++)
        {
            printf("%s ",sections_out[i][j]);
        }
    }
    
    //free variables
    free(density_of_section);
    free(included_sections);
    free(filtered_cv); //freeinng variables
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