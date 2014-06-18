#!/usr/local/bin/python3

import re
from copy import deepcopy

def main():

	scores = {"A": 1, "C": 3, "B": 3, "E": 1, "D": 2, "G": 2,
		"F": 4, "I": 1, "H": 4, "K": 5, "J": 8, "M": 3, "L": 1,
		"O": 1, "N": 1, "Q": 10, "P": 3, "S": 1, "R": 1, "U": 1,
		"T": 1, "W": 4, "V": 4, "Y": 4, "X": 8, "Z": 10}

	#generate list of all possibles words
	file = open("sowpods.txt")
	wordlist = [line.strip() for line in file]
	
	#get user's letters and format them
	inletters = input('Input your letters: ').upper()
	inletters = re.sub(r'\s+', '', inletters)
	letter_dict = {}
	for l in inletters:
		if l in letter_dict:
			letter_dict[l] += 1
		else:
			letter_dict[l] = 1
	
	match_dict = {}
	#for every possible word, see if letters of word match letters given
	for word in wordlist:
		match = 0
		temp_dict = deepcopy(letter_dict)

		if len(word) > len(inletters):
			continue
		
		for letter in word:
			if letter in temp_dict:
				match += 1
				temp_dict[letter] -= 1
				if(temp_dict[letter] == 0):
					del temp_dict[letter]
			else:
			  break

		if(match == len(word)):
			match_dict[word] = 0
			for l in word:
				match_dict[word] += scores[l]
			print(match_dict[word], word)


if __name__ == "__main__": main()
