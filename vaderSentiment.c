#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "utility.h"

// List of intensifiers where the first half indexes hold positive amplifiers and the rest are negative amplifiers 
const char *intensifiers[] = {"very", "uber", "absolutely", "totally", "really", "so", "extremely", 
                            "barely", "hardly", "scarcely", "somewhat", "mildly", "slightly", };
// List of negations 
const char *negations[] = {"not", "isn’t", "doesn’t", "wasn’t", "shouldn’t", "won’t", "cannot", "can’t", "nor"};

// Check if the word is an intensifier -> returns index+1 of intensifier when true and 0 when false  
int is_intensifier(const char *word) {
    for (long unsigned int i = 0; i < sizeof(intensifiers) / sizeof(intensifiers[0]); i++) {
        if (strcmp(word, intensifiers[i]) == 0) {
            return i+1; 
        }
    }
    return 0;
}

// Apply Intensifier and return boost factor  
float apply_intensifier(int intenseIndex, int intenseCaps) { //have to check each word for being an intensifier 
    int numIntense=sizeof(intensifiers) / sizeof(intensifiers[0]);
    if (intenseIndex>0) {
        if (intenseIndex-1 < numIntense/2){
            if (intenseCaps == 1){
                return INTENSE_SCORE*CAPS_FACTOR;
            }
            return INTENSE_SCORE;
        } else if (intenseIndex-1 < numIntense){
            if (intenseCaps == 0){
                return -INTENSE_SCORE*CAPS_FACTOR;
            }
            return -INTENSE_SCORE;
        }
    }
    return 0.0;
}

// Check if  the word passed is an intensifier and return true or false 
int is_negation(const char *word) {
    for (long unsigned int i = 0; i < sizeof(negations) / sizeof(negations[0]); i++) {
        if (strcmp(word, negations[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// Apply negation and return new sentiment score 
float apply_negation(float sentiment, int previous_was_negation) {
    if (previous_was_negation) {
        return sentiment*NEGATION_FACTOR;
    }
    return sentiment;
}

// Aplly all caps boost and return new sentiment score 
float apply_allcaps(float sentiment, const char *word) {
    if (word[0] != '\0') { // Word is not empty, i.e., it is in original case
        int is_allcaps = 1;
        for (int i = 0; word[i] != '\0'; i++) {
            if (!isupper(word[i])) {
                is_allcaps = 0;
                break;
            }
        }
        if (is_allcaps) {
            return sentiment*CAPS_FACTOR;
        }
    }
    return sentiment;
}

// Pass through a sentence and token that is verified to be a lexicon word in the sentance and return 
float apply_punctuation(const char *sentence, const char *word, float sentiment) {
    
    const char *word_position = strstr(sentence, word);

    // Calculate the position just after the word
    const char *after_word = word_position + strlen(word);
    int exclamation_count = 0;

    // Count up to 3 exclamation marks following the word
    while (*after_word == '!' && exclamation_count < MAX_EXCLAMATION_COUNT) {
        exclamation_count++;
        after_word++;
    }
    if (exclamation_count > 0){
        return sentiment + ((float)exclamation_count)*sentiment*PUNC_FACTOR;
    } else {
        return sentiment;
    }
 
}

// Returns a struct pointer that points to word attibutes stored in fileName
WordData* getWordData(const char *filename, int *numWords) {
    FILE *file = fopen(filename, "r");
    if (file==NULL) {
        printf("ERROR: file cannot be opened.\n");
        return NULL;
    }

    int n = 0;
    char ch;
    // Count lines to determine number of words
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            n++;
        }
    }
    rewind(file); // Rewind the file
    *numWords = n; // Correctly set the number of words

    // Dynamically allocate lexicon array with the maximum size
    WordData *wordLibrary = malloc(n*sizeof(WordData));
    if (wordLibrary == NULL) {
        printf("ERROR: memory allocation failed.\n");
        return NULL;
    }
    
    int i = 0;
    char line[MAX_LINE_LENGTH];

    // Read each line from the file
    while (fgets(line, sizeof(line), file)) {
        // Use sscanf to read the word and value1 from the line
        // Ensure no overflow with %19s to limit the word length to 19 characters
        if (i<n && sscanf(line, "%19s  %f  %f  [%d, %d, %d, %d, %d, %d, %d, %d, %d, %d]", 
        wordLibrary[i].word, 
        &wordLibrary[i].value1,
        &wordLibrary[i].value2,
        &wordLibrary[i].intArray[0],
        &wordLibrary[i].intArray[1],
        &wordLibrary[i].intArray[2],
        &wordLibrary[i].intArray[3],
        &wordLibrary[i].intArray[4],
        &wordLibrary[i].intArray[5],
        &wordLibrary[i].intArray[6],
        &wordLibrary[i].intArray[7],
        &wordLibrary[i].intArray[8],
        &wordLibrary[i].intArray[9]) == 13) {
            // Iterate index to store next word attributes
            i++;
        }
    }
    // Close file and return wordLibrary struct pointer
    fclose(file);
    return wordLibrary;
}

// Returns array of pos neg nue and compound scores os sentence string passed
float *analyze_sentiment(const char *sentence, WordData *lexicon, int lexicon_size) {
    char sentence_copy[1024];
    strcpy(sentence_copy, sentence);

    // Initialize score values to 0
    float pos = 0.0;
    float neg = 0.0;
    float neu = 0.0;
    float abs_total_score = 0.0;
    float total_sentiment = 0.0; 

    // Initialize counter values to 0
    int numIntense = 0;
    int numLexicon = 0;
    int previous_was_intensifier = 0;
    int previous_was_negation = 0;
    int previous_intense_allcaps = 0;

    // Count the number of tokens in the sentence
    int numWords = 0;
    char *token = strtok(sentence_copy, " ,.!?");
    while (token != NULL) {
        numWords++;

        // Check if the word is in ALLCAPS
        int word_is_allcaps = 1;
        for (int i = 0; token[i] != '\0'; i++) {
            if (!isupper(token[i])) {
                word_is_allcaps = 0;
                break;
            }
        }

        // Normalize the word to lowercase for lexicon comparison
        char word[MAX_STRING_LENGTH];
        int i = 0;
        for (i = 0; token[i] != '\0'; i++) {
            word[i] = tolower(token[i]);
        }
        word[i] = '\0';

        // Check if the word is in the lexicon
        for (int i = 0; i < lexicon_size; i++) {
            if (strcmp(word, lexicon[i].word) == 0) {

                float sentiment = lexicon[i].value1;
                float intense_boost;

                // Apply the rules: intensifiers, negation, ALLCAPS, punctuation
                intense_boost = apply_intensifier(previous_was_intensifier, previous_intense_allcaps);
                previous_was_intensifier = 0;
                previous_intense_allcaps = 0;

                sentiment = apply_negation(sentiment, previous_was_negation);
                previous_was_negation = 0;

                sentiment = apply_allcaps(sentiment, word_is_allcaps ? token : "");
                sentiment = apply_punctuation(sentence, token, sentiment);

                sentiment = sentiment + sentiment * intense_boost;

                if (sentiment > 0.0) {
                    pos += sentiment;
                } else if (sentiment < 0.0) {
                    neg += sentiment;
                }

                total_sentiment += sentiment;
                numLexicon++;
                break;
            }
        }

        if (is_intensifier(word) != 0) {
            previous_was_intensifier = is_intensifier(word);
            numIntense++;
            if (word_is_allcaps == 1) {
                previous_intense_allcaps = 1;
            }
        }
        if (is_negation(word)) {
            previous_was_negation = 1;
        }

        // Move to the next token
        token = strtok(NULL, " ,.!?");
    }

    // Calculate pos, neg, and neu scores
    neu = numWords - numLexicon - numIntense;
    abs_total_score = pos - neg + neu;
    pos = pos / abs_total_score;
    neg = (neg == 0) ? 0.0 : -neg / abs_total_score;
    neu = neu / abs_total_score;

    // Calculate compound score
    float compound = total_sentiment / sqrt(total_sentiment * total_sentiment + ALPHA);

    float *sentiment_scores = malloc(4 * sizeof(float));
    sentiment_scores[0] = pos;
    sentiment_scores[1] = neg;
    sentiment_scores[2] = neu;
    sentiment_scores[3] = compound;

    return sentiment_scores;
}
