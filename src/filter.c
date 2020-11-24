/*
This program filters the input CV, so that only appropiate parts are included, and the parts
that are included are shortened if some parts are unnecessary.
The output of this file will be used in the format.c file.
*/

typedef struct {
    double doubleVal; //density array
    int intVal; //value to be inserted into cv, to declare which to add first.
} Tuple;//defines the tuple as (x,y), where x is double val, and y is intval

#define MAX_WORDS 50 //max words in the CV

void include_paragraph();
bool is_word_match();
int calculate_paragraph_weight();
void calculate_paragraph_density();
void calculate_cv_density();
int cmp_tuples();
void generate_cv();
void remove_punctuation();
void remove_duplicate();
int levenshtein();

//checks if a paragraph in CV is apart of "bool included paragraphs" to add those paragraphs to "filtered_cv"
void generate_cv(bool *included_paragraphs, char ***sections_out, int sections_count, int *wors_in_section, char **filtered_cv){
    int total_chars = 1;
    int ammount_malloced = 100;

    *filtered_cv = malloc(ammount_malloced*sizeof(char));
    **filtered_cv = '\0';
    for(int i = 0; i < sections_count; i++){
        if (included_paragraphs[i])
        {
            for(int k = 0; k < wors_in_section[i]; k++){
                if (total_chars + strlen(sections_out[i][k]) + 1 >= ammount_malloced){
                    ammount_malloced += 100;
                    *filtered_cv = realloc(*filtered_cv, ammount_malloced * sizeof(char));
                }
                total_chars += strlen(sections_out[i][k])+1; //adds neccesary characters for the added chars plus nullterminator
                strcat(*filtered_cv,sections_out[i][k]);
                if (k != wors_in_section[i] - 1){
                    strcat(*filtered_cv," "); //puts a space after each word, if it isnt the last word
                }
            }
            strcat(*filtered_cv,"\n"); //adds newline
        }  
    }
}

//calculates the density of all paragraphs and returns the value into the density array
void calculate_cv_density(char ***sections_out, char **keyword_List, int *length, int sections_count, int keyword_count, double *density_of_paragraph){
    for (int i = 0; i < sections_count; i++) //loops through all paragraphs to get each density.
    {
        int weight = calculate_paragraph_weight(sections_out[i],keyword_List,length[i],keyword_count);
        calculate_paragraph_density(weight,length[i],i,density_of_paragraph);
    }
}

// divides paragraph weight with the same paragraphs length, to find density form 0 to 1
void calculate_paragraph_density(int Weight, int Length, int i, double* density){
    density[i] = ((double)Weight)/((double)Length);
}

//Checks for how many times a paragraph matches keywords
int calculate_paragraph_weight(char **Paragraph, char **Keywords, int length, int keyword_count){
    int match_Weight = 0;
    for(int j = 0; j < length; j++){
        for(int i = 0; i < keyword_count; i++){
            match_Weight += is_word_match(Paragraph[j],Keywords[i]);
            //if a word matches a keyword, it breaks the loop, so that that one word can't match with more than one keyword
            if(is_word_match(Paragraph[j],Keywords[i]) == 1){
                break;
            }
        }
    }
    return(match_Weight);
}

//compares for string match, to see if they are the same.
bool is_word_match(char word_1[], char word_2[]){
    bool word_match;
    int n1 = 4;
    int n2 = 4;

    word_match = strcasecmp(word_1,word_2); //case insensitive string compare

    //if it doesnt do string match (1 is false) then it will try again, while removing punctuation.
    if (word_match == 1){
        //string copies, to be used in remove punctuation, so that it doesnt change the original file.
        char *temp_word_1 = malloc(sizeof(char)*(strlen(word_1)+1));
        strcpy(temp_word_1,word_1);
        remove_punctuation(temp_word_1);
        word_match = strcasecmp(temp_word_1,word_2);

        /*if the words still don't match, and both words are longer than n1 (arbitarily long enough words)
        it will see the levenshtein distance, and if the distance is under n2 (arbitarily short enough distance)
        then word_match will return positive
        */ 
        if (word_match == 1 && strlen(temp_word_1) > n1 && strlen(word_2) > n1){
            if(levenshtein(temp_word_1,word_2) < n2){
                word_match = 0;
            }
        }
        free(temp_word_1);
    }
    
    //flips the bool value, since strcmp = 0 is true; strcmp = 1 is false
    if(word_match == 0){
        return 1;
    }
    else{
        return 0;
    }
}

//removes punctuation and other symbols, such as( . , : ? ! - + )to make stringcompare more reliable
void remove_punctuation(char *word){
    // int starts at 1, to ignore the first char in the word.
    for (int i = 1; i < strlen(word); i++){
        if((word[i] >= 33 && word[i] <= 47)||(word[i] >= 58 && word[i] <= 63)||(word[i] >= 91 && word[i] <= 96)||(word[i] >= 123 && word[i] <= 126)){
            word[i] = '\0';
        } 
    }
}

/* 
source code for the levenstein algorithm from 
https://rosettacode.org/wiki/Levenshtein_distance#C
Modified to be used in our program.
fuzzy string matching to find out how similar words are, to counteract misspelling.
*/
int levenshtein(char *s, char *t){
	int ls = strlen(s), lt = strlen(t);
	int d[ls + 1][lt + 1];
 
	for (int i = 0; i <= ls; i++)
		for (int j = 0; j <= lt; j++)
			d[i][j] = -1;
 
	int dist(int i, int j){
		if (d[i][j] >= 0) return d[i][j];
 
		int x;
		if (i == ls)
			x = lt - j;
		else if (j == lt)
			x = ls - i;
		else if (s[i] == t[j])
			x = dist(i + 1, j + 1);
		else {
			x = dist(i + 1, j + 1);
 
			int y;
			if ((y = dist(i, j + 1)) < x) x = y;
			if ((y = dist(i + 1, j)) < x) x = y;
			x++;
		}
		return d[i][j] = x;
	}
	return dist(0, 0);
}

//returns a pointer to bool array of which paragraphs that should be included.
void include_paragraph(double *density, char ***sections_out, int *length, int sections_count, bool *include) {
    Tuple priority_array[sections_count]; //defining priority array as a tuple
    int words = 0;
    int i = 0;

    for (int i = 0; i < sections_count; i++) { //initializes the priority array with the values from density.
        priority_array[i].doubleVal = density[i];
        priority_array[i].intVal = i;
    }
    qsort(priority_array, sections_count, sizeof(Tuple), cmp_tuples); //sorts the priority array from highest density to lowest

    while (words < MAX_WORDS && i < sections_count) {  //creates the bool array with what paragraphs that needs to be included
        words += (int)length[priority_array[i].intVal];
        include[priority_array[i].intVal] = 1; 
        i++;
    } 
}

// Comparing tuples by comparing the first (double) value = doubleval. to be used in stdlib.qsort
int cmp_tuples(const void * a, const void * b) {
    double cmp = ((*(Tuple*)b).doubleVal - (*(Tuple*)a).doubleVal);
    // Make sure a negative double also results in returning a negative int, and likewise for positive
    if (cmp < 0.0) {return -1;}
    else if (cmp > 0.0) {return 1;}
    else {return 0;}
}

