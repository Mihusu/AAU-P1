#ifndef P1_SRC_FILTER_H
#define P1_SRC_FILTER_H

#define KEYWORD_LENGTH 12  // amount of keywords in array
#define PARA_AMOUNT 6      // amount of paragraphs
#define PARA_LENGTH 12     // length of each paragraph

// calculates the density of all paragraphs and returns the value into the
// density array
void cv_Density(double *density_of_Paragraph,
                char *CV[PARA_AMOUNT][PARA_LENGTH],
                char *keyword_List[KEYWORD_LENGTH], int length[PARA_AMOUNT]);
// divies paragraph weight with the same paragraphs length, to find density form
// 0 to 1
void paragraph_Density(int Weight, int Length, double *density, int i);
// Checks for how many times a paragraph matches keywords
int paragraph_Weight(char *Paragraph[], char *Keywords[], int length);
// compares for string match, to see if they are the same.
bool is_word_match(char word_1[], char word_2[]);
// Comparing tuples by comparing the first (double) value = doubleval. to be
// used in stdlib.qsort
int cmp_tuples(const void *a, const void *b);
void inclusion(double *Density, char *CV[PARA_AMOUNT][PARA_LENGTH],
               int length[PARA_AMOUNT], bool *include);

#endif  // P1_SRC_FILTER_H
