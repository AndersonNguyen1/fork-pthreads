#ifndef __P1_PROCESS
#define __P1_PROCESS

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <pthread.h>
#include <unistd.h>
#include <sstream>
#include <vector>
#include <sys/wait.h>
#include <algorithm>
#include <sys/types.h>
#include <iomanip>
#include "p1_threads.h"

void get_statistics(std::string class_name[], int num_processes, int num_threads);

struct Data read_file(std::string filename);
void write_file(std::string filename, struct Data data);

#endif
