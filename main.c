#include <stddef.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
pthread_mutex_t mutex_magazine0 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_magazine1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_magazine2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_magazine3 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_magazine4 = PTHREAD_MUTEX_INITIALIZER;
void *delivery(void* magazine)
{
	printf("Start delivery\n");
	int* tmp = (int*) magazine;
	while(1)
		for (int i = 0; i < 5; i++)
			switch (i)
			{
				case 0:
					if (pthread_mutex_trylock(&mutex_magazine0))
					{
						tmp[i] += 150;
						pthread_mutex_unlock(&mutex_magazine0);
						sleep(2);
					}
					break;
				case 1:
					if (pthread_mutex_trylock(&mutex_magazine1))
					{
						tmp[i] += 150;
						pthread_mutex_unlock(&mutex_magazine1);
						sleep(2);
					}
					break;
				case 2:
					if (pthread_mutex_trylock(&mutex_magazine2))
					{
						tmp[i] += 150;
						pthread_mutex_unlock(&mutex_magazine2);
						sleep(2);
					}
					break;
				case 3:
					if (pthread_mutex_trylock(&mutex_magazine3))
					{
						tmp[i] += 150;
						pthread_mutex_unlock(&mutex_magazine3);
						sleep(2);
					}
					break;
				case 4:
					if (pthread_mutex_trylock(&mutex_magazine4))
					{
						tmp[i] += 150;
						pthread_mutex_unlock(&mutex_magazine4);
						sleep(2);
					}
					break;
			}
}

void *consumer(void* magazine)
{
	printf("Start consumer\n");
	int consume_value = 5000;
	int* tmp = (int*) magazine;
	while(consume_value > 0)
		for (int i = 0; i < 5; i++)
		{ 
			switch (i)
			{
				case 0:
					if (pthread_mutex_trylock(&mutex_magazine0))
					{
						if (consume_value > tmp[i] )
						consume_value -= tmp[i] ;
					else
					{
						tmp[i]  -= consume_value;
						consume_value = 0;
					}
						pthread_mutex_unlock(&mutex_magazine0);
						sleep(1);
					}
					break;
				case 1:
					if (pthread_mutex_trylock(&mutex_magazine1))
					{
						if (consume_value > tmp[i] )
						consume_value -= tmp[i] ;
					else
					{
						tmp[i]  -= consume_value;
						consume_value = 0;
					}
						pthread_mutex_unlock(&mutex_magazine1);
						sleep(1);
					}
					break;
				case 2:
					if (pthread_mutex_trylock(&mutex_magazine2))
					{
						if (consume_value > tmp[i] )
						consume_value -= tmp[i] ;
					else
					{
						tmp[i]  -= consume_value;
						consume_value = 0;
					}
						pthread_mutex_unlock(&mutex_magazine2);
						sleep(1);
					}
					break;
				case 3:
					if (pthread_mutex_trylock(&mutex_magazine3))
					{
						if (consume_value > tmp[i] )
						consume_value -= tmp[i] ;
					else
					{
						tmp[i] -= consume_value;
						consume_value = 0;
					}
						pthread_mutex_unlock(&mutex_magazine3);
						sleep(1);
					}
					break;
				case 4:
					if (pthread_mutex_trylock(&mutex_magazine4))
					{
						if (consume_value > tmp[i] )
						consume_value -= tmp[i] ;
					else
					{
						tmp[i] -= consume_value;
						consume_value = 0;
					}
						pthread_mutex_unlock(&mutex_magazine4);
						sleep(1);
					}
					break;
				}
				printf("Magazine %d: %d\n",i+1 ,tmp[i]);
			}
	pthread_exit(NULL);
}

void main ()
{
	void *status;
	int magazine[5] = {1000};
	pthread_t thread_array[4];
	
	pthread_create(&thread_array[0], NULL, delivery, (void *) magazine);
	for (int i = 1; i < 4; i++)
	{
		pthread_create(&thread_array[i], NULL, consumer, (void *) magazine);
	}
	for (int i = 1; i < 4; i++)
	{
		if (i == 1)
			printf("Wait for consumer 1\n");
		if (i == 2)
			printf("Wait for consumer 2\n");
		if (i == 3)
			printf("Wait for consumer 3\n");
		pthread_join(thread_array[i], &status);
	}
	pthread_cancel(thread_array[0]);

}