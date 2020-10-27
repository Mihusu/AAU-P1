#include <stdio.h>
#include <stdlib.h>

/*
The function should convert it a LaTeX file
*/
void LaTeX(char ConLaTeX[]) {
    
    printf("Write down the name of your file");
    scanf("%c", ConLaTeX[]);

    if(ConLaTeX[] <= 0) {
        printf("could not create a file");
        exit(EXIT_FAILURE);
    }

}

int formaliaInLaTeX(preamble, beginText, thePlainText) {
    
    LaTeX(thePlainText);
    preamble;
    beginText;

    return preamble && beginText;
}

int contents(education, workExperience, freeText) {

    if(education) {

    }
    
    if(workExperience) {

    }

    if(freeText) {

    }

    return education && workExperience && freeText;
}