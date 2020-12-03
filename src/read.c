#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void start_read();
void tag_searcher();
void text_reader();
int line_reader();
void worder();
void section_treater();
void the_ending();
void line_reader_controle();

/*/
int main(void){
    char **keywords_pp;
    int nKeywords; // Number of keywords

    char ***itemicedSections_ppp;
    int nItemices, *nItemicedContent_p; // Number of itemices, Number of items in eatch itemices

    char ***inCVSections_ppp;
    int nSections, *nSectionContent_p; // Number of freetext sections, Number of words in eatch section

    char *cvGeneralInfo_p;
    int initialWordCount;

    start_read(&keywords_pp, &nKeywords, &itemicedSections_ppp, &nItemices, &nItemicedContent_p, &inCVSections_ppp, &nSections, &nSectionContent_p, &cvGeneralInfo_p, &initialWordCount);
    // All rest of code here
    the_ending(keywords_pp, nKeywords, itemicedSections_ppp, nItemices, nItemicedContent_p, inCVSections_ppp, nSections, nSectionContent_p, cvGeneralInfo_p);
    return 0;
} // */


void start_read(char ***theKeywords_ppp, int *nKword_p, char ****cvLongItemiced_pppp, int *nItemices_p, int **nItemicedContent_pp, char ****cvLongSections_pppp, int *nSections_p, int **nSectionWords_pp, char **cvGInfo_pp, int *initialWords_p){

    //char *fnLongCV = malloc(); // In case of user defined file name
    FILE *theLongCV, *theKeywords;
    char *cvTotalText_p, *keywordsTotalText_p;
    theLongCV = fopen("LongCV.txt", "r"); // Doing longCV first might have more consecutive space available if pc is low RAM
    theKeywords = fopen("Keywords.txt", "r");
    if(theLongCV == NULL || theKeywords == NULL){
        // Error, can't open file.
        printf("\nError can't open input file(s)\n"); // temp remove later
        exit(EXIT_FAILURE);
    }

    text_reader(theLongCV, &cvTotalText_p);
    tag_searcher(cvTotalText_p, cvLongItemiced_pppp, nItemices_p, nItemicedContent_pp, cvLongSections_pppp, nSections_p, nSectionWords_pp, cvGInfo_pp, initialWords_p);
    free(cvTotalText_p);

    text_reader(theKeywords, &keywordsTotalText_p);
    worder(keywordsTotalText_p, theKeywords_ppp, nKword_p);
    free(keywordsTotalText_p);
} 


void the_ending(char **theKeywords_pp, int nKword, char ***cvLongItemiced_ppp, int nItemices, int *nItemicedContent_p, char ***cvLongSections_ppp, int nSections, int **nSectionWords_p, char *cvGInfo_p){
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
    free(cvGInfo_p);
}


void text_reader(FILE *theFile, char **outText_pp){
    // Read all text from the file.
    int characters = 0, alottetArray = 300;
    char *theText_p = malloc(alottetArray * sizeof(char));
    if(theText_p == NULL){
        // Error can't allocate memmory
        printf("\nError m allo, in text_reader\n"); // Temp remove later
        exit(EXIT_FAILURE);
    }
    
    while(1){
        if(characters >= alottetArray){
            // Allocating more memmory when more is required.
            alottetArray += 100;
            theText_p = (char *) realloc(theText_p, alottetArray * sizeof(char));
            if(theText_p == NULL){
                // Error can't reallocate new memmory
                printf("\nError m re allo, in text_reader\n"); // Temp remove later
                exit(EXIT_FAILURE);
            }
        }
        // Reads the next char from the file.
        theText_p[characters] = fgetc(theFile);

        // End Of File was reatched.
        if(theText_p[characters] == EOF){
            // Change theText_p from char array to string.
            theText_p[characters] = '\0';
            break;
        }
        // Easyer to handel in the rest of the code if there is no '\r'.
        if(theText_p[characters] != '\r')
            characters++;
    }

    if(characters == 0){
        // Error file is empty
        printf("\nError file is empty, in text_reader\n"); // Temp remove later
        exit(EXIT_FAILURE);
    }
    /* Redo theText_p to have correct size.
    About realloc() atempts to resize at current memmory location, only if resize fails:
    atempts to find somewhere with the requestet memmory size and moves there. // */
    theText_p = (char *) realloc(theText_p, (characters + 1) * sizeof(char));
    if(theText_p == NULL){
        // Error can't reallocate new memmory, for the final string
        printf("\nError m allo end, in text_reader\n"); // Temp remove later
        exit(EXIT_FAILURE);
    }
    
    // Returning the variables.
    *outText_pp = theText_p;

    // All content of the file is in a string, file is no longer needed.
    fclose(theFile);
}


void worder(char *cleanText_p, char ***wordsOut_ppp, int *nWordsOut_p){
    // Seperates a string text into a array of strings containing individual words.
    int nTheWords = 0, nWordsSpace = 30, currentChar = 0, wordStart = 0, i;
    char **theWords_pp = malloc(nWordsSpace * sizeof(char *));
    if(theWords_pp == NULL){
        // Error can't allocate memmory
        printf("\nError m allo, in worder, for words\n"); // Temp remove later
        exit(EXIT_FAILURE);
    }
    while(1){
        // Handeling of " \0" and "\n\0" lead to while(1) rather than while(cleanText_p[currentChar] != '\0').
        if(cleanText_p[currentChar] == ' ' || cleanText_p[currentChar] == '\n' || cleanText_p[currentChar] == '\0'){
            if(currentChar != wordStart){
                if(nTheWords >= nWordsSpace){
                    // More memmory is needed.
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
                // Alternative to strncpy(), don't need "&(cleanText_p[wordStart])" calculation.
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
            // Keeps track of the index value for the start of the next word.
            wordStart = currentChar + 1;
        }
        currentChar++;
    }
    if(nTheWords == 0){
        // Error no words in the given string
        printf("\nError bad worder function call, in read.c\n"); // Temp remove later
        exit(EXIT_FAILURE);
    }
    // Resize theWords_pp to correct size.
    theWords_pp = (char **) realloc(theWords_pp, nTheWords * sizeof(char *));
    if(theWords_pp == NULL){
        // Error can't allocate memmory
        printf("\nError m re allo final, in worder, for words\n"); // Temp remove later
        exit(EXIT_FAILURE);
    }
    // Returning the outputs, do here for less dereferencing.
    *wordsOut_ppp = theWords_pp;
    *nWordsOut_p = nTheWords;
}


void tag_searcher(char *fileCleanText_p, char ****cvLongItemiced_pppp, int *nItemices_p, int **nItemicedContent_pp, char ****cvLongSections_pppp, int *nSections_p, int **nSectionWords_pp, char **cvGInfo_pp, int *wordCounter_p){
    // Handels tag splitting of the longCV.
    int currentChar = 1, currentMarker = -1, nTags = 1, alloTags = 5, i = 0, j, areaLength;
    char *infoText_p, **tempTrash_pp;
    // Contains pointers to the tags, in .  Mangler SÆTNING!!!!!
    char **tagLocations_pp = malloc(alloTags * sizeof(char *));
    if(tagLocations_pp == NULL){
        exit(EXIT_FAILURE);
    }
    
    tagLocations_pp[0] = fileCleanText_p;
    while(1){
        if(fileCleanText_p[currentChar] == '\n'){
            currentMarker = currentChar;
        } else if(fileCleanText_p[currentChar] == '\0' || (fileCleanText_p[currentChar] == '#' && currentMarker + 1 == currentChar)){
            if(nTags >= alloTags){
                alloTags += 5;
                tagLocations_pp = (char **) realloc(tagLocations_pp, alloTags * sizeof(char *));
                if(tagLocations_pp == NULL){
                    exit(EXIT_FAILURE);
                }
            }
            tagLocations_pp[nTags] = &(fileCleanText_p[currentChar]);
            nTags++;
            if(fileCleanText_p[currentChar] == '\0')
                break;
        }
        currentChar++;
    }

    areaLength = tagLocations_pp[1] - tagLocations_pp[0];
    tagLocations_pp[1][-1] = '\0';
    infoText_p = (char *) malloc(areaLength * sizeof(char));
    if(infoText_p == NULL){
        exit(EXIT_FAILURE);
    }
    for(j = 0; j < areaLength; j++){
        infoText_p[j] = tagLocations_pp[0][j];
    }
    *cvGInfo_pp = infoText_p;
    // Gets number of words in the infoText.
    worder(infoText_p, &tempTrash_pp, wordCounter_p);
    for(j = 0; j < *wordCounter_p; j++){
        free(tempTrash_pp[j]);
    }
    free(tempTrash_pp);

    line_reader_controle(tagLocations_pp, nTags, cvLongItemiced_pppp, nItemices_p, nItemicedContent_pp, cvLongSections_pppp, nSections_p, nSectionWords_pp, wordCounter_p);
    free(tagLocations_pp);
}


void line_reader_controle(char **tags_pp, int nOfTags, char ****cvLongItemiced_pppp, int *nItemices_p, int **nItemicedContent_pp, char ****cvLongSections_pppp, int *nSections_p, int **nSectionWords_pp, int *nWordsInStart_p){
    int currentItemice = 0, alloItemices = 4, i, j, tempTest, nItems, alloItems, tempWordCounter, tempLineResult;
    char *freeTextVariations[32] = {"freetext", "Freetext", "freeText", "FreeText", "freetext.", "Freetext.", "freeText.", "FreeText.",
    "free text", "Free text", "free Text", "Free Text", "free text.", "Free text.", "free Text.", "Free Text.",
    " freetext", " Freetext", " freeText", " FreeText", " freetext.", " Freetext.", " freeText.", " FreeText.",
    " free text", " Free text", " free Text", " Free Text", " free text.", " Free text.", " free Text.", " Free Text."};
    char *tempFirstLine_p, *tempNextLineLocation_p, **tempWords_pp;
    int *nItemsInItem_p = malloc(alloItemices * sizeof(int));
    char ***itemices_ppp = malloc(alloItemices * sizeof(char **));
    if(itemices_ppp == NULL || nItemsInItem_p == NULL){
        exit(EXIT_FAILURE);
    }

    for(i = 1; i < nOfTags - 1; i++){
        if(tags_pp[i + 1][0] != '\0')
            tags_pp[i + 1][-1] = '\0';
        // &(tags_pp[i][1]) remove # from the start of the first line.
        if(line_reader(&(tags_pp[i][1]), &tempNextLineLocation_p, &tempFirstLine_p) <= 0){
            // Tag is invalid, can't guarantee sufficient information to run the rest of the program.
            exit(EXIT_FAILURE);
        }
        tempTest = 1;
        for(j = 0; j < 32 && tempTest; j++)
            tempTest = strcmp(tempFirstLine_p, freeTextVariations[j]);
        
        if(tempTest){
            if(currentItemice >= alloItemices){
                alloItemices += 2;
                itemices_ppp = (char ***) realloc(itemices_ppp, alloItemices * sizeof(char **));
                nItemsInItem_p = (int *) realloc(nItemsInItem_p, alloItemices * sizeof(int));
                if(itemices_ppp == NULL || nItemsInItem_p == NULL){
                    exit(EXIT_FAILURE);
                }
            }
            worder(tempNextLineLocation_p, &tempWords_pp, &tempWordCounter);
            for(j = 0; j < tempWordCounter; j++){
                free(tempWords_pp[j]);
            }
            free(tempWords_pp);
            *nWordsInStart_p += tempWordCounter;

            alloItems = 5;
            nItems = 1;
            itemices_ppp[currentItemice] = (char **) malloc(alloItems * sizeof(char *));
            if(itemices_ppp[currentItemice] == NULL){
                exit(EXIT_FAILURE);
            }
            itemices_ppp[currentItemice][0] = tempFirstLine_p;
            while(1){
                if(nItems >= alloItems){
                    alloItems += 5;
                    itemices_ppp[currentItemice] = (char **) realloc(itemices_ppp[currentItemice], alloItems * sizeof(char *));
                    if(itemices_ppp[currentItemice] == NULL){
                        exit(EXIT_FAILURE);
                    }
                }
                tempLineResult = line_reader(tempNextLineLocation_p, &tempNextLineLocation_p, &(itemices_ppp[currentItemice][nItems]));
                if(tempLineResult >= 0){
                    nItems++;
                    if(tempLineResult == 0)
                        break;
                } else if(tempLineResult == -2){
                    break;
                }
            }
            itemices_ppp[currentItemice] = (char **) realloc(itemices_ppp[currentItemice], nItems * sizeof(char *));
            if(nItems == 1 || itemices_ppp[currentItemice] == NULL){
                exit(EXIT_FAILURE);
            }
            nItemsInItem_p[currentItemice] = nItems;
            currentItemice++;
        } else {
            free(tempFirstLine_p);
            section_treater(tempNextLineLocation_p, cvLongSections_pppp, nSections_p, nSectionWords_pp);
        }
    }
    if(currentItemice == 0){
        exit(EXIT_FAILURE);
    }
    itemices_ppp = (char ***) realloc(itemices_ppp, currentItemice * sizeof(char **));
    nItemsInItem_p = (int *) realloc(nItemsInItem_p, currentItemice * sizeof(int));
    if(itemices_ppp == NULL || nItemsInItem_p == NULL){
        exit(EXIT_FAILURE);
    }
    *cvLongItemiced_pppp = itemices_ppp;
    *nItemicedContent_pp = nItemsInItem_p;
    *nItemices_p = currentItemice;
}


int line_reader(char *theTextIn_p, char **theNextLine_pp, char **theLineOut_pp){
    int theReader = 0, alloChars = 20, marking = 0, tempWordCounter = 0;
    char *theLine_p = malloc(alloChars * sizeof(char));
    if(theLine_p == NULL){
        exit(EXIT_FAILURE);
    }
    while(1){
        if(theReader >= alloChars){
            // Need more memmory.
            alloChars += 20;
            theLine_p = (char *) realloc(theLine_p, alloChars * sizeof(char));
            if(theLine_p == NULL){
                exit(EXIT_FAILURE);
            }
        }
        if(theTextIn_p[theReader] == '\n' || theTextIn_p[theReader] == '\0')
            break;
        theLine_p[theReader] = theTextIn_p[theReader];
        theReader++;
    }
    // Pointer to start of next line.
    *theNextLine_pp = &(theTextIn_p[theReader + 1]);
    // Something went wrong.
    if(theReader == 0){
        free(theLine_p);
        if(theTextIn_p[theReader] == '\0')
            return -2;
        return -1;
    }
    theLine_p[theReader] = '\0';
    theLine_p = (char *) realloc(theLine_p, (theReader + 1) * sizeof(char));
    if(theLine_p == NULL){
        exit(EXIT_FAILURE);
    }
    *theLineOut_pp = theLine_p;
    
    if(theTextIn_p[theReader] == '\0')
        return 0;
    else
        return 1;
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
Name: Johannes Fjerndam.
Sex: Female/non-binary.
IQ: 78.
#Workexperience
2009-2011 Flaskedreng i Netto.
2011-2013 Flymekaniker.
#Education
2016 AAU Batchelor i software.
2013 HTX-Hilleroed, Mat-Fys.
#FreeText
Hello I am a good worker.

I flush the toilet always.

Going home is for the weak.

I am very proud.
I am also happy.
// */
