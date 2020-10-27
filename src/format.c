#include <stdio.h>
#include <stdlib.h>

/*
The function should convert a plain text into a LaTeX file
*/
void LaTeX(char ConLaTeX[]) {
    
    printf("Write down the name of your file");
    scanf("%c", ConLaTeX[]);

    if(ConLaTeX[] <= 0) {
        printf("could not create a file");
        exit(EXIT_FAILURE);
    }

}

/*
This function will make some modification for the plain text like structure, font etc.
*/
int formaliaInLaTeX(preamble, beginText, thePlainText) {
    
    LaTeX(thePlainText);
    preamble;
    beginText;

    return preamble && beginText;
}

/*
If there is text to one, two, three or more categories then the function will make the
text more beautiful and readable
*/
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
}