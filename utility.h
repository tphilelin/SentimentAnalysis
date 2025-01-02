#ifndef UTILITY_H
#define UTILITY

// Define constant vals 
#define ARRAY_SIZE 10
#define MAX_STRING_LENGTH 20
#define MAX_LINE_LENGTH 1024 
#define CAPS_FACTOR 1.5 
#define INTENSE_SCORE 0.293
#define PUNC_FACTOR 0.292
#define ALPHA 15.0
#define MAX_EXCLAMATION_COUNT 3 
#define NEGATION_FACTOR -0.5

// Define WordData struct
typedef struct {
    char word [MAX_STRING_LENGTH];
    float value1 ; // sentiment value
    float value2 ; // standard deviation
    int intArray [ARRAY_SIZE]; // array of sentiment ratings
} WordData ;

// Check if a word is an intensifier
int is_intensifier(const char *word);

// Apply the intensifier boost
float apply_intensifier(int intenseIndex, int intenseCaps);

// Check if a word is a negation
int is_negation(const char *word);

// Apply the negation factor
float apply_negation(float sentiment, int previous_was_negation);

// Apply the ALLCAPS boost
float apply_allcaps(float sentiment, const char *word);

// Apply punctuation boost (exclamation marks)
float apply_punctuation(const char *sentence, const char *word, float sentiment);

// Get pointer struct with word attributed 
WordData* getWordData(const char *filename, int *numWords);

// Get scores of sentence strings 
float *analyze_sentiment(const char *sentence, WordData *lexicon, int lexicon_size);

#endif