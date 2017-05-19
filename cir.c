#include <stdio.h>
#include <stdlib.h>

#define TAR 600851475143

typedef struct node{
	long prime;
	struct node *link;
}primeList;

int main(){
	primeList *head = NULL;
	primeList *pre = NULL;
	primeList *past = NULL;
	primeList *move = NULL;
	
	long num = TAR;
	long temp = 0;
	
	head = (primeList*)malloc(sizeof(primeList));
	if(!head){
		printf("perror");
		return -1;
	}

	pre = head;
	pre->prime = 2;
	pre->link = NULL;

	while(1){
		pre = head;
		while(pre){
			if((num % (pre->prime)) == 0){
				num /= (pre->prime);
			}
			else{
				past = pre;
				pre = pre->link;
			}
		}
		if(num == 1){
			break;
		}
		num = TAR;

		pre = (primeList*)malloc(sizeof(primeList));
		if(!pre){
			printf("perror");
			return -1;
		}
		past->link = pre;

		pre->prime = 0;
		pre->link = NULL;
		temp = (past->prime) + 1;
		move = head;
		while(pre->prime != temp - 1){
			while(temp % (move->prime)){
				if(temp / move->prime < move->prime){
					pre->prime = temp;
					break;
				}
				move = move->link;
			}
			temp++;
		}
	}

	printf("The largest : %ld\n", past->prime);
	
	pre = head;
	while(pre==NULL){
		past = pre;
		pre=pre->link;
		free(past);
	}

	return 0;
}
