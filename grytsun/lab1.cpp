#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <map>
using namespace std;

char* delimiters = " )(.\t\n,";

int main(int argc, char* argv[]){
	
	set<char> delim_set;
	for(int i=0;delimiters[i]!='\0';i++) delim_set.insert(delimiters[i]);
	map<string,int> count;
	
	if(argc < 2){
		cout << "enter name of file" << endl;
		return 0;
	}
	
	string cur_word;
	char cur_char;
	char* file_name = argv[1];
	ifstream file(file_name);
	if(file.is_open()){
		while(file >> noskipws >> cur_char){
			//file >> cur_char;
			cout << cur_char;
			if(delim_set.find(cur_char) == delim_set.end())
				cur_word.push_back(cur_char);
			else{
				if(cur_word.length()>0){
					if(count.find(cur_word) != count.end()) count[cur_word]++;
					else count[cur_word] = 1;
					string new_word;					
					cur_word = new_word;
				}
			}
		}

		if(cur_word.length()>0){
			if(count.find(cur_word) != count.end()) count[cur_word]++;
			else count[cur_word] = 1;
			string new_word;
			cur_word = new_word;
		}
		for(map<string,int>::iterator it = count.begin();it != count.end(); ++it)
			cout << it->first << " => " << it->second << endl;
	}
	else cout << "unable to open a file" << endl;
	
	return 0;
}
