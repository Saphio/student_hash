#include <iostream>
#include <string>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include "Student.h"
#include "Node.h"

using namespace std;

// FUNCTION PROTOTYPES
void printCmds ();
// adding students
bool insert_student (Node** &ht, Student* s, int size);
void add (Node** &ht, int &size);
// removing students
void remove_student (Node** &ht, int id, int size);
void remove (Node** &ht, int size);
// print, generate random students, and quit
void display (Node** ht, int size);
void generate (Node** &ht, int &size, string fnames[200], string lnames[200]);
void quit (bool &status);
// hash stuff
int hashID (int id, int size);
bool rehash (Node** &ht, int oldSize);
void processNames (string fnames[200], string lnames[200]);

// MAIN FUNCTION
int main () {
  cout << "Beginning the Student List program." << endl;

  bool isRunning = true;
  // hash table
  int size = 101;  
  Node** ht = new Node* [size];
  for (int i = 0; i < size; i++) {
    ht[i] = NULL;
  }

  // pre-processing the names saves a bit of work later
  string fnames[200];
  string lnames[200];
  processNames(fnames, lnames);

  // main loop
  while (isRunning) {
    printCmds (); cout << endl;

    // input
    string input;
    getline(cin, input);

    // QUIT
    if (input == "QUIT") { quit (isRunning); }
    // GENERATE
    else if (input == "GENERATE") { generate (ht, size, fnames, lnames); }
    // DELETE
    else if (input == "DELETE") { remove (ht, size); }
    // PRINT
    else if (input == "PRINT") { display (ht, size); }
    // ADD
    else if (input== "ADD") { add (ht, size); }
    // bad input
    else { cout << "Bad input!" << endl; printCmds(); }
  } 
  return 0;
}

// FUNCTIONS
// print commands
void printCmds () {
  cout << endl << "Commands:" << endl;
  cout << "ADD (add student)" << endl;
  cout << "PRINT (print student list)" << endl;
  cout << "DELETE (delete student)" << endl;
  cout << "GENERATE (generate random students)" << endl;
  cout << "QUIT (quit program)" << endl;
}

// HASH STUFF

// pre-process names into respective arrays
void processNames (string fnames[200], string lnames[200]) {
  ifstream file_first ("fnames.txt");
  ifstream file_last ("lnames.txt");

  // iterate through each file, which has 200 names
  for (int i = 0; i < 200; i++) {
    getline(file_first, fnames[i]);
    getline(file_last, lnames[i]);
  }

  file_first.close(); file_last.close();
  return;
}

// hash function - TODODODODODO
int hashID (int id, int size) {
  return id % size;  
}

// rehash students if necessary
bool rehash (Node** &ht, int oldSize) {
  // essentially, make a new hash table, rehash, and reassign the new table
  // to the old one
  int newSize = oldSize * 2 + 1;
  Node** newHT = new Node* [newSize];
  for (int i = 0; i < newSize; i++) {
    newHT[i] = NULL;
  }
  bool hasCollision = false;
  for (int i = 0; i < oldSize; i++) {
    Node* cur = ht[i];
    Student* s;
    while (cur != NULL) {
      s = cur->getStudent();
      hasCollision |= insert_student (newHT, s, newSize);
      cur = cur->getNext();
    }
  }
  
  ht = newHT;
  return hasCollision;
}

// primary methods
// 1: ADD
bool insert_student (Node** &ht, Student* s, int size) {
  int idx = hashID(s->getID(), size);
  bool hasCollision = false;

  // no collision
  if (ht[idx] == NULL) {
    ht[idx] = new Node(s);
    ht[idx]->setNext(NULL);
  }

  // collision
  else {
    Node* cur = ht[idx];
    int i = 1;
    while (cur->getNext() != NULL) {
      cur = cur->getNext(); i++;
    }
    cur->setNext(new Node(s));
    cur = cur->getNext();
    cur->setNext(NULL);
      
    if (i >= 3) { // more than or equal to 3 nodes after the head
      hasCollision = true;
    }
  }
  return hasCollision;
}

void add (Node** &ht, int &size) {
  string first, last;
  int id;
  float gpa;
  // prompt for information
  cout << "Student's first name?" << endl;
  getline(cin, first); 
  cout << "Student's last name?" << endl;
  getline(cin, last); 
  cout << "Student's ID number?" << endl;
  cin >> id; cin.get();
  cout << "Student's GPA?" << endl;
  cin >> gpa; cin.get();
  // create student
  Student* s = new Student();
  s->setFirst (new string(first));
  s->setLast (new string(last));
  s->setID (id);
  s->setGPA (gpa);
  // insert in hash table
  bool hasCollision = insert_student (ht, s, size);
  while (hasCollision) {
    // rehash and change size
    cout << "Too many collisions! Rehashing..." << endl;
    hasCollision = rehash (ht, size);
    size *= 2; size++;
    cout << "Size of new table: " << size << endl;
  }
  return;
}

// 2: PRINT
void display (Node** ht, int size) {
  for (int i = 0; i < size; i++) {
    Node* cur = ht[i];
    // iterate through each head node in the hash table
    while (cur != NULL) {
      Student* s = cur->getStudent();
      cout << *(s->getFirst()) << " " << *(s->getLast()) << " -- ID: " << s->getID();
      cout << " -- GPA: " << fixed << setprecision(2) << s->getGPA() << endl;
      cur = cur->getNext();
    }
  }
  return;
}

// 3: DELETE
void remove_student (Node** &ht, int id, int size) {
  int idx = hashID(id, size);
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
  if (!found) { cout << "Student not found." << endl; return; }

  Student* s = cur->getStudent();
  Node* next = cur->getNext();
  
  // cur is the head node
  if (prev == NULL) { ht[idx] = next; }
  // cur is not the head node
  else { prev->setNext(next); }
  
  delete s; cout << "Student removed from database." << endl;

  return;
}

void remove (Node** &ht, int size) {
  cout << "ID number of student to be deleted?" << endl;
  int id;
  cin >> id; cin.get();

  // call deletion function
  remove_student(ht, id, size);
  return;
}

// 4: GENERATE
void generate (Node** &ht, int &size, string fnames[200], string lnames[200]) {
  cout << "How many students to generate?" << endl;
  int n;
  cin >> n; cin.get();
  if (n > 40000) { cout << "That's too many!" << endl; return; }

  srand(time(NULL));
  int id = 123456;
  for (int i = 0; i < n; i++) {
    int fidx = rand() % 200, lidx = rand() % 200;
    id += rand() % 100;
    float gpa = rand() % 400 * 0.01;
    string first = fnames[fidx];
    string last = lnames[lidx];

    // I did some copying and pasting here from the add function
    Student* s = new Student();
    s->setFirst (new string(first));
    s->setLast (new string(last));
    s->setID (id);
    s->setGPA (gpa);
    // insert in hash table
    bool hasCollision = insert_student (ht, s, size);
    while (hasCollision) {
      // rehash and change size
      cout << "Too many collisions! Rehashing..." << endl;
      hasCollision = rehash (ht, size);
      size *= 2; size++;
      cout << "Size of new table: " << size << endl;
    }
  } 
  return;
}

// 5: QUIT
void quit (bool &status) {
  cout << "Sorry to see you go." << endl;
  status = false;
  return;
}
