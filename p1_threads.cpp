#include "p1_threads.h"
#include "p1_process.h"

bool sort(const Student& s1, const Student& s2) {
  return s1.grade > s2.grade;
}

void* get_median_case(void* input) {
  struct Data* data = (struct Data*) input;
  median(data->median, data->students);
}

void* get_avg_case(void* input) {
  struct Data* data = (struct Data*) input;
  data->avg = average(data);
}

void* get_std_dev_case(void* input) {
  struct Data* data = (struct Data*) input;
  data->std_dev = std_dev(data);
}

void median(float& median, std::vector<Student> students) {
  int size = students.size();
  if ((size % 2) == 0) {
    median = (students[size / 2 - 1].grade + students[size / 2].grade) / 2;
  }
  else {
    median = students[size / 2].grade;
  }
}

float average(struct Data* data) {
  if (data->students.size() == 0) {
    return 0;
  }
  else {
    float total = 0;
    std::vector<Student>::iterator i;
    for (i = data->students.begin(); i != data->students.end(); i++) {
      total += i->grade;
    }
    float avg = total / data->students.size();
    return avg;
  }
}

float std_dev(struct Data* data) {
  float avg = average(data);
  float temp = 0;
  int size = data->students.size();
  for (int i = 0; i < size; i++) {
    temp += pow((data->students[i].grade - avg), 2);
  }
  float std_dev = sqrt(temp / size);
  return std_dev;
}


