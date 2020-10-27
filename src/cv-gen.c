#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int max_word_count = 700;
int min_word_count = 500;  //change at a later stage, to the req.txt

int main(void){
    //load largecv.read.c
    //load req.read.c
    //load keyword.read.c

    //run word_matcher, to see how many words match keywords

    return 0;
}
/*
 * Function to compare words
 */

bool is_word_match(word1, word2){

    return;
}
//
///*
// * Function to calculate "weight" of paragraph
// */
//int weight(paragraph, keywords){
//    if (word_matcher(word1, word2) {
//        counter++
//    }
//    return counter;
//}
//
///*
// * Function to count the words of a paragraph
// */
//int word_count(paragraph){
//    return number_of_words;
//}
//
///*
// * Function to create an array with the importance and length of all paragraphs
// */
//void importance(long_cv, *importance_array){
//    for (int i = 0; i < size(long_cv); i++) {
//        int count = word_count(paragraph);
//        *importance_array.i = (weight(paragraph) / count, count);
//    }
//}
//
///*
// * Function to create an array with booleans of wether a paragraph is to be
// * included or not
// */
//void include(*importance_array, *inclusion_array){
//    *inclusion_array.i = true;// sets entries to true if they should be included
//}
//
///*
// * Function to output the plain text file with the final cv, so it can be
// * formatted
// */
//void output(long_cv, *inclusion_array){
//    for (int i = 0; i < size(long_cv); i++) {
//        if (*inclusion_array = true) {
//            print long_cv.i;
//        }
//    }
//}
//
//