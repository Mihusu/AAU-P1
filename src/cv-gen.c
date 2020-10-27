#include <stdio.h>

/*
 * Function to compare words
 */
_Bool word_matcher(word1, word2){
    return 1;
}

/*
 * Function to calculate "weight" of paragraph
 */
int weight(paragraph, keywords){
    if (word_matcher(word1, word2) {
        counter++
    }
    return counter;
}

/*
 * Function to count the words of a paragraph
 */
int word_count(paragraph){
    return number_of_words;
}

/*
 * Function to create an array with the importance and length of all paragraphs
 */
void importance(long_cv, *importance_array){
    for (int i = 0; i < size(long_cv); i++) {
        int count = word_count(paragraph);
        *importance_array.i = (weight(paragraph) / count, count);
    }
}

/*
 * Function to create an array with booleans of wether a paragraph is to be
 * included or not
 */
void include(*importance_array, *inclusion_array){
    *inclusion_array.i = true;// sets entries to true if they should be included
}

/*
 * Function to output the plain text file with the final cv, so it can be
 * formatted
 */
void output(long_cv, *inclusion_array){
    for (int i = 0; i < size(long_cv); i++) {
        if (*inclusion_array = true) {
            print long_cv.i;
        }
    }
}

int main(void){
    return 0;
}
