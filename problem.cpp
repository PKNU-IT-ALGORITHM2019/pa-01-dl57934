#include <cstdio>
#include <string>
#include <cstring>
#include <fstream>
#include <vector>
#include <algorithm>

#define READ 1
#define FIND 0
// #define MAX_LENGTH 176051

using namespace std;

int line=0;
char findWords[50];
string wordsDirecotry[180000];
string fullDirectory[180000];
vector<int> saveIndexVector;

void completeFoundResult();
void saveAtDirectory();
void completeFoundResult();
void notFoundResult(int mid);
void printWords(string words);
int input();
int wordsBinarySearch(int start, int end, string findWords);
string splitWords(string item);
string toLowerCase(string words);


int main(){
	saveAtDirectory();
	if(input() == READ)
		printf("%d", line);
	else {
		int mid = wordsBinarySearch(0,  line+1, toLowerCase(string(findWords)));
		 if(!saveIndexVector.empty())
			completeFoundResult();
		else
			notFoundResult(mid);
	}
}

int input(){
	char command[10];
	scanf("%s ", command);
	
	if(strcmp("find", command)==0){
		gets(findWords);
		return FIND;
	}

	printf("size\n");
	return READ;
}

void printWords(string words){
	printf("%s\n", words.c_str());
}

void completeFoundResult(){
	printf("Found %d items.\n", saveIndexVector.size());
	for(int i = 0; i < saveIndexVector.size(); i++)
		printWords(fullDirectory[saveIndexVector[i]]);
}

void notFoundResult(int mid){
	printf("Not found.\n");
	printWords(fullDirectory[mid]);
	printf("- - -\n");
	printWords(fullDirectory[mid+1]);
}

void saveAtDirectory(){
	string item;
	ifstream inFile("dict.txt");
	while(getline(inFile, item))
		if(item.compare("")!=0){
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
			words[i] -= 32;
	return string(words).c_str();
}

int wordsBinarySearch(int start, int end, string findWords){
	int mid = (start + end)/2;
	if(start > end){
		return mid;
	}
	if( wordsDirecotry[mid].compare(findWords) == 0 ){
		saveIndexVector.push_back(mid);
		return wordsBinarySearch(mid+1, end, findWords)+ wordsBinarySearch(start, mid-1, findWords) ;
		
	}
	else 
		if( wordsDirecotry[mid].compare(findWords) > 0)
			return wordsBinarySearch(start ,mid-1 ,findWords);
		else
			return wordsBinarySearch(mid+1 ,end ,findWords);

}












