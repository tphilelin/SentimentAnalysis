#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "utility.h"


int main(){
    // Create lexicon size 
    int lexicon_size;
    // Initialize lexicon struct pointer with word attributes 
    WordData* lexicon = getWordData("vader_lexicon.txt", &lexicon_size);
    // Initialize sentence strings 
    const char *sentence1 = "VADER is smart, handsome, and funny.";
    const char *sentence2 = "VADER is smart, handsome, and funny!";
    const char *sentence3 = "VADER is very smart, handsome, and funny.";
    const char *sentence4 = "VADER is VERY SMART, handsome, and FUNNY.";
    const char *sentence5 = "VADER is VERY SMART, handsome, and FUNNY!!!";
    const char *sentence6 = "VADER is VERY SMART, uber handsome, and FRIGGIN FUNNY!!!";
    const char *sentence7 = "VADER is not smart, handsome, nor funny.";
    const char *sentence8 = "At least it isn’t a horrible book.";
    const char *sentence9 = "The plot was good, but the characters are uncompelling and the dialog is not great.";
    const char *sentence10 = "Make sure you :) or :D today!";
    const char *sentence11 = "Not bad at all";

    // Get scores 
    float *score1 = analyze_sentiment(sentence1, lexicon, lexicon_size);
    float *score2 = analyze_sentiment(sentence2, lexicon, lexicon_size);
    float *score3 = analyze_sentiment(sentence3, lexicon, lexicon_size);
    float *score4 = analyze_sentiment(sentence4, lexicon, lexicon_size);
    float *score5 = analyze_sentiment(sentence5, lexicon, lexicon_size);
    float *score6 = analyze_sentiment(sentence6, lexicon, lexicon_size);
    float *score7 = analyze_sentiment(sentence7, lexicon, lexicon_size);
    float *score8 = analyze_sentiment(sentence8, lexicon, lexicon_size);
    float *score9 = analyze_sentiment(sentence9, lexicon, lexicon_size);
    float *score10 = analyze_sentiment(sentence10, lexicon, lexicon_size);
    float *score11 = analyze_sentiment(sentence11, lexicon, lexicon_size);

    // Print scores 
    printf("'VADER is smart, handsome, and funny.'\n    compound: %.4f\n    pos: %.4f   neg: %.4f\n    neu: %.4f\n\n", score1[3], score1[0],score1[1], score1[2]);
    printf("'VADER is smart, handsome, and funny!'\n    compound: %.4f\n    pos: %.4f   neg: %.4f\n    neu: %.4f\n\n", score2[3], score2[0], score2[1], score2[2]);
    printf("'VADER is very smart, handsome, and funny.'\n    compound: %.4f\n    pos: %.4f   neg: %.4f\n    neu: %.4f\n\n", score3[3], score3[0], score3[1], score3[2]);
    printf("'VADER is VERY SMART, handsome, and FUNNY.'\n    compound: %.4f\n    pos: %.4f   neg: %.4f\n    neu: %.4f\n\n", score4[3], score4[0], score4[1], score4[2]);
    printf("'VADER is VERY SMART, handsome, and FUNNY!!!'\n    compound: %.4f\n    pos: %.4f   neg: %.4f\n    neu: %.4f\n\n", score5[3], score5[0], score5[1], score5[2]);
    printf("'VADER is VERY SMART, uber handsome, and FRIGGIN FUNNY!!!'\n    compound: %.4f\n    pos: %.4f   neg: %.4f\n    neu: %.4f\n\n", score6[3], score6[0], score6[1], score6[2]);
    printf("'VADER is not smart, handsome, nor funny.'\n    compound: %.4f\n    pos: %.4f   neg: %.4f\n    neu: %.4f\n\n", score7[3], score7[0], score7[1], score7[2]);
    printf("Compound Sentiment Score of string 'At least it isn’t a horrible book.'\n    compound: %.4f\n    pos: %.4f   neg: %.4f\n    neu: %.4f\n\n", score8[3], score8[0], score8[1], score8[2]);
    printf("Compound Sentiment Score of string 'The plot was good, but the characters are uncompelling and the dialog is not great.'\n    compound: %.4f\n    pos: %.4f   neg: %.4f\n    neu: %.4f\n\n", score9[3], score9[0], score9[1], score9[2]);
    printf("Compound Sentiment Score of string 'Make sure you :) or :D today!'\n    compound: %.4f\n    pos: %.4f   neg: %.4f\n    neu: %.4f\n\n", score10[3], score10[0], score10[1], score10[2]);
    printf("Compound Sentiment Score of string 'Not bad at all'\n    compound: %.4f\n    pos: %.4f   neg: %.4f\n    neu: %.4f\n\n", score11[3], score11[0], score11[1], score11[2]);

    free(lexicon); // Free memory
    free(score1);
    free(score2);
    free(score3);
    free(score4);
    free(score5);
    free(score6);
    free(score7);
    free(score8);
    free(score9);
    free(score10);
    free(score11);
}