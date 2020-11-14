#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void start_read();
void tag_searcher();
void text_reader();
void line_reader();
void worder();
void section_treater();
void the_ending();


int main(void){

    char **keywords_pp;
    int nKeywords; // Number of keywords

    char ***itemicedSections_ppp;
    int nItemices, *nItemicedContent_p; // Number of itemices, Number of items in eatch itemices

    char ***inCVSections_ppp;
    int nSections, *nSectionContent_p; // Number of freetext sections, Number of words in eatch section

    start_read(&keywords_pp, &nKeywords, &itemicedSections_ppp, &nItemices, &nItemicedContent_p, &inCVSections_ppp, &nSections, &nSectionContent_p);
    // All rest of code here
    the_ending(keywords_pp, nKeywords, itemicedSections_ppp, nItemices, nItemicedContent_p, inCVSections_ppp, nSections, nSectionContent_p);
    return 0;
}


void start_read(char ***theKeywords_ppp, int *nKword_p, char ****cvLongItemiced_pppp, int *nItemices_p, int **nItemicedContent_pp, char ****cvLongSections_pppp, int *nSections_p, int **nSectionWords_pp){

    //char *fnLongCV = malloc(); // In case of user defined file name
    FILE *theLongCV, *theKeywords;
    char *cvTotalText_p, *keywordsTotalText_p;
    theLongCV = fopen("LongCV.txt", "r"); // Doing longCV first might have more consecutive space available if pc is low RAM
    theKeywords = fopen("Hello.txt", "r");
    if(theLongCV == NULL || theKeywords == NULL){
        // Error, can't open file.
        printf("\nError can't open input file(s)\n"); // temp remove later
        exit(EXIT_FAILURE);
    }

    text_reader(theLongCV, &cvTotalText_p);
    tag_searcher(cvTotalText_p, cvLongItemiced_pppp, cvLongSections_pppp);
    free(cvTotalText_p);

    text_reader(theKeywords, &keywordsTotalText_p);
    worder(keywordsTotalText_p, theKeywords_ppp, nKword_p);
    free(keywordsTotalText_p);

} 


void the_ending(char **theKeywords_pp, int nKword, char ***cvLongItemiced_ppp, int nItemices, int *nItemicedContent_p, char ***cvLongSections_ppp, int nSections, int **nSectionWords_p){
    int i, j;
    for(i = 0; i < nKword; i++){
        free(theKeywords_pp[i]);
    }
    free(theKeywords_pp);
    for(i = 0; i < nItemices; i++){
        for(j = 0; j < nItemicedContent_p[i]; j++){
            free(cvLongItemiced_ppp[i][j]);
        }
        free(cvLongItemiced_ppp[i]);
    }
    free(nItemicedContent_p);
    free(cvLongItemiced_ppp);
    for(i = 0; i < nSections; i++){
        for(j = 0; j < nSectionWords_p[i]; j++){
            free(cvLongSections_ppp[i][j]);
        }
        free(cvLongSections_ppp[i]);
    }
    free(nSectionWords_p);
    free(cvLongSections_ppp);
}


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
            // Change theText_p from char array to string
            theText_p[characters] = '\0';
            break;
        }
        // Easyer to handel in the rest of the code if there is no '\r'
        if(theText_p[characters] != '\r')
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


void tag_searcher(char *fileCleanText, char ****theItems_pppp, char ****theText_pppp){
    char ***theReadItems_ppp, ***theReadText_ppp;
    theReadItems_ppp = malloc(2 * sizeof(char **));
    theReadText_ppp = malloc(1 * sizeof(char **));
    
    
}


void line_reader(){



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

/* Exampel of LongCV conntent:
#Workexperience
2009-2011 Flaskedreng i Netto.
2011-2013 Flymekaniker.
#Education
2016 AAU Batchelor i software.
2013 HTX-Hillerød, Mat-Fys.
#FreeText
Hello I am a good worker.

I flush the toilet always.

Going home is for the weak.

I am very proud.
I am also happy.
// */
