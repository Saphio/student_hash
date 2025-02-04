#include <iostream>
#include <string>
#include "Student.h"

using namespace std;

// constructor/destructor
Student::Student() {
  string* first = new string();
  string* last = new string();
  id = 0;
  gpa = 0.0;
}

// destructor
Student::~Student() {
  delete first;
  delete last;
}

// getters
// get name
string* Student::getFirst () {
  return first;
}

string* Student::getLast () {
  return last;
}

// get id
int Student::getID() {
  return id;
}

// get gpa
float Student::getGPA() {
  return gpa;
}

// setters
// set name
void Student::setFirst (string* f) {
  first = f;
}

void Student::setLast (string* l) {
  last = l;
}

// set gpa
void Student::setGPA (float g) {
  gpa = g;
}

// set id
void Student::setID (int i) {
  id = i;
}
