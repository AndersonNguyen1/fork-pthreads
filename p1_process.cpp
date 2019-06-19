#include "p1_process.h"
#include "p1_threads.h"
#include "p1_datatypes.h"

void get_statistics(std::string class_name[], int num_processes, int num_threads) {

  int size_of_base = num_threads / num_processes;
  int remainder = num_threads % num_processes;
  int size = 0;
  int count = 0;
  int status = 0;
  pid_t pid, wpid;
  std::vector<std::string> filename;
  for (int i = 0; i < num_processes; i++) {
   /* 
    if (remainder > 0) {
      size = size_of_base + 1;
    }
    else {
      size = size_of_base;
    }

    if(remainder > 0) {
      remainder -= 1; 
    }
    else {
      remainder -= 0;
    }
    */
    
    size = (remainder > 0) ? (size_of_base + 1) : size_of_base;
    remainder -= (remainder > 0) ? 1 : 0;

    for (int j = 0; j < size; j++) {
      filename.push_back(class_name[count++]);
    }
    
    pid = fork();
    if (pid == 0) {
      break;
    }
    filename.clear();
  }

  if (pid == 0) {
    printf("Child process is created. (pid: %d)\n", getpid());
    for (int i = 0; i < filename.size(); i++) {
      std::string in_file_name = "./input/" + filename[i] + ".csv";
      struct Data data = read_file(in_file_name);
      pthread_t threads[3];

      pthread_create(&threads[0], NULL, get_avg_case, &data);
      pthread_create(&threads[1], NULL, get_median_case, &data);
      pthread_create(&threads[2], NULL, get_std_dev_case, &data);

      for (int j = 0; j < 3; j++) {
        if(pthread_join(threads[j], NULL)) {
          fprintf(stderr, "Error combining threads together\n");  
        }
      }

      std::string out_file_name = "./output/" + filename[i] + "-stats.csv";
      write_file(out_file_name, data);
    }
    printf("Child process is terminated. (pid: %d)\n", getpid()); 
    exit(0);
  }

  while ((wpid = wait(&status)) > 0);
  printf("Parent process is terminated. (pid: %d)\n", getpid());
}

struct Data read_file(std::string filename) {
  std::ifstream ifs;
  ifs.open(filename.c_str());
  if(!ifs.is_open()) {
    fprintf(stderr, "[ERROR] Can't open file.\n");
    exit(-1);
  }
  struct Data data;
  std::string line;
  std::getline(ifs, line);
  data.code = line;

  while (std::getline(ifs, line)) {
    std::string a;
    float b;
    std::istringstream iss(line);
    if (iss >> a >> b) {
      struct Student student;
      student.id = a;
      student.grade = b;
      data.students.push_back(student);
    }
  }
  std::sort(data.students.begin(), data.students.end(), sort);
  ifs.close();
  return data;
}

void write_file(std::string filename, Data data) {
  std::ofstream ofs;
  ofs.open(filename.c_str());
  if(!ofs.is_open()) {
    fprintf(stderr, "[ERROR] Can't create file.\n");
    exit(-1);
  }
  int size = data.students.size();
  ofs << data.code + "\n" << std::endl;
  ofs << std::fixed;
  ofs << std::setprecision(3);
  ofs << "Average: " << data.avg << std::endl;
  ofs << "Median: " << data.median << std::endl;
  ofs << "Std Dev : " << data.std_dev << std::endl;

  ofs << "Rank,Student ID,Grade" << std::endl;
  for (int i = 0; i < 1000000; i++) {
    ofs << i + 1 << "," << data.students[i].id <<   "," << data.students[i].grade << std::endl;
  }
  ofs.close();
}
