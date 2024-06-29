#include "WordFrequency.h";

string m_line;
map<string, int> m_itemsMap;
ifstream m_source;
ofstream m_backup;
int m_average;

/*
	Default constructor, unused for the application.
	Sets m_average to -1, does not enable further use of the application.
*/
WordFrequency::WordFrequency() {
	m_average = -1;
}

/*
	Constructor for the WordFrequency object.
	Takes in the source file as a string, passed by main() as
	"CS210_Project_Three_Input_File.txt". Attempts to open an ifstream on
	the source file. If successful, invokes the m_BuildMap() and m_Save()
	member functions, generating and backing up the Map for use in the program.
	Then closes the ifstream.
*/
WordFrequency::WordFrequency(string source) {
	try {
		m_source.open(source); //"CS210_Project_Three_Input_File.txt"
		m_BuildMap();
		m_Save();
		m_source.close();
	}
	catch (const std::ios_base::failure& fail) {
		cout << fail.what() << endl;
		cout << "Unable to open file: " << source;
	}
}

/*
	Reads the contents of m_source, if m_source is open.
	For each word, if the word is not already in the map
	then the word is inserted into the map with a frequency of 1.
	Otherwise, the frequency of the word is incremented by one.
*/
void WordFrequency::m_BuildMap() {
	if (m_source.is_open()) {
		do {
			getline(m_source,m_line);

			if (m_itemsMap.find(m_line) == m_itemsMap.end()) {
				m_itemsMap.insert(pair<string, int>{ m_line, 1 });
			}
			else {
				m_itemsMap.at(m_line) += 1;
			}
		} while (!m_source.eof());
	}
}

/*
	Creates/Overwrites the defined m_autosave file, 
	m_autosave is declared in the header file.
	Determines the average of the values in the map, for output formatting.
*/
void WordFrequency::m_Save() {
	m_backup.open(m_autosave);
	for (auto itr = m_itemsMap.begin(); itr != m_itemsMap.end(); ++itr) {
		m_backup << itr->first << '\t' << itr->second << '\n';
		m_average += itr->second;
	}
	m_average = m_average / m_itemsMap.size();
	m_backup.close();
}

/*
	Displays main menu to console.
*/
void WordFrequency::DisplayMenu() {
	cout << "************************************************************************" << endl;
	cout << "****************************** Main Menu *******************************" << endl;
	cout << "| Enter 1-4 to select from the following options.                      |" << endl;
	cout << "| Option 1: Get the frequency that a certain word appears in the list. |" << endl;
	cout << "| Option 2: Get the frequency of all words in the list.                |" << endl;
	cout << "| Option 3: Get the frequency of all words in the list as a histogram. |" << endl;
	cout << "| Option 4: Exit program                                               |" << endl;
	cout << "************************************************************************" << endl;
}

/*
	Returns the int value of the objects associated Map<string,int> 
	if the word exists in the map, else returns 0.
*/
int WordFrequency::GetWordFrequencyOnly(string word) {

	if (m_itemsMap.find(word) != m_itemsMap.end()) {
		return m_itemsMap.at(word);
	}
	else {
		return 0;
	}
}

/*
	Prints the Word:Frequency pairs from m_itemsMap as a formatted table.
	Color codes text for items with average to 150% average frequency in yellow.
	Items that appear more than 150% the average rate are color coded in green.
*/
void WordFrequency::PrintWordFrequencyPairs() {
	string wordBuffer = "|                     ",
		   countBuffer = "|               ";

	string count;

	int wordBufferOffset = 2, 
		countBufferOffset = 5;

	cout << "==================================" << endl;
	cout << "|       Word        | Frequency  |" << endl;
	cout << "==================================" << endl;
	for (auto itr = m_itemsMap.begin(); itr != m_itemsMap.end(); ++itr) {
		wordBuffer.replace(wordBufferOffset, itr->first.size() + wordBufferOffset, itr->first);

		count = to_string(itr->second);

		if (itr->second > m_average*1.5) {
			countBuffer.replace(countBufferOffset, count.size() + countBufferOffset, "\033[3;40;92m" + count + "\033[0m\ ");
		}
		else if (itr->second >= m_average) {
			countBuffer.replace(countBufferOffset, count.size() + countBufferOffset, "\033[3;40;93m" + count + "\033[0m\ ");
		}
		else {
			countBuffer.replace(countBufferOffset, count.size() + countBufferOffset, "\033[3;40;97m" + count + "\033[0m\ ");
		}
		countBuffer.append(" |");
		cout << wordBuffer << countBuffer << endl;
		wordBuffer = "|                     ";
		countBuffer = "|               ";
	}
	cout << "==================================" << endl << endl;
}

/*
	Prints the Word:Frequency pairs from m_itemsMap as a formatted table with
	frequency as a histogram.
	Color codes text for items with average to 150% average frequency in yellow.
	Items that appear more than 150% the average rate are color coded in green.
*/
void WordFrequency::PrintWordFrequencyHistogram() {
	string wordBuffer;
	string countBuffer;
	string histogram;

	int wordBufferOffset = 2;
	int countBufferOffset = 2;

	cout << "======================================" << endl;
	cout << "|       Word        |   Frequency    |" << endl;
	cout << "======================================" << endl;

	for (auto itr = m_itemsMap.begin(); itr != m_itemsMap.end(); ++itr) {

		wordBuffer = "|                     ";
		countBuffer = "|              ";
		histogram = "";

		for (int i = 0; i < itr->second; ++i) {
				histogram.push_back('\xDC');
		}

		wordBuffer.replace(wordBufferOffset, itr->first.size() + wordBufferOffset, itr->first);		

		if (histogram.size() > m_average*1.5) {
			countBuffer.replace(countBufferOffset, histogram.size(), "\033[3;40;92m" + histogram + "\033[0m\ ");
		}
		else if (histogram.size() >= m_average) {
			countBuffer.replace(countBufferOffset, histogram.size(), "\033[3;40;93m" + histogram + "\033[0m\ ");
		}
		else {
			countBuffer.replace(countBufferOffset, histogram.size(), "\033[3;40;97m" + histogram + "\033[0m\ ");
		}
		countBuffer.append(" |");
		cout << wordBuffer << countBuffer << endl;
	}
	cout << "======================================" << endl << endl;
}