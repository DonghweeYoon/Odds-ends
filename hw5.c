#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//define max length of value 1024
#define MAX_WORD_LEN 128
#define MAX_LINE_LEN 2048

//Structure for the binary search tree
typedef struct node{
	char nodeKey[MAX_WORD_LEN];
	char nodeValue[MAX_WORD_LEN];
	struct node *leftChild;
	struct node *rightChild;
}bSTPoint;

void makeMap(bSTPoint *rootPM, char *mapFileName);
void handleInput(char* lineH);
void token_makeBST(char* lineT, bSTPoint *rootPMT);
void addNode(bSTPoint **rootPA, char *sourceA, char *targetA);
bSTPoint *createNode(char *keyC, char *valueC);
void reviseFile(bSTPoint *rootPR, char* sourceFileName);
void token_write(char* lineW, bSTPoint *rootPMW, FILE *revisedFW);
char* searchKey(bSTPoint *rootPP, char* inputKey);

int main(int argc, char *argv[]){
	bSTPoint *rootP = NULL;

	makeMap(rootP, argv[2]);
	reviseFile(rootP, argv[1]); 
	
	return 0;
}

void makeMap(bSTPoint *rootPM, char *mapFileName){
	char line[MAX_LINE_LEN];
	FILE *mapF = NULL;

	mapF = fopen(mapFileName, "r");
	if(!mapF){
		perror("file open fail");
		exit(-1);
	}

	while(fgets(line, MAX_LINE_LEN, mapF)){
		handleInput(line);
		token_makeBST(line, rootPM);
	}

	fclose(mapF);
}

//String Handler for fgets (erase line feed & carriage return)
void handleInput(char* lineH){
	while((lineH[strlen(lineH)-1] == '\n') || (int)(lineH[strlen(lineH)-1] == '\r'))
		lineH[strlen(lineH)-1] = '\0';
}

void token_makeBST(char* lineT, bSTPoint *rootPMT){
	char* sourceW = NULL;
	char* targetW = NULL;

	sourceW = strtok(lineT, ":");
	targetW = strtok(NULL, "\0");
	printf("source : '%s', target : '%s'\n", sourceW, targetW);
	addNode(&rootPMT, sourceW, targetW);
	printf("source : '%s', target : '%s'\n", rootPMT->nodeKey, rootPMT->nodeValue);
}

//add new node into the binary search tree.
void addNode(bSTPoint **rootPA, char *sourceA, char *targetA){
	bSTPoint *newNode = NULL;
	bSTPoint *temp = *rootPA;
	
	//create new node with the input variables
	newNode = createNode(sourceA, targetA);
	
	//If the tree is empty
	if(!temp){
		rootPA = &newNode;
		printf("first source : '%s', target : '%s'\n", (*rootPA)->nodeKey, (*rootPA)->nodeValue);
	}

	//If the tree is not empty
	else{
		while(1){
			if(strcmp(newNode->nodeKey, temp->nodeKey) < 0){
				if(temp->leftChild)
					temp = temp->leftChild;
				else{
					temp->leftChild = newNode;
					printf("left source : '%s', target : '%s'\n", temp->leftChild->nodeKey, temp->leftChild->nodeValue);
					return;
				}
			}
			else if(strcmp(newNode->nodeKey, temp->nodeKey) > 0){
				if(temp->rightChild)
					temp = temp->rightChild;
				else{
					temp->rightChild = newNode;
					printf("right source : '%s', target : '%s'\n", temp->rightChild->nodeKey, temp->rightChild->nodeValue);
					return;
				}
			}
			//If the input key exist in the tree, send an message 
			else{
				printf("Duplicate key words in the map file. Latter one is ignored\n");
				return;
			}
		}
	}
}

//Create new node with input variables
bSTPoint *createNode(char *keyC, char *valueC){
	bSTPoint *newNodeC = NULL;	
	if(!(newNodeC = (bSTPoint*)malloc(sizeof(bSTPoint)))){
		perror("malloc Failure\n");
		return NULL; 
	}
	
	strcpy(newNodeC->nodeKey, keyC);
	strcpy(newNodeC->nodeValue, valueC);
	newNodeC->leftChild = NULL;
	newNodeC->rightChild = NULL;

	return newNodeC;
}

void reviseFile(bSTPoint *rootPR, char* sourceFileName){
	FILE* sourceF = NULL;
	FILE* revisedF = NULL;
	char line[MAX_LINE_LEN];
	
	sourceF = fopen(sourceFileName, "r");
	if(!sourceF){
		perror("file open fail");
		exit(-1);
	}

	revisedF = fopen(strcat(sourceFileName, ".rev"), "w");
	if(!revisedF){
		perror("file open fail");
		exit(-1);
	}
	
	while(fgets(line, MAX_LINE_LEN, sourceF)){
		handleInput(line);
		token_write(line, rootPR, revisedF);
	}

	fclose(sourceF);
	fclose(revisedF);
}

void token_write(char* lineW, bSTPoint *rootPMW, FILE *revisedFW){
	char* token = NULL;
	char* written = NULL;

	token = strtok(lineW, " ");
	while(token){
		written = searchKey(rootPMW, token);
		if(written){
		//	fputs(written, revisedFW);
		//	fputs(" ", revisedFW);
		}
		else{
		//	fputs(token, revisedFW);
		//	fputs(" ", revisedFW);
		}
		token = strtok(NULL, " ");
	}
}
	
//print the key and value of the binary search tree(inorder)
char* searchKey(bSTPoint *rootPP, char* inputKey){
	bSTPoint *temp = rootPP;
	
	if(strcmp(temp->nodeKey, inputKey) < 0){
		if(temp->leftChild)
			temp = temp->leftChild;
	}
	else if(strcmp(temp->nodeKey, inputKey) > 0){
		if(temp->rightChild)
			temp = temp->rightChild;
	}
	//If the input key exist in the tree, send an message 
	else
		return temp->nodeValue;
}

/*
//Search the input value in the tree(inorder)
void searchKey(bSTPoint *rootPSV, char *valueSV, int *searchSV){
	if(rootPSV){
		searchValue(rootPSV->leftChild, valueSV, searchSV);
		if(strcmp(rootPSV->nodeValue, valueSV) == 0){
			*searchSV = 1;
		}
		searchValue(rootPSV->rightChild, valueSV, searchSV);
	}
} */
