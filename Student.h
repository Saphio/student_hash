#ifndef STUDENT_H
#define STUDENT_H

#include <cstring>

using namespace std;

class Student {
 public:
  // constructors, destructors
  Student();
  ~Student();
  // getters
  char* getFirst();
  char* getLast();
  int getID();
  float getGPA();
  // setters
  void setFirst (char*);
  void setLast (char*);
  void setID(int);
  void setGPA (float);
 private:
  char* first;
  char* last;
  int id;
  float gpa;
};

#endif
