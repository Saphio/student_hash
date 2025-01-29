#include <iostream>
#include <cstring>
#include "Student.h"

using namespace std;

// constructor/destructor
Student::Student() {
  first = new char[80];
  last = new char[80];
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
char* Student::getFirst () {
  return first;
}

char* Student::getLast () {
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
void Student::setFirst (char* f) {
  strcpy(first, f);
}

void Student::setLast (char* l) {
  strcpy(last, l);
}

void Student::setGPA (float g) {
  gpa = g;
}

void Student::setID (int i) {
  id = i;
}
