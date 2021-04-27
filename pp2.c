#include <stdio.h>
#include <stdlib.h>	// for exit()
#include <unistd.h>	// for sleep()
#include <signal.h>	// for signal()

int debug = 0;
int loop = 0;
int run = 1;

void handler(int signal)
{
	if (debug == 0 && signal == SIGINT) debug = 1;
	else if (debug == 1 && signal == SIGINT) debug = 0;
	else if (signal == SIGUSR1) run = 0;
}

int main()
{
	signal(SIGINT, handler);
	signal(SIGUSR1, handler);
	while (run)
	{
		sleep(2);
		
		if (debug)
		{
			printf("loops: %d\n", loop);
		}
		loop ++;
	}
	exit(0);
	return 0;
}
