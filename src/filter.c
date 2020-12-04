/*
This program filters the input CV, so that only appropiate parts are included, and the parts
that are included are shortened if some parts are unnecessary.
The output of this file will be used in the format.c file.
*/

typedef struct {
    double doubleVal; //density array
    int intVal; //value to be inserted into cv, to declare which to add first.
} Tuple;//defines the tuple as (x,y), where x is double val, and y is intval

#define MAX_WORDS 110 //max words in the CV
#define PP_AMOUNT 62 //amount of personal pronouns.

void include_section();
bool is_word_match();
int calculate_section_weight();
void calculate_section_density();
void calculate_text_density();
int cmp_tuples();
void generate_text();
void remove_punctuation();
void remove_duplicate();
int levenshtein();
void remove_personal_pronouns();

//removes all personal pronouns of the start of every sentence of the input section, before calculating cv density
void remove_personal_pronouns(int *words_in_sections,int sections_count,char ***sections_out){
    //personal pronouns selected from this list https://en.wikipedia.org/wiki/English_personal_pronouns                                                                                                                                                                                                                                                                                                       vvvv official pronouns end here                                             
    char *personal_pronouns[PP_AMOUNT] = {"i","me","myself","mine","my","we","us","ourselves","ourself","ours","our","you","yourself","yours","your","thou","thee","thyself","thine","thy","yourselves","he","him","himself","his","she","her","herself","hers","her","it","itself","its","they","them","themselves","theirs","their","themself","one","oneself","one's","who","whom","whose","what","which","is","it's","its","you're","youre","are","am","im","i'm","have","has","had","take","a","an"};
    for (int i = 0; i < sections_count; i++){ //runs through sections
        int marker = 0;
        for (int j = 0; j < words_in_sections[i]; j++){ //runs through the words in a section
            char ph = sections_out[i][j][strlen(sections_out[i][j]) - 1]; //placeholder for last char in a word
            int m;
            int compare_true = 1;
            for(m = 0; m < PP_AMOUNT && compare_true; m++){ //loops through the personal pronouns list
                compare_true = strcasecmp(sections_out[i][j],personal_pronouns[m]);
            }
            if (!(compare_true) && (marker == j)){ //scans to see if this word exists
                free(sections_out[i][j]); //free the unsued pointer value in the begninging
                words_in_sections[i] -= 1; //decrementing the stored size of a section..
                for (int k = j; k < words_in_sections[i]; k++){ //shifts the words to the left
                    sections_out[i][k] = sections_out[i][k+1];
                }
                sections_out[i] = realloc(sections_out[i],sizeof(char *)*(words_in_sections[i])); //realloc size of the section
                j--;
            }
            //checking to see if the part ends with a specifik punctuation, to also remove the next word starting with personal pronouns
            else if(ph == '.' || ph == '!' || ph == '?' || ph == ':' || ph == ';'){
                marker = j+1;
            }
        }
    }
}

//checks if a paragraph in CV is apart of "bool included paragraphs" to add those paragraphs to "filtered_text"
void generate_text(bool *included_sections, char ***sections_out, int sections_count, int *words_in_section, char **filtered_text){
    int total_chars = 1;
    int ammount_malloced = 100;

    *filtered_text = malloc(ammount_malloced*sizeof(char));
    **filtered_text = '\0';
    for(int i = 0; i < sections_count; i++){
        if (included_sections[i])
        {
            for(int k = 0; k < words_in_section[i]; k++){
                if (total_chars + strlen(sections_out[i][k]) + 2 >= ammount_malloced){
                    ammount_malloced += 100;
                    *filtered_text = realloc(*filtered_text, ammount_malloced * sizeof(char));
                }
                total_chars += strlen(sections_out[i][k]) + 1; //adds neccesary characters for the added chars plus nullterminator
                strcat(*filtered_text,sections_out[i][k]); //adds the section to the filtered CV.
                if (k != words_in_section[i] - 1){
                    strcat(*filtered_text, " "); //puts a space after each word, if it isn't the last word
                }
            }
            total_chars += 1; //adds more characters for the "\\\\"
            strcat(*filtered_text, "\\\\"); //adds newline
        }  
    }
}

//calculates the density of all paragraphs and returns the value into the density array
void calculate_text_density(char ***sections_out, char **keyword_List, int *length, int sections_count, int keyword_count, double *density_of_section){
    for (int i = 0; i < sections_count; i++) //loops through all paragraphs to get each density.
    {
        int weight = calculate_section_weight(sections_out[i],keyword_List,length[i],keyword_count);
        calculate_section_density(weight,length[i],i,density_of_section);
    }
}

// divides paragraph weight with the same paragraphs length, to find density form 0 to 1
void calculate_section_density(int weight, int length, int i, double* density){
    density[i] = ((double)weight)/((double)length);
}

//Checks for how many times a paragraph matches keywords
int calculate_section_weight(char **section, char **keywords, int length, int keyword_count){
    int match_Weight = 0;
    for(int j = 0; j < length; j++){
        for(int i = 0; i < keyword_count; i++){
            match_Weight += is_word_match(section[j],keywords[i]);
            //if a word matches a keyword, it breaks the loop, so that that one word can't match with more than one keyword
            if(is_word_match(section[j],keywords[i]) == 1){
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
        if((word[i] >= 33 && word[i] <= 47)||(word[i] >= 58 && word[i] <= 63)
            ||(word[i] >= 91 && word[i] <= 96)||(word[i] >= 123 && word[i] <= 126)){
            word[i] = '\0';
        } 
    }
}

//returns a pointer to bool array of which paragraphs that should be included.
void include_section(double *density, char ***sections_out, int *length, int sections_count, bool *include) {
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
