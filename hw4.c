#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//define length max
#define MAX_WORD_LEN 128
#define MAX_LIST_LEN 2048
#define MAX_LINE_LEN 4096

//declare structure
typedef struct{
	char word[MAX_WORD_LEN];
	int count;
}list;

//declare functions
void readFile(list* listR, int* lengthR);
void handleInput(char* lineH);
void tokenLine(list* listT, int* lengthT, char* lineT);
void quickSort(list* listQ, int left, int right);
void swap(list* listS1, list* listS2);
void printList(list* listP, int lengthP);

int main(){
	int listLength = 0;
	list wordList[MAX_LIST_LEN];

	readFile(wordList, &listLength);
	quickSort(wordList, 0, listLength - 1);
	printList(wordList, listLength);

	return 0;
}

//function to read a file and tokenize the input string
void readFile(list* listR, int* lengthR){
	FILE *fp;
	char file_name[128];
	char line[MAX_LINE_LEN];
	int i = 0;

	printf("input file name\n");
	scanf("%s", file_name);

	//file open
	fp = fopen(file_name, "r");
	if(fp == NULL){
		perror("fopen failed");
		return;
	}
	
	//loop for tokenizing
	while(fgets(line, MAX_LINE_LEN, fp)){
		handleInput(line);
		tokenLine(listR, lengthR, line);
	}

	fclose(fp);
	return;
}

//String Handler for fgets (erase line feed & carriage return)
void handleInput(char* lineH){
	while((lineH[strlen(lineH)-1] == '\n') || (int)(lineH[strlen(lineH)-1] == '\r'))
		lineH[strlen(lineH)-1] = '\0';
	return;
}

//tokenize the input line
void tokenLine(list* listT, int* lengthT, char* lineT){
	int i;
	char* token;
	
	token = strtok(lineT, " "); 
	while(token != NULL){
		//If the token exists in the list, count the number of the word
		for(i = 0; i < *lengthT ; i++){
			if(!strcmp(listT[i].word, token)){
				listT[i].count++;
				break;
			}
		}
		//If the token doesn't exists in the list and the list is not full and ther word length is under the maximum
		//input new word in the list
		if((i == *lengthT) && (i < MAX_LIST_LEN) && (strlen(token) < MAX_WORD_LEN)){
			strcpy(listT[i].word, token);
			listT[i].count = 1;
			(*lengthT)++;
		}
		token = strtok(NULL, " ");
	}
	return;
}

//quick sort algorithm
void quickSort(list* listQ, int left, int right){
	int pivot, i, j;

	if(left < right){
		i = left;
		j = right + 1;
		pivot = listQ[left].count;
		do{
			do	i++; while(listQ[i].count < pivot);
			do	j--; while(listQ[j].count > pivot);
			if(i < j)
				swap(&listQ[i], &listQ[j]);
		}while(i < j);
		swap(&listQ[left], &listQ[j]);

		quickSort(listQ, left, j-1);
		quickSort(listQ, j+1, right);
	}
	return;
}

//swap function
void swap(list* listS1, list* listS2){
	int tempI;
	char tempC[MAX_WORD_LEN];

	tempI = listS1->count;
	listS1->count = listS2->count;
	listS2->count = tempI;
	strcpy(tempC, listS1->word);
	strcpy(listS1->word, listS2->word);
	strcpy(listS2->word, tempC);
	return;
}

//print five most frequently appeared words
void printList(list* listP, int lengthP){
	int i = 0;

	for(i = lengthP - 1; i > lengthP - 6; i--)
		printf("Word = %s, Count = %d\n", listP[i].word, listP[i].count) ; 

	return;
}
