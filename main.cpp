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
void insert_student (Node** &ht, Student* s, int size);
void add (Node** &ht, int size);
// removing students
void remove_student (Node** &ht, int id, int size);
void remove (Node** &ht, int size);
// print, generate random students, and quit
void display (Node** ht, int size);
void generate (Node** &ht, int size, string fnames[200], string lnames[200]);
void quit (bool &status);
// hash stuff
int hashID (int id, int size);
void rehash (Node** &ht, int newSize, int oldSize);
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
    printCmds ();
    // input
    string input;
    getline(cin, input);

    cout << "Processing..." << endl;

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
  int idx = 0;
  
  for (
  
  return idx % size;  
}

// rehash students if necessary
void rehash (Node** &ht, int newSize, int oldSize) {
  // essentially, make a new hash table, rehash, and reassign the new table
  // to the old one
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
  int idx = hashID(s->getID(), size);

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
      cout << "Too many collisions! Rehashing..." << endl;
      int newSize = 2 * size + 1; 
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

void add (Node** &ht, int size) {
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
  insert_student (ht, s, size);
  return;
}

// 2: PRINT
void display (Node** ht, int size) {
  for (int i = 0; i < size; i++) {
    Node* temp = ht[i];
    // iterate through each head node in the hash table
    while (temp != NULL) {
      Student* s = temp->getStudent();
      cout << *(s->getFirst()) << " " << *(s->getLast()) << " -- ID: " << s->getID();
      cout << " -- GPA: " << fixed << setprecision(2) << s->getGPA() << endl;
      temp = temp->getNext();
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
void generate (Node** &ht, int size, string fnames[200], string lnames[200]) {
  cout << "How many students to generate?" << endl;
  int n;
  cin >> n; cin.get();
  if (n > 40000) { cout << "That's too many!" << endl; return; }

  srand(time(NULL));
  int id = 123456;

  for (int i = 0; i < n; i++) {
    int fidx = rand() % 200, lidx = rand() % 200;
    id ++;
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
    insert_student (ht, s, size);
  } 
  return;
}

// 5: QUIT
void quit (bool &status) {
  cout << "Sorry to see you go." << endl;
  status = false;
  return;
}
