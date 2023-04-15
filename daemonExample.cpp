#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>

int main(int argc, char* argv[])
{
	pid_t pid = 0;
	pid_t sid = 0;
	FILE *fp= NULL;
	FILE *lfp=NULL;
	time_t t;
	time(&t);
	int i = 0,n;
	pid = fork();// fork a new child process

	if (pid < 0)
	{
		printf("fork failed!\n");
		exit(1);
	}

/*	printf("\n Enter value of n : \n");
	scanf("\n %d ",&n);
	printf("\n value of %d * %d = %d",n ,n ,n*n);

*/
	if (pid > 0)// its the parent process
	{
		printf("pid of child process %d \n", pid);
		exit(0); //terminate the parent process succesfully
	}

	umask(0);//unmasking the file mode

	sid = setsid();//set new session
	if(sid < 0)
	{
		exit(1);
	}


	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);

	
	
	fp = fopen ("Example.txt", "w+");
	while (i < 10)
	{
		sleep(5);
		fprintf(fp, "file id %d : %d\n", i, getpid());
		i++;
	}
	fprintf(fp,"\n");
	fclose(fp);



	// Open a log file in write mode.
	lfp = fopen ("Log.txt", "w+");
//	while (1)
	{
		//Dont block context switches, let the process sleep for some time
		sleep(10);
		fprintf(lfp, "Logging info..%d.\n On time %s ", i,ctime(&t));
		fflush(lfp);
		// Implement and call some function that does core work for this daemon.
	}
	fclose(lfp);
	return (0);
}

