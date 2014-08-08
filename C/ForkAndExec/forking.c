#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main() {
	pid_t pid = fork();
	if (-1 == pid) {
		fprintf(stderr, "%s\n",strerror(errno));
		return -1;
	}
	if (! pid) {
		// we're in the child process
		while(1)
			printf("Child says yes!\n");
	}
	else {
		while(1)
			printf("Parent says no!\n");
	}

	return 0;
}