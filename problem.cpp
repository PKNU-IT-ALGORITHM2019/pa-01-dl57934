#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

#define FIND 0
#define READ 1
#define SIZE 2
#define EXIT 3
#define SAME 0
#define DIFFERENCE_AT_LOW_AND_CAPITAL 32
#define DONT_EXIST_FRONT_WORDS 0

int line=0;
string findWord;
string wordsDirecotry[180000];
string fullDirectory[180000];
vector<int> saveIndexVector;

void completeFoundResult();
void saveAtDirectory();
void completeFoundResult();
void notFoundResult(int findIndex);
void printWords(string words);
int input();
int isSameCommand(const char* command , char request[]);
int wordsBinarySearch(int start, int end, string findWords);
string splitWords(string item);
string toLowerCase(string words);


int main(){

	while(1){
		int inputReturn = input();

		switch(inputReturn){
			case SIZE:
				printf("%d\n", line);
				break;
			case FIND:{
				int nearIndex = wordsBinarySearch(0,  line+1, toLowerCase(findWord));
				if(saveIndexVector.empty())
					notFoundResult(nearIndex);	
				else
					completeFoundResult();
				break;
			}
			case EXIT:
				exit(1);
				break;
			
		}	
	}
}

int input(){
	char request[10];
	cin >> request;
	if(isSameCommand("read", request)){
		saveAtDirectory();	
		return READ;
	}
	else if(isSameCommand("find", request)){
		getline(cin, findWord);
		findWord = findWord.substr(1, findWord.size());
		return FIND;
	}else if(isSameCommand("size", request))
		return SIZE;
	
	else if(isSameCommand("exit", request))
		return EXIT;
}

int isSameCommand(const char* command , char request[]){
	return strcmp(command, request) == SAME;
}

void printWords(string words){
	printf("%s\n", words.c_str());
}

void completeFoundResult(){
	printf("Found %lu items.\n", saveIndexVector.size());
	for(int i = 0; i < saveIndexVector.size(); i++)
		printWords(fullDirectory[saveIndexVector[i]]);
	saveIndexVector.clear();
}

void notFoundResult(int nearIndex){
	if(nearIndex == DONT_EXIST_FRONT_WORDS)
		printf("-1");
	else{
		printf("Not found.\n");
		printWords(fullDirectory[nearIndex]);
		printf("- - -\n");
		printWords(fullDirectory[nearIndex+1]);
	}
}

void saveAtDirectory(){
	string item;
	ifstream inFile("dict.txt");
	while(getline(inFile, item))
		if(item.compare("")!=SAME){
			wordsDirecotry[line] = splitWords(item);
			fullDirectory[line] = item;
			line++;
		}
}

string splitWords(string item){
	char *cpyStr = new char[10000];
	strcpy(cpyStr, item.c_str());
	string words = strtok(cpyStr, "(");
	words = words.substr(0, words.length()-1);
	return toLowerCase(words);
}	

string toLowerCase(string words){
	int wordsLen = words.size();	
	for(int i = 0; i < wordsLen; i++)
		if(words[i] >= 'a')
			words[i] -= DIFFERENCE_AT_LOW_AND_CAPITAL;
	return string(words).c_str();
}

int wordsBinarySearch(int start, int end, string findWords){
	int mid = (start + end)/2;
	if(start > end)
		return mid;
	if( wordsDirecotry[mid].compare(findWords) == SAME ){
		saveIndexVector.push_back(mid);
		return mid+ wordsBinarySearch(start ,mid-1 ,findWords) + wordsBinarySearch(mid+1, end, findWords);
	}
	else 
		if( wordsDirecotry[mid].compare(findWords) > 0)
			return wordsBinarySearch(start ,mid-1 ,findWords);
		
		else
			return wordsBinarySearch(mid+1 ,end ,findWords);

}












