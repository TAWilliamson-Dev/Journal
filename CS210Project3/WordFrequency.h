#ifndef CS210PROJECT3_WORDFREQUENCY
#define CS210PROJECT3_WORDFREQUENCY

#include <string>
#include <map>
#include <fstream>
#include <iostream>
using namespace std;

/*
	Private member attributes
	m_line       - string read from m_sourceFile
	m_autosave   - destination file for autosave of m_itemMap
	m_itemMap    - <string, int> pairs of words and their frequency
			 	   as read from m_sourceFile
	m_sourceFile - source file ifstream to read, default for the program is 
					"CS210_Project_Three_Input_File.txt"
	m_backup     - ofstream generated using m_autosave
	m_average	 - average of the frequency of occurence of the words from m_sourceFile

	Private member functions
	m_BuildMap() - Populates the map m_itemMap.
	m_Save()	 - Generates a backup of m_itemMap to the file m_autosave
*/
class WordFrequency {

private:
	string m_line; 
	string const m_autosave = "frequency.dat";
	map<string, int> m_itemMap;
	ifstream m_sourceFile;
	ofstream m_backup;
	int m_average;
private:
	void m_BuildMap();
	void m_Save();
public:
	WordFrequency();
	WordFrequency(string source);
	void DisplayMenu();
	int GetWordFrequencyOnly(string word);
	void PrintWordFrequencyPairs();
	void PrintWordFrequencyHistogram();
};

#endif