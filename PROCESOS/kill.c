#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
int main()
{
 pid_t pid;
 if (( pid = fork()) == 0) {
 while(1) {
 printf("HIJO PID = %d\n", pid);
 sleep(1);
 }
 }
 sleep(10);
 printf("PADRE Terminacion proceso %d\n", pid);
 kill (pid,SIGTERM);
 exit(0);
}