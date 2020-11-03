#ifndef P1_SRC_READ_H
#define P1_SRC_READ_H

#include <stdio.h>

int main(void);

void start_read(char ***theKeywords_ppp, char ****cvLongItemiced_pppp,
                char ****cvLongSections_pppp);

void text_reader(FILE *theFile, char **outText_pp, int *outLength_p);

void word_reader(FILE *theInFile, char ***theOutput_ppp);

/*
void arrayExtender(char ***theIn_ppp, int currLength){
    // Adds an extra entry to the array
    char **theNew_pp = malloc((currLength + 10) * sizeof(char *));
    for(int i = 0; i < currLength; i++){
        theNew_pp[i] = (*theIn_ppp)[i];
    }
    free(*theIn_ppp);
    *theIn_ppp = theNew_pp;
}// */

void **arrayExtenderExperimental(void **theIn_pp, int currLength);

void tag_searcher(FILE *fileInbound, char ****theItems_pppp,
                  char ****theText_pppp);

void line_reader();

#endif  // P1_SRC_READ_H
