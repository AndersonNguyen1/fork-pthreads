#ifndef __P1_THREADS
#define __P1_THREADS
#include "p1_datatypes.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include <pthread.h>
#include "p1_process.h"

bool sort(const Student& s1, const Student& s2);

void* get_median_case(void* input);
void* get_avg_case(void* input);
void* get_std_dev_case(void* input);


void median(float& median, std::vector<Student> students);
float average(struct Data* data);
float std_dev(struct Data* data);

#endif
