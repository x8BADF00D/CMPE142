#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <string.h>

void handler (int signal) 
{
	// do nothing
}

int main (int argc, char *argv[])
{
	int pid, status;
	signal(SIGCONT, handler);

	if (argc == 3 && strcmp(argv[1], "-n") == 0 && argv[2] > 0)
	{
		int n = atoi(argv[2]);
		for (int i = 0; i < n; i++)
		{
			pid = fork();
			if (pid == 0)	// Child section
			{
				exit(0);
			}
		}
		pause();
		for (int i = 0; i < n; i++)
		{
			wait(&status);
		}
	}
	else if (argc == 3 && strcmp(argv[1], "-n") == 0 && argv[2] == 0)
	{
		// do nothing, since 0 zombies were asked for
	}
	else if (argc == 1)
	{
		printf("You did not enter a number. Please use the format ./zombifier -n <number of zombies>");
	}
	else
	{
		printf("Entry error. Please use the format ./zombifier -n <number of zombies>\n");
	}

	return 0;
}
