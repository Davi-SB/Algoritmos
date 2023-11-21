#include <iostream>
using namespace std;

#define MAX_CAPACITY 10

int queue[MAX_CAPACITY];
int front = -1;
int rear = -1;

bool isFull() {
    if ((rear + 1) % MAX_CAPACITY == front) return true;
    else return false;
}

bool isEmpty() {
    if (front == -1) return true;
    else return false;
}

void CreateQueue() {
    front = -1;
    rear = -1;
}

// Function to enqueue an element
void Enqueue(int element) {
    if (isFull()) {
        cout << "Queue is full. Unable to enqueue " << element << endl;
        return;
    }
    if (isEmpty()) {
        front = 0;
    }
    rear = (rear + 1) % MAX_CAPACITY;
    queue[rear] = element;
    cout << "Enqueued " << element << endl;
}

// Function to dequeue an element
int Dequeue() {
    if (isEmpty()) {
        cout << "Queue is empty. Unable to dequeue" << endl;
        return -1;
    }
    int element = queue[front];
    if (front == rear) {
        front = -1;
        rear = -1;
    } else {
        front = (front + 1) % MAX_CAPACITY;
    }
    cout << "Dequeued " << element << endl;
    return element;
}

// Function to print the queue
void PrintQueue() {
    if (isEmpty()) {
        cout << "Queue is empty" << endl;
        return;
    }
    int i;
    cout << "Queue elements are: ";
    for (i = front; i != rear; i = (i + 1) % MAX_CAPACITY) {
        cout << queue[i] << " ";
    }
    cout << queue[i] << endl;
}

int main() {
    CreateQueue();
    Enqueue(5);
    Enqueue(6);
    Enqueue(7);
    Enqueue(8);
    Enqueue(9);
    Enqueue(10);
    Enqueue(11);
    PrintQueue();
    Dequeue();
    Dequeue();
    PrintQueue();
    return 0;
}