What is Vader Sentiment Analysis?
 Vader Sentiment Analysis is a Natural Language Processing technique used to determine
 the sentiment of various sentence strings. This analysis becomes useful in deciphering the
 emotions behind text within various media. This report follows basic rules and does not
 decipher more complex strings that include emoticons or other complex elements. This
 program was implemented using C and utilized memory allocation. Improvements in the
 future can be made by storing the words from the lexicon file in a hashmap.

Rules Implemented within program
 All Capital cases:
  In the case of a lexicon word having all capital characters, the program will multiply the
  sentiment score and boost it by a factor of 1.5. For non lexicon words, all capital cases
  are neutral.
 Punctuation Cases:
  If there is an exclamation mark directly after a lexicon word, the sentiment score is
  boosted by a factor of 1.292. If there are multiple exclamation marks, the logic follows
  1+n(0.292) where n is the number of exclamation marks. This number however is capped
  at 3 so additional exclamation marks have no impact on the sentiment score of the word.
  Exclamation marks following non-lexicon words are neutral and have no effect on the
  total score.
 Negation Cases:
  If a negation word such as “not” or “isn’t” is detected in the sentence, the next lexicon
  word detected will be multiplied by a factor of-0.5 to negate the sentiment and slightly
  suppress it. Non-lexicon words following negations remain neutral. NOTE: negation
  words are counted as neutral within the program.
 Intensifiers:
  Intensifier words such as “very” and “uber” add a boost to the sentiment value. This
  boost is an addition of 0.293 to the sentiment score. If the intensifier is an all capital case,
  the boost is boosted by 1.5. Intensifiers have no effect on non-lexicon words. NOTE:
  intensifier words are counted as non-neutral in the program
