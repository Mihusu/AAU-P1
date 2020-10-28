
#include <stdio.h>
#include <stdlib.h>

void start_read();
void word_reader();
void tag_searcher();

int main(void){

char wow[10];

    start_read();

}

void start_read(){
    // Open a file (Keywords, Requirments, Long CV)
    FILE *hello; 
    hello = fopen("Hello.txt", "r");

    word_reader(hello);

    // Send Long CV file to tag_searcher
    if(Long CV){
        tag_searcher
    }
    // Send file to word_reader function
    else{
    
        word_reader();
    }
    
} 


void word_reader(FILE *hello2){
    // Read every word of a file or section (in an array)
    char arrayofwords[9999];
    char *jim[9999];
    int hej = 0, i;
    
    while(1){
        fscanf(hello2, "%s", &arrayofwords[hej]);
        hej++;

    
    }
        

    if(File contains no more words)

    }

    // Find tags, and end current reading there

}


void tag_searcher(){

    // Use to divide sections in Long CV reading (array)

}
