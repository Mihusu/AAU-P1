#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define KEYWORD_LENGTH 12 //amount of keywords in array
#define PARA_AMOUNT 6 //amount of paragraphs
#define PARA_LENGTH 12 //length of each paragraph

void inclusion();
int main(void)
{
    char *CV[PARA_AMOUNT][PARA_LENGTH] = {{"Jeg","har","en","gym","uddannelse"}, //testing, tb replace by read.c
                                            {"jeg","har","arbejdet","i","netto"},
                                            {"Jeg","er","god","til","C","prog"},
                                            {"Jeg","kan","finde","ud","af","machinelearning","og","statistik","og","sandsynlighedsteori"},
                                            {"Jeg","tager","en","Bsc","i","Software"},
                                            {"Erfaring","med","C","python","css","og","databaser"}};
    char *buzz[KEYWORD_LENGTH] = {"netto","gym","C","prog","css","databaser","python","statistik","sandsynlighedsteori","machinelearning","Bsc","Software"}; //testing, tb replace by read.c
    int length[PARA_AMOUNT] = {5,5,6,10,6,7}; //length of each individuel paragraph //testing, tb replace by read.c
    double density_of_Paragraph[PARA_AMOUNT] = {0.2, 0.2, 0.33, 0.3, 0.33, 0.57};
    bool included_Paragraphs[PARA_AMOUNT];
    inclusion(density_of_Paragraph,CV,length,included_Paragraphs);
    return 0;
}
typedef struct {
    double doubleVal; //density array
    int intVal; //value to be inserted into CV, to declare which to add first.
} tTuple;//defines the tuple as (x,y), where x is double val, and y is intval
    
// Making a compare tuple that will check if one is bigger than the other
int cmp_tuples(const void * a, const void * b) {
    double cmp = ((*(tTuple*)a).doubleVal - (*(tTuple*)b).doubleVal);
    printf("Compare double is: %lf\n", cmp);
    return cmp;
}

void inclusion(double *Density, char *CV[PARA_AMOUNT][PARA_LENGTH], int *length[PARA_AMOUNT], bool *include) {
    tTuple priority_array[PARA_AMOUNT]; //defining priority array as a tuple

    for (int i = 0; i < PARA_AMOUNT; i++) //
    {
        priority_array[i].doubleVal = Density[i];
        priority_array[i].intVal = i;
        printf("%d doubleval: %lf, intVal: %d  ---", i, priority_array[i].doubleVal,priority_array[i].intVal); //testing
        printf("density[%d]: %lf, CV[%d]: %s, length[%d]: %d, include[%d]: %d\n",i, Density[i], i, *CV[i], i, length[i],i,include[i]);
    }
    qsort(priority_array, PARA_AMOUNT, sizeof(tTuple), cmp_tuples);
    printf("\n==============\n");
    for (int i = 0; i < PARA_AMOUNT; i++) //
    {
        printf("%d doubleval: %lf, intVal: %d  ---\n", i, priority_array[i].doubleVal,priority_array[i].intVal); //testing
    }


}
