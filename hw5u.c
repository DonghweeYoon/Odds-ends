//In the class, professor said use the argv[]
//So when you run, use format : <program> <textfile.txt> <mapfile.txt>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//define max length of variables
#define MAX_WORD_LEN 128
#define MAX_LINE_LEN 2048

//Structure for the binary search tree
typedef struct node{
	char nodeKey[MAX_WORD_LEN];
	char nodeValue[MAX_WORD_LEN];
	struct node *leftChild;
	struct node *rightChild;
}bSTPoint;

//Function Declaration
void makeMap(bSTPoint **rootPM, char *mapFileName);
void handleInput(char* lineH);
void token_makeBST(char* lineT, bSTPoint **rootPMT);
void addNode(bSTPoint **rootPA, char *sourceA, char *targetA);
bSTPoint *createNode(char *keyC, char *valueC);
void reviseFile(bSTPoint **rootPR, char* sourceFileName);
void token_write(char* lineW, bSTPoint **rootPW, FILE *revisedFW);
char* searchKey(bSTPoint **rootPP, char* inputKey);

//main function
int main(int argc, char *argv[]){
	bSTPoint *rootP = NULL;

	makeMap(&rootP, argv[2]);
	reviseFile(&rootP, argv[1]); 
	
	return 0;
}

//open map file, change input text to binary search tree
void makeMap(bSTPoint **rootPM, char *mapFileName){
	char line[MAX_LINE_LEN];
	FILE *mapF = NULL;

	mapF = fopen(mapFileName, "r");
	if(!mapF){
		perror("file open fail");
		exit(-1);
	}

	//BST Making loop
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

//tokenize the line into key and value, and add new node into BST
void token_makeBST(char* lineT, bSTPoint **rootPMT){
	char* sourceW = NULL;
	char* targetW = NULL;

	//tokenize the string
	sourceW = strtok(lineT, ":");
	targetW = lineT + strlen(sourceW) + 2;
	
	//add node into BST
	addNode(rootPMT, sourceW, targetW);
}

//add new node into the binary search tree.
void addNode(bSTPoint **rootPA, char *sourceA, char *targetA){
	bSTPoint *newNode = NULL;
	bSTPoint *temp = *rootPA;
	
	//create new node with the input variables(key, value)
	newNode = createNode(sourceA, targetA);
	
	//If the tree is empty
	if(!temp){
		*rootPA = newNode;
	}
	//If the tree is not empty
	else{
		while(1){
			//chase left child
			if(strcmp(newNode->nodeKey, temp->nodeKey) < 0){
				if(temp->leftChild)
					temp = temp->leftChild;
				else{
					temp->leftChild = newNode;
					return;
				}
			}
			//chase right child
			else if(strcmp(newNode->nodeKey, temp->nodeKey) > 0){
				if(temp->rightChild)
					temp = temp->rightChild;
				else{
					temp->rightChild = newNode;
					return;
				}
			}
			//If the input key already exist in the tree, send an message 
			else{
				printf("Duplicate key words in the map file. Latter one is ignored\n");
				return;
			}
		}
	}
}

//Create new node with input variables(key, value)
bSTPoint *createNode(char *keyC, char *valueC){
	bSTPoint *newNodeC = NULL;	
	if(!(newNodeC = (bSTPoint*)malloc(sizeof(bSTPoint)))){
		perror("malloc Failure\n");
		return NULL; 
	}
	
	//initialize new node
	strcpy(newNodeC->nodeKey, keyC);
	strcpy(newNodeC->nodeValue, valueC);
	newNodeC->leftChild = NULL;
	newNodeC->rightChild = NULL;

	return newNodeC;
}

//open source text file
//revise it and make new file with BST 
void reviseFile(bSTPoint **rootPR, char* sourceFileName){
	FILE* sourceF = NULL;
	FILE* revisedF = NULL;
	char line[MAX_LINE_LEN];
	
	//open source file
	sourceF = fopen(sourceFileName, "r");
	if(!sourceF){
		perror("file open fail");
		exit(-1);
	}
	
	//open(or make&open) revised file 
	revisedF = fopen(strcat(sourceFileName, ".rev"), "w");
	if(!revisedF){
		perror("file open fail");
		exit(-1);
	}

	//Revising source text file and Writing new file loop
	while(fgets(line, MAX_LINE_LEN, sourceF)){
		handleInput(line);
		token_write(line, rootPR, revisedF);
	}

	fclose(sourceF);
	fclose(revisedF);
}

//token the input from source file
//Compare the input with BST
//The input word exists in BST keys, it is revised with BST node value
void token_write(char* lineW, bSTPoint **rootPW, FILE *revisedFW){
	char* token = NULL;
	char* written = NULL;

	token = strtok(lineW, " ");
	while(token){
		written = searchKey(rootPW, token);
		if(written){
			//If the tokenized word exists in BST, write revised word
			fputs(written, revisedFW);
			fputs(" ", revisedFW);
		}
		else{
			//If the tokenized word doesn't exist in Bst, write original word
			fputs(token, revisedFW);
			fputs(" ", revisedFW);
		}
		token = strtok(NULL, " ");
	}
	//At the end of the line, insert '\n' to change line
	fseek(revisedFW, -1, 2);
	fputs("\n", revisedFW);
}
	
//Check the input exists in BST
//If so, return nodeKey and if not, return null
char* searchKey(bSTPoint **rootPP, char* inputKey){
	bSTPoint *temp = *rootPP;
	while(1){
		//chase left child
		if(strcmp(inputKey, temp->nodeKey) < 0){
			if(temp->leftChild)
				temp = temp->leftChild;
			else
				return NULL;
		}
		//chase right child
		else if(strcmp(inputKey, temp->nodeKey) > 0){
			if(temp->rightChild)
				temp = temp->rightChild;
			else
				return NULL;
		}
		//If the input key exist in the tree, send an message 
		else
			return temp->nodeValue; 
	}
}
