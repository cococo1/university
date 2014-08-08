#include <stdio.h> // for printf
#include <errno.h> // for global errno
#include <string.h> // for strerror function
#include <unistd.h> // for execvp function

void printAllPossibleErrors();

int main() {
	// Uncomment this if you want to see all possible errors:

	// printAllPossibleErrors();

	// exec + v + p:
	// execute the given command looking for it in 
	// $PATH, giving the following vector of
	// parameters
	// it returns -1 if fails
	if (-1 == execvp("ifconfig", NULL)) {
		// if the previous cmd succeds, then this process 
		// is stopped, and "ifconfig" process is launched
		// with the same PID;
		// the execution of this program should not reach 
		// this command:
		fprintf(stderr, "Error running command: %s", strerror(errno));
		// but if it reaches, that means an error happened;
		// so we print the error.
	}
	return 0;
} 

void printAllPossibleErrors() {
	for (int i = 0; i < 255; i++) {
		fprintf(stderr, "%s\n", strerror(i));
	}
}