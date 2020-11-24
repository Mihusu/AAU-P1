#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KEYWORD_LENGTH 12 //amount of keywords in array
#define PARA_AMOUNT 6     //amount of paragraphs
#define PARA_LENGTH 12    //length of each paragraph

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
    fp = fopen("D:\\Skole\\Universitet\\1_semester\\P1\\AAU_P1\\docs\\CV.tex", "w+"); // Creates a file
    fprintf(fp, "%s %s %s %d", "We", "LORT", "in", 2012);
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