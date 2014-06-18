solver
======

Scrabble Solver
Copyright Connor Holm 2014

Python script that determines all possible words from a given input of
letters. Prints those words with their associated point value.

Currently works without sorting the words by point value, would like to
do this by implementing a priority queue. I'd like to eliminate the 
repeated deepcopy of the input letters. Also I believe I can speed up the
algorithm for determining the matches.

Does not support inputting "blank" tiles yet.
