#include <cstdio>
#include <string.h>
#include <string>
#include <fstream>
#define READ 1
#define FIND 0

using namespace std;

char findWords[50];
string direcotry[180000];

int input();
int getDictLength();


int main(){
	if(input() == READ){
		printf("%d", getDictLength());
	}
	else {

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

int getDictLength(){
	int line=0;
	string item;

	ifstream inFile("dict.txt");
	while(getline(inFile, item)){
		if(item.compare("")!=0)
			direcotry[line++] = item;
	}
	return line;
}