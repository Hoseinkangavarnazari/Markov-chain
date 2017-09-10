#include <iostream> 
#include <string> 
#include <cstdlib> 
#include <sstream> 
#include <fstream>
#include <vector> 
#include <list>

using namespace std;

struct word{
	string text = "";
};
class sentence{
public:
	vector<word> word;
	int value = 0;
};
class sentences {
public:
	vector<sentence> sentence;
};

//..........................................Globals...............................................
int ** varzeshi_table;
int ** entertainment_table;
vector<string> dictionary;
//std::ios::app is the open mode "append" meaning
//new data will be written to the end of the file.
ofstream out;
int Gstart = 0;
int Gend = 600;
int sLanda = 1;
int eLanda = 1;
//.........................................lowercase..............................................
//.................................Turns a WORD to lowerCase......................................
void cChanger(string &word){
	int c = 0;
	char ch;

	while (word[c] != '\0') {
		ch = word[c];
		if (ch >= 'A' && ch <= 'Z')
			word[c] = word[c] + 32;
		c++;
	}

}


//****************************************Forward decleration.....................................
void fillArray(string word, string parent, string type);
void findSE(int &start, int &end, char fWord);

//.......................................Show result..............................................
void show(int index, double pSport, double pEntertainment){
	//**********************************************************instruction to use**********************************************************
	//in your current function do :
	/*out.open("showFlile.txt", ios::app);
	show(index, pSport, pEntertainment);
	out.close();*/
	//in globals define :
	/*ofstream out;
	*/


	if (index >= 0 && index <= 9){
		if (pSport >= 0 && pSport <= 9){
			out << index << "    :   " << "p(sport) =  " << (pSport / sLanda) << "%     |    " << "p(Entertainment) =  " << (pEntertainment / eLanda) << "%" << endl;
		}
		else{
			out << index << "    :   " << "p(sport) =  " << (pSport / sLanda) << "%    |    " << "p(Entertainment) =  " << (pEntertainment / eLanda) << "%" << endl;
		}
	}
	if (index >= 10 && index <= 99){
		if (pSport >= 0 && pSport <= 9){
			out << index << "   :   " << "p(sport) =  " << (pSport / sLanda) << "%     |    " << "p(Entertainment) =  " << (pEntertainment / eLanda) << "%" << endl;
		}
		else{
			out << index << "   :   " << "p(sport) =  " << (pSport / sLanda) << "%    |    " << "p(Entertainment) =  " << (pEntertainment / eLanda) << "%" << endl;
		}
	}
	if (index >= 100 && index <= 999){
		if (pSport >= 0 && pSport <= 9){
			out << index << "  :   " << "p(sport) =  " << (pSport / sLanda) << "%     |    " << "p(Entertainment) =  " << (pEntertainment / eLanda) << "%" << endl;
		}
		else{
			out << index << "  :   " << "p(sport) =  " << (pSport / sLanda) << "%    |    " << "p(Entertainment) =  " << (pEntertainment / eLanda) << "%" << endl;
		}
	}
	if (index >= 1000 && index <= 9999){
		if (pSport >= 0 && pSport <= 9){
			out << index << " :   " << "p(sport) =  " << (pSport / sLanda) << "%     |    " << "p(Entertainment) =  " << (pEntertainment / eLanda) << "%" << endl;
		}
		else{
			out << index << " :   " << "p(sport) =  " << (pSport / sLanda) << "%    |    " << "p(Entertainment) =  " << (pEntertainment / eLanda) << "%" << endl;
		}
	}

}

//....................................PrePosition result..........................................
bool clear_preposition(string word, vector<string> preposition){
	bool result = false;
	for (int i = 0; i < preposition.size(); i++){
		if (preposition[i] == word){
			result = true;
			break;
		}
	}
	// age true bargardone yani bayad hazf she 
	return result;
}

//.................................Reading proposition from file..................................
void readPreposition(vector<string> &preposition){

	ifstream dataRead;
	dataRead.open("extras.txt");
	string temp;
	while (!dataRead.eof()){
		dataRead >> temp;
		preposition.push_back(temp);
	}
}

void readFromFile(sentences* storage, const string Context, vector<string> preposition){

	ifstream dataRead;
	ofstream testwrite;
	testwrite.open("testw.txt");
	string path = "";
	dataRead.open("sport/001.txt");
	string test;
	dataRead >> test;


	int fileCounter = 0;
	//all file reader
	while (fileCounter < 150){
		fileCounter++;

		//begining of file path generator++++++++++++++++++++++
		if (Context == "sport"){
			path = "sport/";
			if (fileCounter < 10){
				path += "00" + std::to_string(fileCounter) + ".txt";
			}
			else if (fileCounter >= 10 && fileCounter < 100) {
				path += "0" + std::to_string(fileCounter) + ".txt";
			}
			else{
				path += std::to_string(fileCounter) + ".txt";
			}
		}
		else if (Context == "entertainment"){
			path = "entertainment/";
			if (fileCounter < 10){
				path += "00" + std::to_string(fileCounter) + ".txt";
			}
			else if (fileCounter >= 10 && fileCounter < 100) {
				path += "0" + std::to_string(fileCounter) + ".txt";
			}
			else{
				path += std::to_string(fileCounter) + ".txt";
			}
		}
		//end of file path generator------------------------------

		//start reading single file ++++++++++++++++++++++++++++++
		dataRead.close();  // age ghablio nabandi , on yekio ke va mikone dochare moshkel mishe 
		dataRead.open(path);

		string line = "";
		string fullText = "";

		getline(dataRead, line);
		fullText += line + '.';
		while (!dataRead.eof()){
			getline(dataRead, line);
			fullText += line;
		}

		//Sentence Reader while
		while (fullText != ""){
			sentence temp_s;
			
			//Word reader while
			int counter_table = 0;
			string parent = "";
			while (true){
				counter_table++;
				if (counter_table == 1){
					parent = "";
				}

				word temp_w;
				if (fullText == "." || fullText == "\"" || fullText == "'\""){
					fullText = "";
					break;
				}
				if (fullText[0] == '(' || fullText[0] == ')' || fullText[0] == '\'' || fullText[0] == 'آ' || fullText[0] == '&' || fullText[0] == '\"' || fullText[0] == ' ' || fullText[0] == ':' || fullText[0] == ',' || fullText[0] == '.' || fullText[0] == '-' && fullText.size()>0){
					fullText = fullText.substr(1, fullText.size());
					continue;
				}

				int space_pos = fullText.find_first_of(" ");
				int dot_pos = fullText.find_first_of(".");
				int pos = 0;
				bool end_sentence = false;
				if ((dot_pos != -1 && dot_pos < space_pos) || space_pos == -1){
					end_sentence = true;
					pos = dot_pos;
				}
				else{
					pos = space_pos;
				}
				if (dot_pos == -1 && space_pos == -1){
					pos = fullText.size();
				}

				temp_w.text = fullText.substr(0, pos);
				fullText.erase(0, pos + 1);

				while (temp_w.text[temp_w.text.size() - 1] == ')' || temp_w.text[temp_w.text.size() - 1] == ',' || temp_w.text[temp_w.text.size() - 1] == ':' || temp_w.text[temp_w.text.size() - 1] == ';' && temp_w.text.size() > 0 || temp_w.text[temp_w.text.size() - 1] == '\"'){
					temp_w.text = temp_w.text.substr(0, temp_w.text.size() - 1);
				}

				// age jozve horofe nabashe inja ezafe kon be barname 
				if (!clear_preposition(temp_w.text, preposition)){
					cChanger(temp_w.text);

					if (counter_table == 1){

						fillArray(temp_w.text, "", Context);
					}
					else{

						fillArray(temp_w.text, parent, Context);
					}

					temp_s.word.push_back(temp_w);
					parent = temp_w.text;
				}
				if (end_sentence){
					break;
				}
			}
			storage->sentence.push_back(temp_s);
		}
	}
}

void readFromFile_learn(sentences* storage, const string Context, vector<string> preposition){

	ifstream dataRead;
	ofstream testwrite;
	testwrite.open("testw.txt");
	string path = "";
	dataRead.open("sport/001.txt");
	string test;
	dataRead >> test;


	int fileCounter = 150;

	// all file reader
	while (fileCounter < 200){
		fileCounter++;

		//begining of file path generator
		if (Context == "sport"){
			path = "sport/";
			if (fileCounter < 10){
				path += "00" + std::to_string(fileCounter) + ".txt";
			}
			else if (fileCounter >= 10 && fileCounter < 100) {
				path += "0" + std::to_string(fileCounter) + ".txt";
			}
			else{
				path += std::to_string(fileCounter) + ".txt";
			}
		}
		else if (Context == "entertainment"){
			path = "entertainment/";
			if (fileCounter < 10){
				path += "00" + std::to_string(fileCounter) + ".txt";
			}
			else if (fileCounter >= 10 && fileCounter < 100) {
				path += "0" + std::to_string(fileCounter) + ".txt";
			}
			else{
				path += std::to_string(fileCounter) + ".txt";
			}
		}
		//end of file path generator------------------------------

		//start reading single file ++++++++++++++++++++++++++++++
		dataRead.close();  // age ghablio nabandi , on yekio ke va mikone dochare moshkel mishe 
		dataRead.open(path);
		string line = "";
		string fullText = "";

		getline(dataRead, line);
		fullText += line + '.';
		while (!dataRead.eof()){
			getline(dataRead, line);
			fullText += line;
		}

		//Sentence Reader while
		while (fullText != ""){
			sentence temp_s;
			//Word reader while
			while (true){
				word temp_w;
				if (fullText == "." || fullText == "\"" || fullText == "'\""){
					fullText = "";
					break;
				}
				if (fullText[0] == '(' || fullText[0] == ')' || fullText[0] == '\"' || fullText[0] == ' ' || fullText[0] == ':' || fullText[0] == ',' || fullText[0] == '.' || fullText[0] == '-' && fullText.size()>0){
					fullText = fullText.substr(1, fullText.size());
					continue;
				}

				int space_pos = fullText.find_first_of(" ");
				int dot_pos = fullText.find_first_of(".");
				int pos = 0;
				bool end_sentence = false;
				if ((dot_pos != -1 && dot_pos < space_pos) || space_pos == -1){
					end_sentence = true;
					pos = dot_pos;
				}
				else{
					pos = space_pos;
				}
				if (dot_pos == -1 && space_pos == -1){
					pos = fullText.size();
				}
				temp_w.text = fullText.substr(0, pos);
				if (temp_w.text == "cleared"){
					int y = 0;
					y++;
				}

				fullText.erase(0, pos + 1);

				while (temp_w.text[temp_w.text.size() - 1] == ')' || temp_w.text[temp_w.text.size() - 1] == ',' || temp_w.text[temp_w.text.size() - 1] == ':' && temp_w.text.size()>0 || temp_w.text[temp_w.text.size() - 1] == '\"'){
					temp_w.text = temp_w.text.substr(0, temp_w.text.size() - 1);
				}

				// age jozve horofe nabashe inja ezafe kon be barname 
				if (!clear_preposition(temp_w.text, preposition)){
					temp_s.word.push_back(temp_w);
				}
				if (end_sentence){
					break;
				}
			}
			storage->sentence.push_back(temp_s);
		}
	}
}

vector<string> readDic(void){
	vector<string> storage;
	ifstream dataRead;
	dataRead.open("bbc.txt");
	string temp;
	while (!dataRead.eof()){
		dataRead >> temp;
		storage.push_back(temp);
	}
	return storage;
}

//Function for find a WORD : Start and End
void findSE(int &start, int &end, char fWord){

	string lineDef;
	string temp;
	ifstream map_stream("dicInfo.txt");
	while (!map_stream.eof()){
		map_stream >> lineDef;
		if (lineDef[0] == fWord){

			//filling start
			lineDef = lineDef.substr(2, lineDef.size());
			temp = lineDef.substr(0, lineDef.find_first_of(":"));
			start = stoi(temp);

			//filling end
			lineDef = lineDef.substr(lineDef.find_first_of(":") + 1, lineDef.size());
			end = stoi(lineDef);
		}
	}
}

//Function for find WORD index in BBC
int searchBBC(int start, int end, string word){

	//Creating dictionary

	//dictionary = readDic();

	//initializing index
	int index = start - 1;
	bool flag = false;
	//search in Dictionary from `start` to `end`
	for (int i = start - 1; i < end; i++){
		if (dictionary[i] == word){
			return index;
			flag = true;
		}
		index++;
	}
	if (!flag)
		return -1;
}

//Function to give it the word and it's parent and it plus plus the counter 
void fillArray(string word, string parent, string type){

	char word_first = word[0];
	char parent_first = parent[0];
	// shoro va khateme ro mige jke to bbc bayad to che hlozei begarde
	int start_word = -1;
	int end_word = -1;
	int start_parent = -1;
	int end_parent = -1;

	// this is for index of data tables for example : entertainment_table[index_i][index_j]
	int index_i = -1;
	int index_j = -1;

	findSE(start_word, end_word, word_first);
	if (start_word == -1 || end_word == -1){
		return;
	}
	index_i = searchBBC(start_word, end_word, word);

	if (index_i >= 0){
		if (parent != ""){
			findSE(start_parent, end_parent, parent_first);
			if (start_parent != -1 && end_parent != -1){
				index_j = searchBBC(start_parent, end_parent, parent);
			}
			if (index_j >= 0){
				if (type == "sport"){
					varzeshi_table[index_i][index_j]++;
				}
				else{
					entertainment_table[index_i][index_j]++;
				}
			}
			else{
				if (type == "sport"){
					varzeshi_table[index_i][index_i]++;
				}
				else{
					entertainment_table[index_i][index_i]++;
				}
			}
		}
		else{
			if (type == "sport"){
				varzeshi_table[index_i][index_i]++;
			}
			else{
				entertainment_table[index_i][index_i]++;
			}
		}
	}

}

//Function to find index
int index_finder(string word){

	char word_first = word[0];
	int start = -1;
	int end = -1;
	int index = -1;

	findSE(start, end, word_first);

	if (start != -1 && end != -1){
		index = searchBBC(start, end, word);
	}
	return index;
}

//Function to compute joint
void fulljoint(sentences& storage){
	int start = Gstart;
	int end = Gend;

	for (int i = start; i < end; i++){

		double calc_v, calc_e;
		calc_v = calc_e = 1;
		bool seen = false;
		for (int j = 0; j < storage.sentence[i].word.size(); j++){
			if (j == 0){// age kalame avale
				int index_i = index_finder(storage.sentence[i].word[j].text);
				if (index_i >= 0){
					calc_e *= entertainment_table[index_i][index_i];
					calc_v *= varzeshi_table[index_i][index_i];
					seen = true;
				}
			}
			else{ //age kalame dovom va be bad vashe ham i ro begir ham j ro bgir 
				int index_i = index_finder(storage.sentence[i].word[j].text);
				int index_j = index_finder(storage.sentence[i].word[j - 1].text);

				if (index_i >= 0){
					if (index_j >= 0){
						calc_e *= entertainment_table[index_i][index_j];
						calc_v *= varzeshi_table[index_i][index_j];
						seen = true;
					}
					else{
						continue;
					}
				}
				else
				{
					continue;
				}

			}
		}
		if (!seen){
			out.open("showFlile.txt", ios::app);
			show(i, 0, 0);
			out.close();
		}
		else{
			out.open("showFlile.txt", ios::app);
			show(i, calc_v, calc_e);
			out.close();
		}


	}
}


int main(){

	vector<string> preposition;
	sentences varzeshi;
	sentences entertainment;

	sentences varzeshi_learn;
	sentences entertainment_learn;

	varzeshi_table = new int*[9636];
	for (int i = 0; i < 9636; i++){
		varzeshi_table[i] = new int[9636];
	}

	entertainment_table = new int*[9636];
	for (int i = 0; i < 9636; i++){
		entertainment_table[i] = new int[9636];
	}


	// intialize whole table 
	for (int i = 0; i < 9636; i++){
		for (int j = 0; j < 9636; j++){
			varzeshi_table[i][j] = 0;
			entertainment_table[i][j] = 0;
		}
	}

	//reading preposition word form extra file
	readPreposition(preposition);

	dictionary = readDic();

	cout << endl << " Wait Please ... ";

	readFromFile(&varzeshi, "sport", preposition);
	readFromFile(&entertainment, "entertainment", preposition);

	//sLanda = varzeshi.sentence.size();
	//eLanda = entertainment.sentence.size();

	readFromFile_learn(&varzeshi_learn, "sport", preposition);
	readFromFile_learn(&entertainment_learn, "entertainment", preposition);

	//int counter_horof = 0;
	//for (int i = 0; i < 9636; i++){
	//	for (int j = 0; j < 9636; j++){
	//		if (i != j && varzeshi_table[i][j]){
	//			counter_horof++;
	//			cout << endl << varzeshi_table[i][j];
	//		}
	//		if (i != j && entertainment_table[i][j]){
	//			cout << endl << entertainment_table[i][j];
	//			counter_horof++;
	//		}
	//	}
	//}
	//cout << endl << endl << "counter : " << counter_horof;

	
	fulljoint(entertainment_learn);
	cout << endl << " OK! File is ready. " << endl;
	cout << " ";
	system("PAUSE");
	return 0;
}

