#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <pthread.h>

#include "p1_process.h"
#include "p1_threads.h"

int main(int argc, char** argv) {
	printf("Main process is created. (pid: %d)\n", getpid());
	int num_processes = 0;
	int num_threads = 0;

	std::string class_name[] = {"os", "architecture", "java", "algorithm", "digital-design"};

	// Check the argument and print error message if the argument is wrong
	if(argc == 3 && (atoi(argv[1]) > 0 && atoi(argv[2]) > 0)) { 
		num_processes = atoi(argv[1]);
		num_threads = atoi(argv[2]);
		// Call the process
		get_statistics(class_name, num_processes, num_threads);
	}
	else {
		printf("[ERROR] Expecting 2 arguments with integral value greater than zero.\n");
		printf("[USAGE] p1_exec <number of processes> <number of threads>\n");
	}
	printf("Main process is terminated. (pid: %d)\n", getpid());
	return 0;
}

/*
int main(int argc, char** argv) {
  if (argc != 2) {
    fprintf(stderr, "[ERROR] Expecting 1 argument, but got (%d) \n", argc - 1);
    fprintf(stderr, "[USAGE] p1_exec <number of processes>\n");
    return -1;
  }

  std::cout << "Beginning of the main()   (pid: " << getpid() << ")" << std::endl;
  std::string class_name[] = {"os", "architecture", "java", "algorithm", "digital-design"};
  int num_threads = sizeof(class_name) / sizeof(class_name[0]);
  int num_processes = (atoi(argv[1]) <= num_threads) ? atoi(argv[1]) : num_threads;

  get_statistics(class_name, num_processes, num_threads);
  std::cout << "End of the main()     (pid: " << getpid() << ")" << std::endl;
  return 0;
}
*/
