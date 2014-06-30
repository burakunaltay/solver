#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <fstream>
#include <algorithm>
#include <cctype>

using namespace std;

struct Matchword {
	unsigned points;
	string word;
	
	Matchword(): points(0) {}
	Matchword(string word_in): points(0), word(word_in) {}

};
struct Word_comparator {

		Word_comparator() {}

		bool operator() (Matchword a, Matchword b) const {
			if(a.points < b.points) 
				return true;
			else if(b.points < a.points)
				return false;
			else if(a.word < b.word)
				return true;
			else if(b.word < a.word)
				return false;
			else
				return true;
		}
};

typedef unordered_map<char, int> Lettermap;

Lettermap point_map ({{'A', 1}, {'C', 3}, { 'B', 3}, {'E', 1}, {'D', 2}, {'G', 2},
	{'F', 4}, {'I', 1}, {'H', 4}, {'K', 5}, {'J', 8}, {'M', 3}, {'L', 1},
	{'O', 1}, {'N', 1}, {'Q', 10}, {'P', 3}, {'S', 1}, {'R', 1}, {'U', 1}
	,{'T', 1}, {'W', 4}, {'V', 4}, {'Y', 4}, {'X', 8}, {'Z', 10} } 
	);


int main() {

	ifstream infile;
	infile.open("sowpods.txt");
	priority_queue<Matchword, vector<Matchword>, Word_comparator> match_queue;
	
	unordered_set<string> wordlist;
	string word;
	while(!infile.eof()) {
		infile>>word;
		wordlist.insert(word);
	}

	cout<<"Enter your letters(without any spaces): ";
	cin>>word;

	int match = 0;
	int length = word.length();
	unordered_map<char, int> letters;
	for(int i = 0; i < length; i++) {
		if(letters[toupper(word[i])])
			letters[toupper(word[i])]++;
		else
			letters[toupper(word[i])] = 1;
	}

	for(auto temp:wordlist) {
		match = 0;
		unordered_map<char, int> seen;
		if(temp.length() > length)
			continue;

		for(int i = 0; i < temp.length(); i++) {
			if(letters.count(temp[i])) {
					match++;

					auto find = seen.find(temp[i]);

					if(find != seen.end()) { 
						if(find->second < letters[find->first])
							seen[find->first]++;
						else
							break;
					}
					else
						seen[temp[i]] = 1;
			}
		}
		if (match == temp.length()) {
			Matchword mymatch(temp);
			for(int i = 0; i < temp.length(); i++)
				mymatch.points += point_map[temp[i]];
			match_queue.push(mymatch);
		}
	}

	while(!match_queue.empty()) {
		Matchword temp = match_queue.top();
		match_queue.pop();
		cout<<temp.word<<" "<<temp.points<<endl;
	}
}
//need to define less than comp to create priority queue
//then also use a vec/list for all the words matched, iterate through list to put
					//in priority queue, print pqueue
