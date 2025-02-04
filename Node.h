#ifndef NODE_H
#define NODE_H

#include "Student.h"
#include <iostream>
#include <cstring>

using namespace std;

class Node{
 public:
  Node(Student* newstudent); //constructor (accepts student pointer)
  ~Node(); //destructor
  Node* getNext(); //gets next node in the linked list
  void setNext(Node* newnext); //set the next node
  Student* getStudent(); //get value of node
private:
  Student* student;
  Node* next;
};

#endif
