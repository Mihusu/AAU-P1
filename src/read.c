#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void start_read();
void word_reader();
void tag_searcher();
void arrayExtender();
void** arrayExtenderExperimental();
void text_reader();


int main(void){

    char **keywords_pp, ***inCVSections_ppp, ***itemicedSections_ppp;
    int keywords, *itemicedNumbers, *sectionsNumbers, numberOfSections;
    start_read(&keywords_pp, &itemicedSections_ppp, &inCVSections_ppp);

    return 0;
}


void start_read(char ***theKeywords_ppp, char ****cvLongItemiced_pppp, char ****cvLongSections_pppp){
    // Open a file (Keywords, Long CV)
    
    word_reader(fopen("Hello.txt", "r"), theKeywords_ppp);

    // Send Long CV file to tag_searcher
    
    // Send file to word_reader function
    
} 

void text_reader(FILE *theFile){
    // Alternative, probably simpler
    char *theText = malloc(10 * sizeof(char));
    int characters = 0;
    while(feof(theFile)){
        
    }
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


void arrayExtender(char ***theIn_ppp, int currLength){
    // Adds an extra entry to the array
    char **theNew_pp = malloc((currLength + 10) * sizeof(char *));
    for(int i = 0; i < currLength; i++){
        theNew_pp[i] = (*theIn_ppp)[i];
    }
    free(*theIn_ppp);
    *theIn_ppp = theNew_pp;
}


void** arrayExtenderExperimental(void **theIn_pp, int currLength){
    // Creates a new array (containing pointers) thats 1 space longer
    // than the old array, copies the content of old into new and
    // free the old array.
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

void arrayExtender(char ***theIn_ppp, int currLength){
    // Adds an extra entry to the array
    char **theNew_pp = malloc((currLength + 10) * sizeof(char *));
    for(int i = 0; i < currLength; i++){
        theNew_pp[i] = (*theIn_ppp)[i];
    }
    free(*theIn_ppp);
    *theIn_ppp = theNew_pp;
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

void** arrayExtenderExperimental(void **theIn_pp, int currLength){
    // Creates a new array (containing pointers) thats 1 space longer
    // than the old array, copies the content of old into new and
    // free the old array.
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
I flush the toilet always.

Going home is for the weak.

I am very proud.
I am also happy.
// */
