#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>	// for threads
#include <signal.h>	// for SIGINT/signals
#include <unistd.h>	// for sleep

int run = 1;
int thread = 0;

pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond2 = PTHREAD_COND_INITIALIZER;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void sighandler(int sig)
{
	if (sig == SIGINT) run = 0;
}

void *func(void *val) 
{
	while(run)
	{
		pthread_mutex_lock(&lock);
		if(thread == 0)
		{
			// thread 1
			printf("thread 1: ping thread 2\n");
			thread = 1;
			pthread_cond_signal(&cond2);
			pthread_cond_wait(&cond1, &lock);
			printf("thread 1: pong! thread 2 ping received\n");
		}
		else
		{
		// thread 2
			printf("thread2: pong! thread 1 ping received\n");
			thread = 0;
			printf("thread 2: pinng thread 1\n");
			pthread_cond_signal(&cond1);
		}
		pthread_mutex_unlock(&lock);
		sleep(1);
	}
	return NULL;
}

int main(int argc, char **argv)
{
	signal(SIGINT, sighandler);
	pthread_t t1, t2;
	
	pthread_create(&t1, NULL, func, NULL);
	pthread_create(&t2, NULL, func, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	return 0;
}
