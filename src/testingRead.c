
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void text_reader();
void worder();
void section_treater();


void text_reader(FILE *theFile, char **outText_pp){
    // Read all text from the file
    int characters = 0, alottetArray = 300;
    char *theText_p = malloc(alottetArray * sizeof(char));
    if(theText_p == NULL){
        // Error can't allocate memmory
        printf("\nError m allo, in text_reader\n"); // Temp remove later
        exit(EXIT_FAILURE);
    }
    while(1){
        if(characters >= alottetArray){
            alottetArray += 100;
            theText_p = (char *) realloc(theText_p, alottetArray * sizeof(char));
            if(theText_p == NULL){
                // Error can't reallocate new memmory
                printf("\nError m re allo, in text_reader\n"); // Temp remove later
                exit(EXIT_FAILURE);
            }
        }
        // Reads the next char from the file
        theText_p[characters] = fgetc(theFile);

        // End Of File was reatched
        if(theText_p[characters] == EOF){
            theText_p[characters] = '\0';
            break;
        }
        characters++;
    }
    if(characters == 0){
        // Error file is empty
        printf("\nError file is empty, in text_reader\n"); // Temp remove later
        exit(EXIT_FAILURE);
    }
    // Redo the char array to have correct size
    theText_p = (char *) realloc(theText_p, (characters + 1) * sizeof(char));
    if(theText_p == NULL){
        // Error can't reallocate new memmory, for the final string
        printf("\nError m allo end, in text_reader\n"); // Temp remove later
        exit(EXIT_FAILURE);
    }
    
    // Returning the variables
    *outText_pp = theText_p;

    // Placement here instead of file_read: needs testing
    fclose(theFile);
}


void worder(char *cleanText_p, char ***wordsOut_ppp, int *nWordsOut_p){
    // Seperates a string text into a array of strings containing individual words
    int nTheWords = 0, nWordsSpace = 30, currentChar = 0, wordStart = 0, i;
    char **theWords_pp = malloc(nWordsSpace * sizeof(char *));
    if(theWords_pp == NULL){
        // Error can't allocate memmory
        printf("\nError m allo, in worder, for words\n"); // Temp remove later
        exit(EXIT_FAILURE);
    }
    while(1){
        // Handeling of " \0" and "\n\0" lead to while(1) rather than while(cleanText_p[currentChar] == '\0')
        if(cleanText_p[currentChar] == ' ' || cleanText_p[currentChar] == '\n' || cleanText_p[currentChar] == '\0'){
            if(currentChar != wordStart){
                if(nTheWords >= nWordsSpace){
                    nWordsSpace += 10;
                    theWords_pp = (char **) realloc(theWords_pp, nWordsSpace * sizeof(char *));
                    if(theWords_pp == NULL){
                        // Error can't reallocate memmory
                        printf("\nError m re allo, in worder\n"); // Temp remove later
                        exit(EXIT_FAILURE);
                    }
                }
                char *aWord_p = malloc((currentChar - wordStart + 1) * sizeof(char));
                if(aWord_p == NULL){
                    // Error can't allocate memmory
                    printf("\nError m allo, in worder, for a word\n"); // Temp remove later
                    exit(EXIT_FAILURE);
                }
                // Alternative to strncpy(), strncpy() needs second argument to be const char *
                // New knowlege: char * --> const char *, is ok, work already done so why change
                for(i = wordStart; i < currentChar; i++){
                    aWord_p[i - wordStart] = cleanText_p[i];
                }
                aWord_p[currentChar - wordStart] = '\0';
                theWords_pp[nTheWords] = aWord_p;
                nTheWords++;
            }
            if(cleanText_p[currentChar] == '\0'){
                break;
            }
            wordStart = currentChar + 1;
        }
        currentChar++;
    }
    *wordsOut_ppp = theWords_pp;
    *nWordsOut_p = nTheWords;
}


void section_treater(char *theFreeText_p, char ****theSections_pppp, int *theNSections_p, int **theNWordSections_pp){
    int theReader = 0, currentMarker = -1, nSections = 1, nSectAllo = 10, i;
    char **theSectionsTemp_pp = malloc(nSectAllo * sizeof(char *));
    if(theSectionsTemp_pp == NULL){
        exit(EXIT_FAILURE);
    }
    theSectionsTemp_pp[0] = theFreeText_p;
    while(theFreeText_p[theReader] != '\0'){
        if(theReader == currentMarker && theFreeText_p[theReader] == '\n' && theFreeText_p[theReader + 1] != '\0'){
            if(nSections >= nSectAllo){
                nSectAllo += 10;
                theSectionsTemp_pp = (char **) realloc(theSectionsTemp_pp, nSectAllo * sizeof(char *));
                if(theSectionsTemp_pp == NULL){
                    exit(EXIT_FAILURE);
                }
            }
            theFreeText_p[theReader - 1] = '\0';
            theSectionsTemp_pp[nSections] = &(theFreeText_p[theReader + 1]);
            nSections++;
        } else if(theFreeText_p[theReader] == '\n'){
            currentMarker = theReader + 1;
        }
        theReader++;
    }
    char ***finalSections_ppp = malloc(nSections * sizeof(char **));
    int *wordsInSections_p = malloc(nSections * sizeof(int));
    if(finalSections_ppp == NULL || wordsInSections_p == NULL){
        exit(EXIT_FAILURE);
    }
    for(i = 0; i < nSections; i++){
        worder(theSectionsTemp_pp[i], &(finalSections_ppp[i]), &(wordsInSections_p[i]));
    }
    free(theSectionsTemp_pp);
    *theSections_pppp = finalSections_ppp;
    *theNSections_p = nSections;
    *theNWordSections_pp = wordsInSections_p;
}