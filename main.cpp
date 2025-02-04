#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>
#include "Student.h"
#include "Node.h"

using namespace std;

// function prototypes
void printCmds ();
void insert_student (Node** &ht, Student* s, int size);
void add (Node** &ht, int size);
void remove_student (Node** &ht, int id, int size);
void remove (Node** &ht, int size);
void display (Node** ht, int size);
void generate (Node** &ht, int size); // TODO
void quit (bool &status);

int hash (int id, int size);
void rehash (Node** &ht, int newSize, int oldSize);

// main function
int main () {
  cout << "Beginning the Student List program." << endl;

  bool isRunning = true;
  // hash table
  int size = 211;  
  Node** ht = new Node* [size];
  for (int i = 0; i < size; i++) {
    ht[i] = NULL;
  }
  
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

    // QUIT
    if (strcmp(input, "QUIT") == 0) { quit (isRunning); }
    // GENERATE
    else if (strcmp(input, "GENERATE") == 0) { generate (ht); } // TODO
    // DELETE
    else if (strcmp(input, "DELETE") == 0) { remove (ht); }
    // PRINT
    else if (strcmp(input, "PRINT") == 0) { display (ht); }
    // ADD
    else if (strcmp(input, "ADD") == 0) { add (ht); }
    // ???
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
  cout << "GENERATE (generate random students)" << endl;
  cout << "QUIT (quit program)" << endl;
}

// TODODODODODOO

// hash function
int hash (int id, int size) {
  int idx = 0;
  

  return idx % size;  
}

void rehash (Node** &ht, int newSize, int oldSize) {
  Node** newHT = new Node* [newSize];
  for (int i = 0; i < oldSize; i++) {
    Node* temp = ht[i];
    Student* s;
    while (temp != NULL) {
      s = temp->getStudent();
      insert_student (newHT, s, newSize);
      temp = temp->getNext();
    }
  }
  
  ht = newHT;
  return;
}

// primary methods
// 1: ADD
void insert_student (Node** &ht, Student* s, int size) {
  int idx = hash(s->getID(), size);

  // no collision
  if (ht[idx] == NULL) {
    ht[idx] = new Node(s);
    ht[idx]->setNext(NULL);
  }

  // collision
  else {
    Node* temp = ht[idx];
    int i = 1;
    while (temp->getNext() != NULL) {
      temp = temp->getNext(); i++;
    }
    if (i > 3) {
      // rehash and change size
      cout << "rehashing..." << endl;
      int newSize = 2 * size + 1; // CHANGE THIS LATER
      rehash (ht, newSize, size);
    }
    else {
      temp->setNext(new Node(s));
      temp = temp->getNext();
      temp->setNext(NULL);
    }
  }
  return;
}

void add (Node* &ht) {
  char first[80], last[80];
  int id;
  float gpa;
  // prompt for information
  cout << "Student's first name?" << endl;
  cin.get(first, 80); cin.get();
  cout << "Student's last name?" << endl;
  cin.get(last, 80); cin.get();
  cout << "Student's ID number?" << endl;
  cin >> id; cin.get();
  cout << "Student's GPA?" << endl;
  cin >> gpa; cin.get();
  // create student
  Student* s = new Student();
  s->setFirst (first);
  s->setLast (last);
  s->setID (id);
  s->setGPA (gpa);
  // insert in hash table
  insert_student (ht, s);
  return;
}

// 2: PRINT
void display (Node** ht, int size) {
  for (int i = 0; i < size; i++) {
    Node* temp = ht[i];
    while (temp != NULL) {
      Student* s = temp->getStudent();
      cout << s->getFirst() << " " << s->getLast() << " -- ID: " << s->getID();
      cout << " -- GPA: " << fixed << setprecision(2) << s->getGPA() << endl;
      temp = temp->getNext();
    }
  }
  return;
}

// 3: DELETE
void remove_student (Node** &ht, int id, int size) {
  int idx = hash(id);
  Node* cur = ht[idx]; Node* prev = NULL;
  bool found = false;

  // iterate until the student is found
  while (cur != NULL && !found) {
    if (cur->getStudent()->getID() == id) {
      found = true;
    }
    else {
      prev = cur;
      cur = cur->getNext();
    }
  }
  
  // not found
  if (!found) { cout << "Student not found."; return; }

  // cur is the head node
  if (prev == NULL) { 
    Student* s = cur->getStudent();
    Node* next = cur->getNext();
    ht[idx] = next;
    delete s; cout << "Student removed from database." << endl;
    return;
  }

  // cur is not the head node
  else {
    Student* s = cur->getStudent();
    Node* next = cur->getNext();
    prev->setNext(next); 
    delete s; cout << "Student removed from database." << endl;
    return;
  }
  return;
}
  
 
void remove (Node** ht, int size) {
  cout << "ID number of student to be deleted?" << endl;
  int num;
  cin >> num;
  cin.get();
  // call deletion function
  remove_student (Node** ht, int id, int size);
  return;
}

// 4: GENERATE
void generate (Node** ht) {
  ifstream fnames ("fnames.txt");
  ifstream lnames ("lnames.txt");


  fnames.close(); lnames.close();
  return;
}

// 5: QUIT
void quit (bool &status) {
  cout << "Sorry to see you go." << endl;
  status = false;
  return;
}
