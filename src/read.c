
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void start_read();
void word_reader();
void tag_searcher();
void arrayExtender();


int main(void){

    char **keaywords_pp, ***inCVSections_ppp, ***itemicedSections_ppp;
    int wordsInKeaywords, *wordsInSections_p, *itemsInItemicasion_p;
    start_read(&keaywords_pp, &wordsInKeaywords, &inCVSections_ppp, &wordsInSections_p, &itemicedSections_ppp, &itemsInItemicasion_p);

    return 0;
}


void start_read(char ***theKeaywords_ppp, int *wordsInKeaywords_p, char ****cvLongSections_pppp, int **cvLongSectionsWord_pp, char ****cvLongItemiced_pppp, int **cvLongItemicedWord_pp){
    // Open a file (Keywords, Requirments, Long CV)
    /*
    FILE *hello; 
    hello = fopen("Hello.txt", "r");
    // */
    word_reader(fopen("Hello.txt", "r"), theKeaywords_ppp);

    // Send Long CV file to tag_searcher
    
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
        hej++;
    }

    // Find tags, and end current reading there
    *theOutput_ppp = allWords_pp;
}


void arrayExtender(char ***theIn_ppp, int currLength){
    // Adds an extra entry to the array
    char *theNew_pp[] = malloc((currLength + 1) * (__SIZEOF_POINTER__));
    for(int i = 0; i < currLength; i++){
        theNew_pp[i] = (*theIn_ppp)[i];
    }
    free(*theIn_ppp);
    *theIn_ppp = theNew_pp;
}


void tag_searcher(){

    // Use to divide sections in Long CV reading (array)

}
