//Richard Zhang P.7
//Binary Search Tree

#include <iostream>
#include <cstring>
#include <fstream>
#include "Node.h"


using namespace std;

void strToLower(char* a);
void addNode(Node* head, int number, Node* &treeHead); // Number added to tree
void printTree(Node* head, int level); //prints the tree
Node* nodeSearch (Node* head, int number, Node* &parent, bool &right); //Value in tree and returns 
bool deleteNode(Node* &head, int number); //Deletes the node

void configureInput(ifstream &stream, bool &isFile){
  //take input from text or from a file
  
  char input[128];
  isFile = false;
  
  cout << "Do you want to 1) read from a file or 2) from a text" << endl;
  cin.getline(input,128);
  strToLower(input);
  
  if(input[0] == '1'){
    cout << "What is the file" << endl;
    cin.getline(input,128);
    stream.open(input);
    if(stream.is_open()){
      isFile = true;
    }
    else{
      cout << "The file could not be opened. Please enter through the command line" << endl;
    }
  }
  else{
    cout << "Please enter through the command line" << endl;
  }
}
void addNumbers(istream &from, Node* &head){
  //goes through a stream and adds them to the tree
  int newInput;
  from >> newInput;
  addNode(head,newInput,head);
  while(from.peek() != '\n' && !from.eof()){
    if(isdigit(from.peek())){
      from >> newInput;
      addNode(head,newInput,head);
    }
    else{
      from.ignore();
    }
  }
}

int main(){
  
  Node* head = NULL;
  bool running = true;
  char input[30];

  while (running == true){
    cin.getline(input,30);
    strToLower(input);
    if (!strcmp(input,"add")){
      ifstream stream;
      bool isFile;
      configureInput(stream, isFile);
      addNumbers(isFile ? stream : cin, head);
      if(isFile) stream.close();
      cin.ignore();
    }
    else if (!strcmp(input,"print")){
      if(head){
	printTree(head,0);
      }
      else
	cout << "There is nothing to print" << endl;
    }
    else if(!strcmp(input,"search")){
      if (head){
	cout << "What number are you looking for?" << endl;
	int number;
	Node* parent;
	bool right;
	cin >> number;
	if (nodeSearch(head,number,parent,right)){
	  cout << number << " is in the tree" << endl;
	}
	else{
	  cout << number << " is not in the tree" << endl;
	}
      }
      else{
	cout << "You can't search an empty tree." << endl;
      }
    }
    else if(!strcmp(input,"delete")){
      if (head){
        cout << "What number are you looking for?" << endl;
        int number;
	cin >> number;
	if (deleteNode(head,number)){
	  cout << number << " has been deleted" << endl;
        }
        else{
          cout << number << " is not in the tree" << endl;
        }
      }
      else{
        cout << "You can't delete a node from an empty tree" << endl;
      } 
    }	   
    else{
      cout << "Please input ADD, SEARCH, DELETE" << endl;
    }
  }
} 

void strToLower(char* a){ //converts words to lower
  while(*a){
    *a = tolower(*a);
    a++;
  }
}
void addNode(Node* head, int number, Node* &treeHead){
  if (treeHead == NULL){
    treeHead = new Node(number);
  }
  else if (number < head->getData()){
    if (head->getLeft()){
      addNode(head->getLeft(),number,treeHead);
    }
    else{
      head->setLeft(new Node(number));
    }
  }
  else if (number > head->getData()){
    if (head->getRight()){
      addNode(head->getRight(),number,treeHead);
    }
    else{
      head->setRight(new Node(number));
    }
  }
}
void printTree(Node* head, int level){
  level ++;
  if(head->getRight()){
    printTree(head->getRight(), level);
  }
  for (int i = 0; i < level; i++){
    cout << " ";
  }
  cout << head->getData() << endl;
  if(head->getLeft()){
    printTree(head->getLeft(), level);
  } 
}
Node* nodeSearch(Node* head, int number, Node* &parent, bool &right){
  if (number < head->getData()){
    if(head->getLeft()){
      right = false;
      parent = head;
      return nodeSearch(head->getLeft(), number, parent,right);
    }
    else return NULL;
  }
  else if (number > head->getData()){
    if(head->getRight()){
      right = true;
      parent = head;
      return nodeSearch(head->getRight(), number,parent,right);
    }
    else return NULL;
  }
  else return head;
}
bool deleteNode(Node* &head, int number){
  Node* parent;
  Node* dNode;
  bool right;
  Node* toSwap = NULL;
  dNode = nodeSearch(head,number,parent,right);
  if (!dNode){
    return false;
  }
  if (!dNode->getLeft() && !dNode->getRight()){
    toSwap = NULL;
  }
  else if(!dNode->getRight()){
    toSwap = dNode->getLeft();
  }
  else if(!dNode->getLeft()){
    toSwap = dNode->getRight();
  }
  else if(!dNode->getLeft()->getRight()){
    Node* current = dNode->getLeft();
    current->setRight(dNode->getRight());
    toSwap = current;
  }
  else{
    Node* leftRoot = dNode->getLeft();
    Node* current = dNode->getLeft()->getRight();
    Node* currentParent = leftRoot;
    while(current->getRight()){
      currentParent = current;
      current = current->getRight();
    }
    currentParent->setRight(current->getLeft());
    current->setLeft(leftRoot);
    current->setRight(dNode->getRight());
    toSwap = current; 
  
  }
  if(head == dNode) head = toSwap;
  else if(right) parent->setRight(toSwap);
  else parent->setLeft(toSwap);
  return true;
}
