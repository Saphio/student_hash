#ifndef STUDENT_H
#define STUDENT_H

#include <string>

using namespace std;

class Student {
 public:
  // constructors, destructors
  Student();
  ~Student();
  // getters
  string* getFirst();
  string* getLast();
  int getID();
  float getGPA();
  // setters
  void setFirst (string*);
  void setLast (string*);
  void setID(int);
  void setGPA (float);
 private:
  string* first;
  string* last;
  int id;
  float gpa;
};

#endif
