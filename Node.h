using namespace std;

class Node{
    public: 
        Node(int newData);
        Node();
        ~Node();
        Node* getLeft();
        Node* getRight();
        int getData();
        void setLeft(Node* node);
        void setRight(Node* node);
    protected:
        int data;
        Node* left;
        Node* right;
};
