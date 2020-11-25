#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include "filter.c"
#include "testingRead.c" //testing to be replaced by full version
#include "format.c"

/*
This program reads the input cv and keyword and requirements, filterets it 
and outputs the new CV as a latex document.

Project done by Ming Sun, David Rasmusen, Mikkel Kaa, Hans Heje
*/

int main(void){
    printf("########  ########   #######        ## ########  ######  ########    ##     ## #### ########    ###\n##     ## ##     ## ##     ##       ## ##       ##    ##    ##       ##     ##  ##     ##      ## ##   \n##     ## ##     ## ##     ##       ## ##       ##          ##       ##     ##  ##     ##     ##   ##  \n########  ########  ##     ##       ## ######   ##          ##       ##     ##  ##     ##    ##     ## \n##        ##   ##   ##     ## ##    ## ##       ##          ##        ##   ##   ##     ##    ######### \n##        ##    ##  ##     ## ##    ## ##       ##    ##    ##         ## ##    ##     ##    ##     ## \n##        ##     ##  #######   ######  ########  ######     ##          ###    ####    ##    ##     ## \n");
    //wordsinsections tells how many words in each paragraph/section. section count is total section numbers.
    int sections_count, *words_in_sections, i, j, keyword_count;
    char *full_text, ***sections_out;
    char **keywords;
    FILE *freetext_file_in = fopen("Long.txt", "r");
    FILE *keyword_file_in = fopen("Keywords.txt", "r");
    text_reader(freetext_file_in, &full_text);
    section_treater(full_text, &sections_out, &sections_count, &words_in_sections);
    free(full_text);
    text_reader(keyword_file_in, &full_text);
    worder(full_text,&keywords,&keyword_count);
    free(full_text);
    double *density_of_paragraph = calloc(sections_count,sizeof(double)); //defines a density for each sections/paragraph
    char *filtered_cv; //makes a dynamic variable to later be malloced to be used to dynamically change length/words in new cv
    bool *included_paragraphs = calloc(sections_count,sizeof(bool)); //defines an array of which paragraphs/sections should be included

    remove_personal_pronouns(words_in_sections,sections_count,sections_out);
    calculate_text_density(sections_out,keywords,words_in_sections,sections_count,keyword_count,density_of_paragraph);
    include_section(density_of_paragraph,sections_out,words_in_sections,sections_count,included_paragraphs);
    generate_text(included_paragraphs,sections_out,sections_count,words_in_sections,&filtered_cv);
    
    printf("\n%s\n", filtered_cv);
    output_LaTeX_free_text(filtered_cv);
    //output_LaTeX_essential_contents(general_information, education, work_experience);   // SKAL BRUGES. M.I.S

    //testing read started again, to free variables
    free(density_of_paragraph);
    free(included_paragraphs);
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