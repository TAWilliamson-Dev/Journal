/*
*   Course:       CS-210-11083-M01
*   Instructor:   Felicia Rosemond
*   Student:      Travis Williamson
*   Assignment:	  Project 3
*   Date:		  6/22/2024
*/


#include "WordFrequency.h"
using namespace std;

/*
	Takes a unique_ptr<WordFrequency> reference.
	Prints the number of times that a user specified word appears 
	in the file associated with the WordFrequency object.
	Calls the GetWordFrequencyOnly(string) member method of the 
	associated WordFrequency object.
*/
void PrintWordFrequency(unique_ptr<WordFrequency> &t_wordFrequency) {	
	string word;
	int freq;

	cout << "Enter the word you would like to know the frequency of:" << endl;
	cin >> word;

	freq = t_wordFrequency->GetWordFrequencyOnly(word);

	cout << word << " appears " << freq << " times in the list." << endl << endl;
}

/*
	Creates a unique_ptr<WordFrequency> to a new WordFrequency object, using
	the file CS210_Project_Three_input_file.txt for input.

	Prompts the user to select an option (1-4):
	Option 1: Print the frequency of a specific word
	Option 2: Print the frequency of all words in the WordFrequency objects associated Map<string, int>
	Option 3: Print the frequency of all words in the WordFrequency objects associated Map<string, int>
			  as a histogram.
	Option 4: Exit Program

	If any other character is entered, program defaults to exit program.
*/
int main() {

	int userOption = 0;
	unique_ptr<WordFrequency> wordFrequency( new WordFrequency("CS210_Project_Three_Input_File.txt"));

	while (userOption >= 0 && userOption < 4) {
		wordFrequency->DisplayMenu();
		cin >> userOption;

		switch (userOption) {
		case 1:
			PrintWordFrequency(wordFrequency);
			break;
		case 2:
			wordFrequency->PrintWordFrequencyPairs();
			break;
		case 3:
			wordFrequency->PrintWordFrequencyHistogram();
			break;
		case 4:
		default:
			return 0;
		}
		system("PAUSE");
	}	
	return 0;
}