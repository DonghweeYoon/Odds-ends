#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>

#include <unistd.h>

#include <pthread.h>
#include <semaphore.h>

#include "ExclusiveQueue.h"

#define TRUE 1
#define FALSE 0

#define NoConsumer 5				// # of consumer threads
int gThreadContinue = TRUE;

void exclusivePrint(const char *format, ...);

void* ProducerThreadFn(void *param);
void* ConsumerThreadFn(void *param);

int main()
{
	int t = 0;

	ExclusiveQueue queue;
	
	// TO DO: initialize random seed
	srand(time(NULL));

	// TO DO: initialize an ExclusiveQueue variable
	EQ_Init(&queue);

	pthread_t producer;
	pthread_t consumer[NoConsumer];

	// TO DO: launch producer and consumer threads
	pthread_create(&producer, NULL, ProducerThreadFn, &queue); 
	for(t = 0; t < NoConsumer; t++){
		pthread_create(&consumer[t], NULL, ConsumerThreadFn, &queue); 
	}

	// TO DO: terminate threads by setting gThreadContinue by FALSE
	while(gThreadContinue){
		sleep(10);
		gThreadContinue = FALSE;
	}
	
	// TO DO: Think and find out why the following code is necessary.
	int semValue = 0;	
	sem_getvalue(&queue.empty, &semValue);
	while(semValue < 1){
		printf("Releasing producer\n");
		EQ_Delete(&queue);
		sem_getvalue(&queue.empty, &semValue);
	}

	// TO DO: wait for threads to terminate
	pthread_join(producer, NULL);
	for(t = 0; t < NoConsumer; t++){
		pthread_join(consumer[t], NULL);
	}
	printf("Bye!\n");

	// TO DO: destroy the ExclusiveQueue
	EQ_Destroy(&queue);

	return 0;
}

void* ProducerThreadFn(void *param)
{
	ExclusiveQueue *pQueue = (ExclusiveQueue*) param;

	while(gThreadContinue){
		// TO DO: generate a random number between 1 and 100, and add it to the queue.
		EQ_Add(pQueue, rand()%100 + 1);
	}

	printf("Terminating producer.\n");

	return NULL;
}

void* ConsumerThreadFn(void *param)
{
	ExclusiveQueue *pQueue = (ExclusiveQueue*) param;
	int i = 0, sum = 0;

	while(gThreadContinue){
		// TO DO: complete this code
		
		// 	retrieve a number v from the queue.
		i = EQ_Delete(pQueue);

		// 	print the sum of numbers from 1 to v.
		while(i>0){
			sum += i;
			i--;
		}
		printf("sum = %d\n", sum);
		sum = 0;

		// 	sleep for 1 second.
		sleep(1);
	}

	printf("Terminating consumer.\n");

	return NULL;
}
