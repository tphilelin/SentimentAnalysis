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
 intensifier words are counted as non-neutral in the program.
PythonImplementation
 Thepythonimplementationofthesameprogrammayusedifferentlogic.Atable
 comparingonesuchpythonimplementationandthecimplementationusingthe
 compoundvaluesofsentencestringscanbeseenbelow.
 String(sentencestring) C(compoundscore) Python(compoundscore)
 VADERissmart,
 handsome,andfunny.
 0.8316 0.8316
 VADERissmart,
 handsome,andfunny!
 0.8539 0.8439
 VADERisverysmart,
 handsome,andfunny.
 0.8518 0.8545
 VADERisVERYSMART,
 handsome,andFUNNY.
 0.9139 0.9227
 VADERisVERYSMART,
 handsome,andFUNNY!!!
 0.9452 0.9342
 VADERisVERYSMART,
 uberhandsome,and
 FRIGGINFUNNY!!!
 0.9506 0.9469
 VADERisnotsmart,
 handsome,norfunny.
 0.1027-0.7424
 Atleastitisn’tahorrible
 book.
 0.3071 0.431
 Theplotwasgood,butthe
 charactersare
 uncompellingandthe
 dialogisnotgreat.-0.1406 0.094
 Makesureyou:)or:D
 today!
 0.8225 0.8633
 Notbadatall 0.3071 0.431
 CScores:
'VADER is smart, handsome, and funny.'
 compound: 0.8316
 pos: 0.6591 neg: 0.0000
 neu: 0.3409
 'VADER is smart, handsome, and funny!'
 compound: 0.8539
 pos: 0.6793 neg: 0.0000
 neu: 0.3207
 'VADER is very smart, handsome, and funny.'
 compound: 0.8518
 pos: 0.6774 neg: 0.0000
 neu: 0.3226
 'VADER is VERY SMART, handsome, and FUNNY.'
 compound: 0.9139
 pos: 0.7440 neg: 0.0000
 neu: 0.2560
 'VADER is VERY SMART, handsome, and FUNNY!!!'
 compound: 0.9452
 pos: 0.7890 neg: 0.0000
 neu: 0.2110
 'VADER is VERY SMART, uber handsome, and FRIGGIN FUNNY!!!'
 compound: 0.9506
 pos: 0.7478 neg: 0.0000
 neu: 0.2522
 'VADER is not smart, handsome, nor funny.'
 compound: 0.1027
 pos: 0.2750 neg: 0.2250
 neu: 0.5000
 Compound Sentiment Score of string 'At least it isn’t a
 horrible book.'
 compound: 0.3071
pos: 0.1724 neg: 0.0000
 neu: 0.8276
 Compound Sentiment Score of string 'The plot was good, but
 the characters are uncompelling and the dialog is not
 great.'
 compound:-0.1406
 pos: 0.1162 neg: 0.1498
 neu: 0.7339
 Compound Sentiment Score of string 'Make sure you :) or :D
 today!'
 compound: 0.8225
 pos: 0.5833 neg: 0.0000
 neu: 0.4167
 Compound Sentiment Score of string 'Not bad at all'
 compound: 0.3071
 pos: 0.2941 neg: 0.0000
 neu: 0.7059
 Python Scores:
 VADERis smart, handsome, and funny.----------------------------- {'pos': 0.746, 'compound': 0.8316, 'neu': 0.254,
 'neg': 0.0}
 VADERis smart, handsome, and funny!----------------------------- {'pos': 0.752, 'compound': 0.8439, 'neu': 0.248,
 'neg': 0.0}
 VADERis very smart, handsome, and funny.------------------------ {'pos': 0.701, 'compound': 0.8545, 'neu': 0.299,
 'neg': 0.0}
 VADERis VERYSMART,handsome, and FUNNY.------------------------ {'pos': 0.754, 'compound': 0.9227, 'neu':
 0.246, 'neg': 0.0}
 VADERis VERYSMART,handsome, and FUNNY!!!---------------------- {'pos': 0.767, 'compound': 0.9342, 'neu':
 0.233, 'neg': 0.0}
 VADERis VERYSMART,uber handsome, and FRIGGIN FUNNY!!!--------- {'pos': 0.706, 'compound': 0.9469,
 'neu': 0.294, 'neg': 0.0}
 VADERis not smart, handsome, nor funny.------------------------- {'pos': 0.0, 'compound':-0.7424, 'neu': 0.354, 'neg':
 0.646}
 At least it isn't a horrible book.------------------------------- {'pos': 0.363, 'compound': 0.431, 'neu': 0.637, 'neg': 0.0}
 The plot was good, but the characters are uncompelling and the dialog is not great. {'pos': 0.094, 'compound':-0.7042, 'neu': 0.579, 'neg': 0.327}
 Make sure you :) or :D today!------------------------------------ {'pos': 0.706, 'compound': 0.8633, 'neu': 0.294, 'neg':
 0.0}
Not bad at all--------------------------------------------------- {'pos': 0.487, 'compound': 0.431, 'neu': 0.513, 'neg': 0.0}
 Compiling and Running program
 The Makefile included in the program allows for easy compilation. If the Makefile is
 downloaded, the program can be compiled by running ‘make’ within the terminal where
 the Makefile as well as other code files and vader_lexicon.txt are downloaded. If the
 Makefile is not downloaded, the program can be compiled using a command listed below.
 If Makefile is downloaded:
 >make
 If Makefile is not downloaded:
 >gcc vaderSentiment.c main.c-o vader-lm-Wall-Wextra
 Then, by running the below command within the terminal, the program can run.
 >./vader
 To remove the object file there are again 2 options
 If Makefile is downloaded:
 >make clean
 If Makefile is not downloaded:
 >rm vader
