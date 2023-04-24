#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>

int daemonize(void)
{
        pid_t pid;
        int fds[3],i;

        fds[0] = open("/dev/null", O_RDONLY);
        fds[1] = open("/dev/null", O_WRONLY);
        fds[2] = open("/dev/null", O_WRONLY);
        if(fds[0] == -1 || fds[1] == -1 || fds[2] == -1) {
                fputs("Can't open /dev/null\n", stderr);
                for( i = 0; i <= 2; i++)
                        if(fds[i] != -1)
                                close(fds[i]);
                return -1;
        }
        for(i = 0; i <= 2; i++) {
                if(dup2(fds[i], i) == -1) {
                        return -1;
                }
        }
        for(i = 0; i <= 2; i++)
                if(fds[i] > 2)
                        close(fds[i]);

        pid = fork();
        if(pid == -1)
                return -1;
        if(pid)
                exit(0);
        setsid();
        return 0;
}

int main()
{
      if(daemonize() < 0)
        {
                printf("process not daemonize");
                return 0;
        }

      	while(1){}

}
