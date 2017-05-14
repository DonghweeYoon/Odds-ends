#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LEN 128
#define MAX_LIST_LEN 2048
#define MAX_FILE_LEN 65536
#define MAX_LINE_LEN 2048

typedef struct{
	char* word;
	int count;
}list;

void readFile(list* listR, int* lengthR);
void tokenLine(list* listT, int* lengthT, char* lineT);
void quickSort(list* listQ, int left, int right);
void swap(list* listS1, list* listS2);
void printList(list* listP, int lengthP);

int main(){
	int listLength = 0;
	list wordList[MAX_LIST_LEN];
	memset(wordList, 0, sizeof(wordList));

	readFile(wordList, &listLength);
	quickSort(wordList, 0, listLength - 1);
	printList(wordList, listLength);

	return 0;
}

void readFile(list* listR, int* lengthR){
	FILE *fp;
	char file_name[128];
	char line[MAX_FILE_LEN];
	int i = 0;

	printf("input file name?\n");
	scanf("%s", file_name);

	fp = fopen(file_name, "r");

	while(fgets(line, MAX_LINE_LEN, fp)){
		tokenLine(listR, lengthR, line);
	}

	fclose(fp);
	return;
}

void tokenLine(list* listT, int* lengthT, char* lineT){
	int i;
	char* token;

	lineT[strlen(lineT)-1] = '\0';
	lineT[strlen(lineT)-1] = '\0';
	token = strtok(lineT, " ");

	while((token != NULL) && (strlen(token) < MAX_WORD_LEN - 1)){
		for(i = 0; i < *lengthT; i++){
			if(strcmp(listT[i].word, token)== 0){
				listT[i].count++;
				i = *lengthT;
			}
		}
		
		if((i == (*lengthT)) && (i < MAX_LIST_LEN)){
			listT[i].word = (char*)malloc(MAX_WORD_LEN * sizeof(char));

			strcpy(listT[i].word, token);
			listT[i].count++;
			(*lengthT)++;
		}
		token = strtok(NULL, " ");
	}
	
	return;
}

void quickSort(list* listQ, int left, int right){
	int pivot, i, j, k;
	
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

void printList(list* listP, int lengthP){
	int i = 0;
	
	for(i = lengthP - 1; i > lengthP - 6; i--)
		printf("count = %d, word = %s\n", listP[i].count, listP[i].word); 

	return;
}
