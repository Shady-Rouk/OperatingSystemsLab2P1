#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>


void ChildProcess(void);
void ParentProcess(void);

int main() {
	srandom(time(NULL));
	pid_t pid;
	pid = fork();
	if (pid < 0) {
		printf("Error: Fork Operation was unsuccessful\n");
	} else if (pid == 0) {
		ChildProcess();
	} else {
		ParentProcess();
	}
		
	return 0;
}

void ChildProcess(void) {
	int i;
	int rand_num = random()%31;
	for (i=0; i<rand_num; i++) {
		printf("Child Pid: %d is going to sleep!\n", getpid());
		sleep(random()%11);
		printf("Child Pid: %d is awake!\nWhere is my Parent: %d?\n", getpid(), getppid());
	}
	exit(0);
}

void ParentProcess(void) {
	int status;
	pid_t pid;
	pid = fork();
	if (pid < 0) {
		printf("Error: Fork Operation was unsuccessful\n");
	} else if (pid == 0) {
		ChildProcess();
	} else {
		pid_t child_pid1 = wait(&status);
		printf("Child Pid: %d has completed\n", child_pid1);
		pid_t child_pid2 = wait(&status);
		printf("Child Pid: %d has completed\n", child_pid2);
	}
}