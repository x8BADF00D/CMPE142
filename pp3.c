#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>	// for pipe
#include <sys/wait.h>	// for wait

int main(int argc, char* argv[])
{
	/*
		Even though the spec says 'create a pipe,' I have created 2 to facilitate
		bidirectional communication, since pipes are unidirectional.
	*/
	
	int pc[2], cp[2];		// pc = parent to child, cp = parent to child
	if (pipe(pc) == -1)
	{
		printf("parent to child pipe creation error.\n");
		return 1;
	}
	if (pipe(cp) == -1)
	{
		printf("child to parent pipe creation error.\n");
		return 2;
	}

	int pid = fork();
	if (pid == -1)
	{
		printf("fork error.\n");
	}
	if (pid == 0)		// child
	{
		close(pc[1]);
		char x[50];
		read(pc[0], &x, sizeof(x));
		close(pc[0]);
		printf("%s\n", x);
		
		sprintf(x, "Daddy my name is %d\n", getpid());
		
		write(cp[1], &x, sizeof(x));
		close(cp[1]);
		exit(0);
	}
	if (pid > 0)		// parent
	{
		char str[50];
		sprintf(str, "I am your daddy! and my name is %d\n", getpid());
		
		write(pc[1], &str, sizeof(str));
		close(pc[1]);

		read(cp[0], &str, sizeof(str));
		close(cp[0]);
		printf("%s\n", str);
		wait(NULL);
	}
	return 0;
}
