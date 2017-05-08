#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#include "ExclusiveQueue.h"

void EQ_Init(ExclusiveQueue *pQueue)
{
	// initialize head and tail
	pQueue->head = 0;
	pQueue->tail = 0;

	// initialize mutex
	pthread_mutex_init(&pQueue->mutex, NULL);

	// initialize empty by 100 and full by 100
	sem_init(&pQueue->empty, 0, 100);
	sem_init(&pQueue->full, 0, 100);
}

void EQ_Destroy(ExclusiveQueue *pQueue)
{
	// destroy mutex, empty and full
	pthread_mutex_destroy(&pQueue->mutex);
	sem_destroy(&pQueue->empty);
	sem_destroy(&pQueue->full);
}

void EQ_Add(ExclusiveQueue *pQueue, int v)
// This function is called by producer
{
	// implement the entry section of producer  (wait for empty and mutex)
	sem_wait(&pQueue->empty);
	pthread_mutex_lock(&pQueue->mutex);

	// insert v into the queue (critical section)
	// checking full condition is not necessary
	pQueue->array[pQueue->tail] = v;
	pQueue->tail = (pQueue->tail + 1) & QueueSize;

	// implement the exit section of producer (signal mutex and full)
	pthread_mutex_unlock(&pQueue->mutex);
	sem_post(&pQueue->full);
}

int EQ_Delete(ExclusiveQueue *pQueue)
// This function is called by consumer
{
	int v = 0;
	
	// implement the entry section of consumer  (wait for full and mutex)
	sem_wait(&pQueue->full);
	pthread_mutex_lock(&pQueue->mutex);

	// retrieve an item into v and delete it from the queue (critical section)
	// checking empty condition is not necessary
	v = pQueue->array[pQueue->head]; 
	pQueue->head = (pQueue->head + 1) & QueueSize;

	// implement the exit section of consumer (signal mutex and empty)
	pthread_mutex_unlock(&pQueue->mutex);
	sem_post(&pQueue->empty);

	return v;
}

