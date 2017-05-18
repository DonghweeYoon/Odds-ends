#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	long prime;
	struct node *link;
}primeList;

int main(){
	primeList *head = NULL;
	primeList *pre = NULL;
	primeList *past = NULL;
	primeList *move = NULL;
	
	long num = 600851475143;
	long temp = 0;
	head = (primeList*)malloc(sizeof(primeList));
	pre = head;
	pre->prime = 2;
	pre->link = NULL;

	while(1){
		pre = head;
		while(pre){
			printf("while first, %d, %ld\n", pre, pre->prime);
			if((num % (pre->prime)) == 0){
				printf("if");	
				num /= (pre->prime);
			}
			else{
				printf("else first,  %d, %ld\n", pre, pre->prime);
				past = pre;
				pre = pre->link;
				printf("else last,  %d, %ld\n", past, past->prime);
			}
		}
		printf("%ld", past->prime);
		if(num == 1)
			break;
		num = 600851475143;
		
		pre = (primeList*)malloc(sizeof(primeList));
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
	printf("The largest : %ld", past->prime);
	return 0;
}



















