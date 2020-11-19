#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "format.h"

#define MAX_CHARACTER 100
void formaliaInLaTeX(char *plaintext);

int main(void) {
    char *filter_text;
    formaliaInLaTeX(filter_text);
    return 0;
}

/*
This function will make some modification for the plain text like structure, layout, font etc.
The function should also convert a plain text into a LaTeX file
*/

void formaliaInLaTeX(char *plaintext) {
    FILE *fp; 
    FILE * preamble;
    FILE * main_tex;

    fp = fopen("D:\\Skole\\Universitet\\1_semester\\P1\\AAU_P1\\docs\\CV.tex", "w"); // Creates a file
    preamble = fopen("D:\\Skole\\Universitet\\1_semester\\P1\\AAU_P1\\docs\\preliminaries\\preamble.tex", "r");
    if(preamble == NULL){
        printf("\nError can't open input file(s)\n"); // temp remove later
        exit(EXIT_FAILURE);
    }
    main_tex = fopen("D:\\Skole\\Universitet\\1_semester\\P1\\AAU_P1\\docs\\main_test.tex", "r");
    fprintf(fp,"%s %s %s %d", "We", "are", "in", 2012);
}

/*
If there is text to one, two, three or more categories then the function will make the
text more beautiful and readable
*/
/*
int contents(education, workExperience, freeText) {

    if(education) {
        // Make bulletpoints for the text
        printf("* ");
    }
    
    if(workExperience) {
        // Make bulletpoints for the text
        printf("* ");

    }

    if(freeText) {

    }

    return education && workExperience && freeText;
}*/