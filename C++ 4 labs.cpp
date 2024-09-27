MAIN.CPP
#include <iostream>
#include <vector>
#include "Maze.h"

int main() {
    bool continueRunning = true;

    while (continueRunning) {
        Maze maze;
        maze.inputMaze();

        int startX, startY, endX, endY;

        std::cout << "Enter startX (0-" << Maze::N - 1 << "): ";
        std::cin >> startX;
        std::cout << "Enter startY (0-" << Maze::N - 1 << "): ";
        std::cin >> startY;
        std::cout << "Enter endX (0-" << Maze::N - 1 << "): ";
        std::cin >> endX;
        std::cout << "Enter endY (0-" << Maze::N - 1 << "): ";
        std::cin >> endY;

        if (startX < 0 || startX >= Maze::N || startY < 0 || startY >= Maze::N ||
            endX < 0 || endX >= Maze::N || endY < 0 || endY >= Maze::N) {
            std::cout << "Invalid input. Start and end points must be within the maze boundaries." << std::endl;
            continue;
        }

        if (maze.findShortestPath(startX, startY, endX, endY)) {
            std::cout << "Shortest path found!" << std::endl;
            maze.printMazeWithPath(startX, startY, endX, endY);
        } else {
            std::cout << "No path found!" << std::endl;
        }

        // Clear the solution for the next run
        maze.clearSolution();
    }

    return 0;
}

//////////////////////////////////////////
MAZE.H
#ifndef MAZE_H
#define MAZE_H

#include "Stack.h"
#include "Queue.h"

class Maze {
public:
    static const int N = 5;

    Maze();

    void inputMaze();
    bool findShortestPath(int startX, int startY, int endX, int endY);
    void printMazeWithPath(int startX, int startY, int endX, int endY);
    void clearSolution();

private:
    int maze[N][N];
    int solution[N][N];
};

#endif
/////////////////////////////////////////////////
MAZE.CPP
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Maze.h"
#include <vector> // Добавьте эту строку


Maze::Maze() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            maze[i][j] = 0;
            solution[i][j] = 0;
        }
    }
}

void Maze::inputMaze() {
    std::cout << "Enter the maze (0 for empty cell, 1 for blocked cell):\n";
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            std::cin >> maze[i][j];
            solution[i][j] = 0;
        }
    }
}

bool Maze::findShortestPath(int startX, int startY, int endX, int endY) {
    Queue queue;
    queue.push(startX, startY);

    std::vector<std::vector<int>> dist(N, std::vector<int>(N, -1));
    dist[startX][startY] = 0;

    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};

    while (!queue.isEmpty()) {
        int x = queue.frontX();
        int y = queue.frontY();

        queue.pop();

        for (int i = 0; i < 4; ++i) {
            int newX = x + dx[i];
            int newY = y + dy[i];

            if (newX >= 0 && newX < N && newY >= 0 && newY < N &&
                maze[newX][newY] == 0 && dist[newX][newY] == -1) {
                queue.push(newX, newY);
                dist[newX][newY] = dist[x][y] + 1;
            }
        }
    }

    if (dist[endX][endY] == -1) {
        return false; // No path found
    }

    // Backtrack and mark only the shortest path
    int x = endX;
    int y = endY;

    while (x != startX || y != startY) {
        solution[x][y] = 2;
        for (int i = 0; i < 4; ++i) {
            int newX = x + dx[i];
            int newY = y + dy[i];
            if (newX >= 0 && newX < N && newY >= 0 && newY < N && dist[newX][newY] == dist[x][y] - 1) {
                x = newX;
                y = newY;
                break;
            }
        }
    }
    solution[startX][startY] = 2;

    return true;
}

void Maze::printMazeWithPath(int startX, int startY, int endX, int endY) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (solution[i][j] == 2) {
                std::cout << "* ";
            } else {
                std::cout << maze[i][j] << " ";
            }
        }
        std::cout << std::endl;
    }
}

void Maze::clearSolution() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            solution[i][j] = 0;
        }
    }
}
////////////////////////////////////////////////////////
STACK.H
#ifndef STACK_H
#define STACK_H

struct Node {
    int x, y;
    Node* next;
};

class Stack {
public:
    Stack();
    ~Stack();

    void push(int x, int y);
    void pop();
    bool isEmpty();
    int topX();
    int topY();

private:
    Node* top;
};

#endif
////////////////////////////////////////////////////////
STACK.CPP
#include "Stack.h"

Stack::Stack() : top(nullptr) {}

Stack::~Stack() {
    while (!isEmpty()) {
        pop();
    }
}

void Stack::push(int x, int y) {
        Node* newNode = new Node;
        newNode->x = x;
        newNode->y = y;
        newNode->next = top;
        top = newNode;
}

void Stack::pop() {
        if (top) {
            Node* temp = top;
            top = top->next;
            delete temp;
        }
}

bool Stack::isEmpty() {
        return top == nullptr;
}

int Stack::topX() {
        if (top) {
            return top->x;
        }
        return -1; // Handle empty stack
}

int Stack::topY() {
        if (top) {
            return top->y;
        }
        return -1; // Handle empty stack
}
////////////////////////////////////////////////////////////////
Queue.h
#ifndef QUEUE_H
#define QUEUE_H

struct QueueNode {
    int x, y;
    QueueNode* next;
};

class Queue {
public:
    Queue();
    ~Queue();

    void push(int x, int y);
    void pop();
    bool isEmpty();
    int frontX();
    int frontY();

private:
    QueueNode* front;
    QueueNode* rear;
};

#endif
///////////////////////////////////////////////////////////
Queue.cpp
#include "Queue.h"

Queue::Queue() : front(nullptr), rear(nullptr) {}

Queue::~Queue() {
    while (!isEmpty()) {
        pop();
    }
}

void Queue::push(int x, int y) {
        QueueNode* newNode = new QueueNode;
        newNode->x = x;
        newNode->y = y;
        newNode->next = nullptr;

        if (rear == nullptr) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
}

void Queue::pop() {
        if (front == nullptr) {
            return;
        }

        QueueNode* temp = front;
        front = front->next;
        if (front == nullptr) {
            rear = nullptr;
        }
        delete temp;
}

bool Queue::isEmpty() {
        return front == nullptr;
}

int Queue::frontX() {
        if (front) {
            return front->x;
        }
        return -1; // Handle empty queue
}

int Queue::frontY() {
        if (front) {
            return front->y;
        }
        return -1; // Handle empty queue
}
