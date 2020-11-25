#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 

void output_capitalized(char *capitalized_text) {
    //Calculating length.
    int marker_index = -1;
    int length = strlen(capitalized_text);
    *capitalized_text = toupper(*capitalized_text);
    for(int i = 1; i < length-1; i++) {
        if(marker_index == i && (capitalized_text[i] == '\n' || capitalized_text[i] == ' ')) {
            capitalized_text[i+1] = toupper(capitalized_text[i+1]);
        } else if(capitalized_text[i] == '.' || capitalized_text[i] == '?' || capitalized_text[i] == '!') {
            marker_index = i + 1;
        }
    }
}

/*
If there is text to one, two, three or more categories then the function will make the
text more beautiful and readable.
*/
void output_LaTeX_essential_contents(char *array_general_information, char ***array_essential_contents) {
    FILE *CV_contents = fopen(".\\..\\docs\\CV.tex", "w");
    if (CV_contents == NULL) { 
        printf("Cannot open file\n"); 
        exit(EXIT_FAILURE);
    }
}

/*
This function will make some modification for the plain text like structure, layout, font etc.
The function should also convert a plain text into a LaTeX file.
*/
void output_LaTeX_free_text(char *array_free_text) {
    FILE *CV_free_text = fopen(".\\..\\docs\\CV.tex", "w"); // Creates a file.
    if(CV_free_text == NULL) { 
        printf("Cannot open file\n"); 
        exit(EXIT_FAILURE); 
    }
}

void run_pdfLaTeX(char *run_general_info, char ***run_essential_info, int n, int *amount_of_itemized, char *run_free_text) {
    FILE *final_CV = fopen(".\\..\\docs\\CV.tex", "w");
    if(final_CV == NULL) { 
        printf("Cannot open file\n"); 
        exit(EXIT_FAILURE); 
    }
    output_capitalized(run_general_info);
    fprintf(final_CV,"\\section{General information}\n%s\n", run_general_info);
    for(int i = 0; i < n; i++) {
        fprintf(final_CV,"\\section{}\n%s\n", );
    }
    output_capitalized(run_free_text);
    // Prints out the free text that has been filtered to the CV.tex file.
    fprintf(final_CV,"\\section{Free text}\n%s\n", run_free_text);
    fclose(final_CV);
}