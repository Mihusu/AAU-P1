
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void start_read();
void word_reader();
void tag_searcher();
void arrayExtender();
void** arrayExtenderExperimental();


int main(void){

    char **keaywords_pp, ***inCVSections_ppp, ***itemicedSections_ppp;
    start_read(&keaywords_pp, &inCVSections_ppp, &itemicedSections_ppp);

    return 0;
}


void start_read(char ***theKeaywords_ppp, char ****cvLongSections_pppp, char ****cvLongItemiced_pppp){
    // Open a file (Keywords, Long CV)
    /*
    FILE *hello; 
    hello = fopen("Hello.txt", "r");
    // */
    word_reader(fopen("Hello.txt", "r"), theKeaywords_ppp);

    // Send Long CV file to tag_searcher
    tag_searcher(fopen("LongCV.txt", "r"), cvLongItemiced_pppp, cvLongSections_pppp);
    
    // Send file to word_reader function
    
} 


void word_reader(FILE *theInFile, char ***theOutput_ppp){
    // Read every word of a file or section (in an array)
    char **allWords_pp = malloc(1 * (__SIZEOF_POINTER__));
    int hej = 0;
    
    while(1){
        if(feof(theInFile)){
            // feof() -> is next char in the file_input-stream the 'EOF' (End Of File)
            break;
        }
        // Temporary storage for 1 word.
        char theWordTemp_p[52]; // Longest word in Danish is 51
        fscanf(theInFile, "%s", theWordTemp_p);
        // Final storage for 1 word, only allocated the required length for that word
        char theWord_p[] = malloc((strlen(theWordTemp_p) + 1) * sizeof(char));
        strcpy(theWord_p, theWordTemp_p);
        
        allWords_pp[hej] = theWord_p;
        arrayExtender(&allWords_pp, hej+1);
        //allWords_pp = (char **) arrayExtenderExperimental(allWords_pp, hej+1);
        hej++;
    }

    // Find tags, and end current reading there
    *theOutput_ppp = allWords_pp;
}


void arrayExtender(char ***theIn_ppp, int currLength){
    // Adds an extra entry to the array
    char **theNew_pp = malloc((currLength + 1) * (__SIZEOF_POINTER__));
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
    void **theNew_pp = malloc((currLength + 1) * (__SIZEOF_POINTER__));
    for(int i = 0; i < currLength; i++){
        theNew_pp[i] = theIn_pp[i];
    }
    free(theIn_pp);
    return theNew_pp;
}


void tag_searcher(FILE *fileInbound, char ****hellos_pppp, char ****hellos2_pppp){

    // Use to divide sections in Long CV reading (array) 
    
    // Run Word_Reader on Long CV
    while(!(feof(fileInbound))){
        word_reader();
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