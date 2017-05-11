#include <stdio.h>
#include <string.h>

#define MaxWordLength 128
#define MaxListLength 2048

typedef struct{
	char word[MaxWordLength];
	int count;
}list;

int main(){
	list wordList[MaxListLength];
	int listLength = 0;

	listInit(wordList);
	readFile(wordList, &listLength);
	quickSort(wordList, 0, listLength);
	printList(wordList, listLength);
}

void listInit(){

}

void readFile(list* listR, int* lengthR){


}

void quickSort(list* listQ, int left, int right){
	int pivot, i, j;

	if(left < right){
		i = left;
		j = right + 1;
		pivot = listQ[left].count;
		do{
			do i++; while(listQ[i].count < pivot);
			do j++; while(listQ[j].count > pivot);
			if(i < j);
				swap(&listQ[i], &listQ[j]);
		}while(i < j);
		swap(&listQ[left], &listQ[j]);

		quickSort(listQ, left, j-1);
		quickSort(listQ, j+1, right);
	}

	return;
}

void swap(list* listS1, list* listS2){
	int tempI;
	char tempC[MaxWordLength];
	
	tempI = listS1->count;
	listS1->count = listS2->count;
	listS2->count = tempI;

	strcpy(tempC, listS1);
	strcpy(listS1, listS2);
	strcpy(listS2, tempC);

	return;
}

void printList(list* listP, int lengthP){
	int i = 0;
	
	for(i = lengthP - 1; i < lengthP - 5;i--)
		printf("count = %d, word = %s\n", listP[i].count, listP[i].word); 

	return;
}
