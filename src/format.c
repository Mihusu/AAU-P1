#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filter.c"

void formaliaInLaTeX(char *array_text);

int main(void)
{
    char *filter_text;
    formaliaInLaTeX(filter_text);
    return 0;
}

/*
This function will make some modification for the plain text like structure, layout, font etc.
The function should also convert a plain text into a LaTeX file
*/
void formaliaInLaTeX(char *array_text)
{
    FILE *fp;
    char c;
    fp = fopen("D:\\Skole\\Universitet\\1_semester\\P1\\AAU_P1\\docs\\CV.tex", "w+"); // Creates a file 
    fprintf(fp, "%s", "hej");
}

void output(char *array_text) {

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