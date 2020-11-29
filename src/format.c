#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 

void output_capitalized(char *capitalized_text) {
    int marker_index = -1;
    //Calculating length.
    int length = strlen(capitalized_text);
    // Capitalized the first paragraph for the first letter  
    *capitalized_text = toupper(*capitalized_text);
    // This will capitalize for other scenarios
    for(int i = 1; i < length - 1; i++) { // length should go -1 because of the '.'
        if(marker_index == i && (capitalized_text[i] == '\n' || capitalized_text[i] == ' ')) {
            // Capitalized the next letter
            capitalized_text[i+1] = toupper(capitalized_text[i+1]);
        } 
        else if(capitalized_text[i] == '.' || capitalized_text[i] == '?' || capitalized_text[i] == '!') {
            marker_index = i + 1;
        }
    }
}

/*
This function will make some modification for the plain text like structure, layout, font etc.
The function should also convert a plain text into a LaTeX format.
*/
void output_general_contents(FILE *general_CV) { //char *array_general_information,  FILE *Picture
    //output_capitalized(array_general_information);
    fprintf(general_CV,"\\begin{minipage}[b]{0.45\\textwidth} \n\\subsubsection*{General information}\n Name: David Vinje \n\n Address: Islands brygge 56b 1tv \n\n Zip nr. 2300 Koebenhavn S \n\n Phone number: 26325635 \n\n E-mail: david2300@hotmail.com \n\n Country: Danmark \n\n Date of birth: 11/06/1995 \n \\end{minipage}\n \\hfill");
    //fprintf(general_CV,"\\section*{General information}\n%s\n", array_general_information);
}

/* Load a picture to the CV. That can be essential for the recruiter. */
void output_picture(FILE *picture) {
    //Put your picture here after the phrase figures/...
    // This figure can be adjusted, so it will be at the right side of the CV
    fprintf(picture, "\n\\begin{minipage}[b]{3cm} \\includegraphics[height=4cm]{figures/1200px-Drottning_Margrethe_av_Danmark} \\end{minipage}\n");
}

void output_essential_contens(char ***array_essential_contents, int n, int *amount_of_itemized, FILE *essenctial_CV) {
    for(int i = 0; i < n; i++) {
        // The print is going to start at index 0, because of 'i' is going to start at 0.
        fprintf(essenctial_CV, "\\section*{%s}\n\\begin{itemize}[label=$\\ast$]\n", array_essential_contents[i][0]);
        for(int j = 1; j < amount_of_itemized[i]; j++) {
            fprintf(essenctial_CV, "\\item %s\n", array_essential_contents[i][j]);
        }
        fprintf(essenctial_CV, "\\end{itemize}\n");
    }    
}

/*
If there is text to one, two, three or more categories then the function will make the
text more beautiful and readable
*/
void output_LaTeX_free_text(char *array_free_text, FILE *free_text_CV) {
    output_capitalized(array_free_text);
    // Prints out the free text that has been filtered to the CV.tex file.
    fprintf(free_text_CV,"\n\\section*{Free text}\n%s\n", array_free_text);
}

void run_pdfLaTeX(/*char *run_general_info, char ***run_essential_info,*/ char *run_free_text) {
    FILE *final_CV = fopen(".\\..\\docs\\CV.tex", "w");
    if(final_CV == NULL) { 
        printf("Cannot open file\n"); 
        exit(EXIT_FAILURE); 
    }
    output_general_contents(final_CV);
    output_picture(final_CV);
    //output_essential_contens(run_essential_info, final_CV);
    output_LaTeX_free_text(run_free_text, final_CV);
    fclose(final_CV);
}