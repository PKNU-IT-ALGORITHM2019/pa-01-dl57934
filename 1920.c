#include <stdio.h>

#define NArray 1;
#define MArray 0;

int range = 0;
int nNums[100002];
int mNums[100002];

void mergesort(int start, int end);
void merge(int start, int mid, int end);
int binarySearch(int start, int end, int findValue);

void input(int isN);

int main(){
	input(1);
	mergesort(0, range-1);
	int end = range;
	input(0);

	for(int i = 0; i < range; i++){
		if(binarySearch(0, end-1, mNums[i])!= -1){
			printf("1\n");
		}
		else
			printf("0\n");
	}
}

void input(int isN){
	scanf("%d", &range);
	for(int i = 0; i < range; i++)
		scanf("%d", (isN? &nNums[i]:&mNums[i]));
}

void mergesort(int start, int end){
	if(start < end){
		int mid = (start+end)/2;
		mergesort(start, mid);
		mergesort(mid+1, end);
		merge(start, mid, end);
	}
}

void merge(int start, int mid, int end){
	int temp[100002];
	for(int i = start; i<=end; i++)
		temp[i] = nNums[i];

	int index = start;
	int part1 = start, part2 = mid+1;

	while(part1<=mid && part2<=end){
		if(temp[part1] < temp[part2]){
			nNums[index] = temp[part1];
			part1++;
		}else{ 
			nNums[index] = temp[part2];
			part2++;
		}
		index+=1;
	}

	for(int i = 0; i <= mid-part1; i++)
		nNums[i+index] = temp[part1+i];
}

int binarySearch(int start, int end, int findValue){
	int mid = (start+end)/2;
	if(start > end)
		return -1;
	if(nNums[mid] == findValue)
		return mid;
	else{
		if(nNums[mid] > findValue)
			return binarySearch(start, mid-1, findValue);
		else
			return binarySearch(mid+1, end, findValue);
	}
}