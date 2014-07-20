// Max Chetrusca, maxchetrusca@gmail.com
// 20/07/2014
// A short program showing how to parse command line options and arguments

#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
  char c;
  char* argument;
  // a and b are valid options
  // : means b requires an argument 
  while ((c = getopt(argc, argv, "ab:")) != EOF)
    switch (c) {
      case 'a' : 
        printf("You passed option 'a' to the program\n");
        break;
      case 'b' :
        argument = optarg; // this is the required argument by 'b' option
        printf("You passed option 'b' with argument %s\n", argument);
        break;
      default:
        fprintf(stderr, "Unknown option.\n");
        return 1;
    }
  // optind stores the number of strings read from cmd
  // after these, argv[0] will point to first cmd-line arg that follows 
  // the options:
  argc -= optind;
  argv += optind;
  return 0;
}

