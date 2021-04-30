#include <iostream>
using namespace std;

struct IntNode{
    // Node with pointer to another node.
    IntNode *next;
    int value;

    IntNode(int n=0){
        next = NULL;
        value = n;
    }
};

struct LinkedList{
    // Implementation of singly-linked list.
    IntNode *head;
    LinkedList(){
        head = NULL;
    }

    void append(int n){
        IntNode *node = new IntNode(n);
        node->next = head;
        head = node;
    }

    ~LinkedList(){
        // Go through all nodes and delete
        IntNode *currentNode = head;
        while (currentNode != NULL){
            IntNode *temp = currentNode;
            currentNode = temp->next;
            delete temp;
            temp = NULL;
        }
    }
};

struct IntStack{
    // Implementation of stack using linked list.
    LinkedList stack;
    int length;

    IntStack(){
        length = 0;
    }

    void push(int n){
        stack.append(n);
        length += 1;
    }

    int pop(){
        // Return the value of the most recent insert.
        // Move the head once to the right
        // and delete the previous head node.
        IntNode *temp = stack.head;
        int value = stack.head->value;
        stack.head = stack.head->next;
        length -= 1;
        delete temp;
        temp = NULL;
        return value;
    }
};

int main(){
    // Node
    IntNode n1(1);
    IntNode n2(2);
    IntNode n3(3);

    n1.next = &n2;
    n2.next = &n3;

    IntNode *currentNode = &n1;
    cout << "IntNode:" << endl;
    while (currentNode != NULL){
        cout << "Node value: " << currentNode->value << endl;
        currentNode = currentNode->next;
    }

    // LinkedList
    cout << "LinkedList:" << endl;
    LinkedList ll = LinkedList();

    for (int i=0; i <= 5; i++) {
        cout << "Appending: " << i << endl;
        ll.append(i);
    }
    cout << "Traversal:" << endl;
    currentNode = ll.head;
    while (currentNode != NULL){
        cout << "Current node value: " << currentNode->value << endl;
        currentNode = currentNode->next;
    }

    // Stack
    cout << "Stack:" << endl;
    IntStack myStack;
    for (int i=0; i <= 5; i++) {
        cout << "Pushing: " << i << endl;
        myStack.push(i);
    }
    while (myStack.length != 0){
        cout << "Popped value:" << myStack.pop() << endl;
    }
}