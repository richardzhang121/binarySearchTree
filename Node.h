//Methods that will be used for binary search tree

using namespace std;


class Node{
 public:
  Node(int newData);
  Node();
  ~Node();
  Node* getLeft(); //returns the next node
  Node* getRight();
  int getData(); //returns the student the node points to
  void setLeft(Node* node); //sets the pointer to the next node
  void setRight(Node* node); 
 protected:
  int data;
  Node* left;
  Node* right;
};
