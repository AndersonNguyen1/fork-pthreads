#ifndef P1_DATATYPE_H
#define P1_DATATYPE_H
#include <stdio.h>
#include <iostream>
#include <vector>

struct Student {
  std::string id;
  float grade;
};

struct Data {
  std::string code;
  float median;
  float avg;
  float std_dev;
  std::vector<Student> students;
};

#endif
