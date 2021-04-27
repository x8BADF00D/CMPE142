#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>


void sigHandler (int s){
}

int main() {

	int status = 0;
	
	signal(SIGINT, sigHandler);
	
	int pid = fork();
	
	if (pid == 0) //if pid == 0, it is child
	{
		printf("child PID = %d\n", getpid());
		pause();
		exit(5);
	}
	
	else
	{
		waitpid(pid, &status, 0);
		printf("\nchild PID = %d, exitstatus = %d\n", pid, WEXITSTATUS(status));
	}
	
	return 0;
}

