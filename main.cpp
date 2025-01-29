#include <iostream>
#include <vector>
#include <cstring>
#include <iomanip>
#include "Student.h"
#include "Node.h"

using namespace std;

// function prototypes
int checkInput (char input[80]);
void printCmds ();
void add (Node* &head);
void recurse (int id, Node* &head, Node* previous, Node* current);
void remove (Node* &head);
void display (Node* n);
void average (Node* s, int students, float runningTotal);
void quit (bool &status);

// main function
int main () {
  cout << "Beginning the Student List program." << endl;

  bool isRunning = true;
  // head node
  Node* head = NULL;

  while (isRunning) {
    printCmds ();
    // input
    char input[80];
    cin.get(input, 80);
    cin.get();
    int cmd;
    while (checkInput(input) == 0) {
      cout << "Not a command. HELP for command list." << endl;
      if (input[0] == '\n') {
	cin.clear();
	cin.ignore();
      }
      cout << "Enter command:" << endl;
      cin.get(input, 80);
      cin.get();
    }
    // commands
    cmd = checkInput(input);
    if (cmd == 5) { // QUIT
      quit (isRunning);
    }
    else if (cmd == 4) { // AVERAGE
      average (head, 0, 0);
    }
    else if (cmd == 3) { // DELETE
      remove (head);
    }
    else if (cmd == 2) { // PRINT
      display (head);
    }
    else if (cmd == 1) { // ADD
      add (head);
    }
    else {
      cout << "Unknown error occurred." << endl;
      isRunning = false;
    }
  } 
  return 0;
}

// functions
// print commands
void printCmds () {
  cout << endl << "Commands:" << endl;
  cout << "ADD (add student)" << endl;
  cout << "PRINT (print student list)" << endl;
  cout << "DELETE (delete student)" << endl;
  cout << "AVERAGE (print average GPA)" << endl;
  cout << "QUIT (quit program)" << endl;
}

// parse move input
/*
  0 = bad input
  1 = ADD
  2 = PRINT
  3 = DELETE
  4 = AVERAGE
  5 = QUIT
 */
int checkInput (char input[80]) {
  if (strcmp(input, "ADD") == 0) { return 1; }
  else if (strcmp(input, "PRINT") == 0) { return 2; }
  else if (strcmp(input, "DELETE") == 0) { return 3; }
  else if (strcmp(input, "AVERAGE") == 0) { return 4; }
  else if (strcmp(input, "QUIT") == 0) { return 5; }
  return 0;
}

// primary methods
// 0: INSERT
void insert (Student* &s, Node* &head, Node* previous, Node* current) {
  // no students
  if (head == NULL) {
    head = new Node(s);
    return;
  }
  // insert before head student
  else if (s->getGPA() < head->getStudent()->getGPA()) {
    Node* temp = head;
    head = new Node(s);
    head->setNext(temp);
    return;
  }
  // last student
  else if (current == NULL) {
    Node* temp = new Node(s);
    previous->setNext(temp);
    previous->getNext()->setNext(NULL);
    return;
  }
  // between students
  else if (s->getGPA() < current->getStudent()->getGPA()) {
    Node* temp = new Node(s);
    previous->setNext(temp);
    temp->setNext(current);
    return;
  }
  // recurse
  else {
    insert(s, head, current, current->getNext());
  }
}

// 1: ADD
void add (Node* &head) {
  char first[80], last[80];
  int id;
  float gpa;
  // prompt for information
  cout << "Student's first name?" << endl;
  cin.get(first, 80);
  cin.get();
  cout << "Student's last name?" << endl;
  cin.get(last, 80);
  cin.get();
  cout << "Student's ID number?" << endl;
  cin >> id;
  cin.get();
  cout << "Student's GPA?" << endl;
  cin >> gpa;
  cin.get();
  // create student
  Student* s = new Student();
  s->setFirst (first);
  s->setLast (last);
  s->setID (id);
  s->setGPA (gpa);
  // insert in linked list
  insert(s, head, head, head);
  return;
}

// 2: PRINT
void display (Node* n) {
  if (n != NULL) {
    // print
    Student* s = n->getStudent();
    cout << s->getFirst() << " " << s->getLast() << " -- ID: " << s->getID();
    cout << " -- GPA: " << fixed << setprecision(2) << s->getGPA() << endl;
    // recurse
    if (n->getNext() != NULL) {
      display(n->getNext());
    }
  }
  return;
}

// 3: DELETE
void recurse (int id, Node* &head, Node* previous, Node* current) {
  // no students
  if (head == NULL) {
    cout << "You have no students!" << endl;
    return;
  }
  // head is the student
  else if (id == head->getStudent()->getID()) {
    Student* s = head->getStudent();
    Node* next = head->getNext();
    head = next;
    delete s;
    cout << "Poof! They're gone." << endl;
    return;
  }
  // student not found
  else if (current == NULL) {
    cout << "That student doesn't exist!" << endl;
    return;
  }
  // student is the current node
  else if (id == current->getStudent()->getID()) {
    Student* s = current->getStudent();
    Node* next = current->getNext();
    previous->setNext(next);
    delete s;
    cout << "Poof! They're gone." << endl;
    return;
  }
  // go to next student
  else {
    recurse (id, head, current, current->getNext());
  }
}
  
 
void remove (Node* &head) {
  cout << "ID number of student to be deleted?" << endl;
  int num;
  cin >> num;
  cin.get();
  // call recursion function
  recurse (num, head, head, head);
  return;
}

// 4: AVERAGE
void average (Node* s, int students, float runningTotal) {
  // no students (avoid divide-by-zero error)
  if (s == NULL) {
    cout << "Average GPA: 0.00" << endl;
  }
  // add to running total
  else {
    runningTotal += s->getStudent()->getGPA();
    students ++;
    // no students left
    if (s->getNext() == NULL) {
      cout << "Average GPA: " << fixed << setprecision(2) << (float)runningTotal/(float)students << endl;
      return;
    }
    // recurse
    average(s->getNext(), students, runningTotal);
  }
}

// 5: QUIT
void quit (bool &status) {
  cout << "Sorry to see you go." << endl;
  status = false;
  return;
}
