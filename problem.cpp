#include <cstdio>
#include <string>
#include <cstring>
#include <fstream>
#include <string.h>
#include <vector>
#include <algorithm>

#define READ 1
#define FIND 0
#define MAX_LENGTH 176051

using namespace std;

char findWords[50];
string wordsDirecotry[180000];
string fullDirectory[180000];
std::vector<int> saveIndexVector;

int line=0;

int input();
void saveAtDirectory();
string splitWords(string item);
int wordsBinarySearch(int start, int end, string findWords);

int main(){
	saveAtDirectory();
	if(input() == READ){
		printf("%d", line);
	}
	else {
		int index = wordsBinarySearch(0,  MAX_LENGTH, string(findWords));
		if(!saveIndexVector.empty()){
			for(int i = 0; i < saveIndexVector.size(); i++)
			printf("%s\n", fullDirectory[saveIndexVector[i]].c_str());
		}
		else{
			printf("Not found.\n- - -");
		}
	}
}

int input(){
	char command[10];
	scanf("%s", command);
	
	if(strcmp("find", command)==0){
		scanf("%s", findWords);
		return FIND;
	}
	printf("size\n");
	return READ;
}

void saveAtDirectory(){
	string item;
	ifstream inFile("dict.txt");
	while(getline(inFile, item)){
		if(item.compare("")!=0){
			wordsDirecotry[line] = splitWords(item);
			fullDirectory[line] = item;
			line++;
		}
	}
}

string splitWords(string item){
	char *cpyStr = new char[10000];
	strcpy(cpyStr, item.c_str());

	char *tok = strtok(cpyStr, " ");

	return string(tok).c_str();
}

int wordsBinarySearch(int start, int end, string findWords){
	int mid = (start + end)/2;
	if(start > end)
		return -1;
	if( wordsDirecotry[mid].compare(findWords) == 0 ){
		for(int i = mid+1; i < MAX_LENGTH-saveIndexVector.size(); i++)
			wordsDirecotry[i-1] = wordsDirecotry[i];
		printf("%d\n",mid+saveIndexVector.size());
		saveIndexVector.push_back(mid);
		return  wordsBinarySearch(0,  MAX_LENGTH-saveIndexVector.size(), string(findWords));
	}
	else {
		if( wordsDirecotry[mid].compare(findWords) > 0)
			return wordsBinarySearch(start ,mid-1 ,findWords);
		else
			return wordsBinarySearch(mid+1 ,end ,findWords);
	}

}










