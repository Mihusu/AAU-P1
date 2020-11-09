#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void start_read();
void word_reader();
void tag_searcher();
//void arrayExtender();
void** arrayExtenderExperimental();
void text_reader();
void worder();
int length_of_a_string();


int main(void){

    char **keywords_pp;
    int nKeywords; // Number of keywords

    char ***itemicedSections_ppp;
    int nItemices, *nItemicedContent_p; // Number of itemices, Number of items in eatch itemices

    char ***inCVSections_ppp;
    int nSections, *nSectionContent_p; // Number of freetext sections, Number of words in eatch section

    start_read(&keywords_pp, &nKeywords, &itemicedSections_ppp, &nItemices, &nItemicedContent_p, &inCVSections_ppp, &nSections, &nSectionContent_p);

    return 0;
}


int length_of_a_string(char *inStr){
    // Returns the length of a null terminated char array, not including the termination character
    int i = 0;
    while(inStr[i] != '\0')
        i++;
    return i;
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
    //tag_searcher(theLongCV, cvLongItemiced_pppp, cvLongSections_pppp);


    text_reader(theKeywords, &keywordsTotalText_p);
    worder(keywordsTotalText_p, theKeywords_ppp, nKword_p);
    free(keywordsTotalText_p);

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
    while(!(feof(theFile))){
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
    // Alter char array to string
    theText_p[characters] = '\0';
    
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


void word_reader(FILE *theInFile, char ***theOutput_ppp){
    // Read every word of a file or section (in an array)
    char **allWords_pp = malloc(10 * sizeof(char *));
    int hej = 0, hills = 10;
    
    while(1){
        if(feof(theInFile)){
            // feof() -> is next char in the file_input-stream the 'EOF' (End Of File)
            break;
        }
        // Temporary storage for 1 word.
        char theWordTemp_p[100]; // Longest word in Danish is 51
        fscanf(theInFile, "%s", theWordTemp_p);
        // Final storage for 1 word, only allocated the required length for that word
        char *theWord_p = malloc((strlen(theWordTemp_p) + 1) * sizeof(char));
        strcpy(theWord_p, theWordTemp_p);
        
        allWords_pp[hej] = theWord_p;
        if(hej >= hills){
            //arrayExtender(&allWords_pp, hej+1);
            allWords_pp = (char **) arrayExtenderExperimental(allWords_pp, hej+1);
        }
        hej++;
    }

    // Find tags, and end current reading there
    *theOutput_ppp = allWords_pp;
}

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


void** arrayExtenderExperimental(void **theIn_pp, int currLength){
    // Creates a new array (containing pointers) thats 1 space longer
    // than the old array, copies the content of old into new and
    // free the old array. Only works for a array containing pointers.
    void **theNew_pp = malloc((currLength + 1) * sizeof(void *));
    for(int i = 0; i < currLength; i++){
        theNew_pp[i] = theIn_pp[i];
    }
    free(theIn_pp);
    return theNew_pp;
}


void tag_searcher(FILE *fileInbound, char ****theItems_pppp, char ****theText_pppp){
    char ***theReadItems_ppp, ***theReadText_ppp;
    theReadItems_ppp = malloc(2 * sizeof(char **));
    theReadText_ppp = malloc(1 * sizeof(char **));
    // Use to divide sections in Long CV reading (array) 
    
    // Run Word_Reader on Long CV
    while(!(feof(fileInbound))){
        //word_reader();
    }
    
}

void line_reader(){

    // Use to divide sections in Long CV reading (array)

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
