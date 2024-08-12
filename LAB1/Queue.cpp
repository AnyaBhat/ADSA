#include <iostream>

#define MAX 100 // Define the maximum size of the queue

class Queue {
private:
    int arr[MAX];    // Array to hold the elements
    int front;       // Index of the front element
    int rear;        // Index of the rear element
    int size;        // Current number of elements in the queue

public:
    // Constructor
    Queue() : front(0), rear(-1), size(0) {}

    // Function to add an element to the rear of the queue
    void enqueue(int value) {
        if (isFull()) {
            std::cout << "Queue is full!" << std::endl;
            return;
        }
        rear = (rear + 1) % MAX; // Circular increment
        arr[rear] = value;
        size++;
    }

    // Function to remove an element from the front of the queue
    int dequeue() {
        if (isEmpty()) {
            std::cout << "Queue is empty!" << std::endl;
            return -1; // Sentinel value indicating an empty queue
        }
        int value = arr[front];
        front = (front + 1) % MAX; // Circular increment
        size--;
        return value;
    }

    // Function to check if the queue is empty
    bool isEmpty() const {
        return size == 0;
    }

    // Function to check if the queue is full
    bool isFull() const {
        return size == MAX;
    }

    // Function to get the size of the queue
    int getSize() const {
        return size;
    }

    // Function to display the elements of the queue
    void display() const {
        if (isEmpty()) {
            std::cout << "Queue is empty!" << std::endl;
            return;
        }
        std::cout << "Queue elements: ";
        for (int i = 0; i < size; i++) {
            std::cout << arr[(front + i) % MAX] << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    Queue q;

    // Enqueue some elements
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);

    // Display the queue
    q.display(); // Output: Queue elements: 10 20 30

    // Dequeue an element
    std::cout << "Dequeued: " << q.dequeue() << std::endl; // Output: Dequeued: 10

    // Display the queue again
    q.display(); // Output: Queue elements: 20 30

    // Check the size
    std::cout << "Queue size: " << q.getSize() << std::endl; // Output: Queue size: 2

    // Enqueue more elements
    q.enqueue(40);
    q.enqueue(50);

    // Display the queue
    q.display(); // Output: Queue elements: 20 30 40 50

    return 0;
}
