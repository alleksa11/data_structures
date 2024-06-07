#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <climits> // добавляем эту библиотеку для INT_MIN

using namespace std;
using namespace std::chrono;

struct Node {
    int data;
    Node* next;
};

class LinkedListQueue {
private:
    Node *front, *rear;

public:
    LinkedListQueue() {
        front = rear = nullptr;
    }

    ~LinkedListQueue() {
        while (front != nullptr) {
            Node* temp = front;
            front = front->next;
            delete temp;
        }
    }

    bool isEmpty() {
        return front == nullptr;
    }

    void enqueue(int item) {
        Node* temp = new Node();
        temp->data = item;
        temp->next = nullptr;
        if (rear == nullptr) {
            front = rear = temp;
            return;
        }
        rear->next = temp;
        rear = temp;
    }

    int dequeue() {
        if (isEmpty())
            return INT_MIN;
        Node* temp = front;
        front = front->next;
        if (front == nullptr)
            rear = nullptr;
        int item = temp->data;
        delete temp;
        return item;
    }

    int frontItem() {
        if (isEmpty())
            return INT_MIN;
        return front->data;
    }

    int rearItem() {
        if (isEmpty())
            return INT_MIN;
        return rear->data;
    }
};

struct Point {
    int x, y;
};

bool isValid(int x, int y, vector<vector<int>>& maze, vector<vector<bool>>& visited) {
    int N = maze.size();
    int M = maze[0].size();
    return (x >= 0 && x < N && y >= 0 && y < M && maze[x][y] == 0 && !visited[x][y]);
}

bool bfs(Point start, Point end, vector<vector<int>>& maze) {
    vector<vector<bool>> visited(maze.size(), vector<bool>(maze[0].size(), false));
    LinkedListQueue q;
    q.enqueue(start.x * maze[0].size() + start.y);
    visited[start.x][start.y] = true;

    int rowNum[] = {-1, 0, 0, 1};
    int colNum[] = {0, -1, 1, 0};

    while (!q.isEmpty()) {
        int currIndex = q.dequeue();
        Point curr = {currIndex / maze[0].size(), currIndex % maze[0].size()};

        if (curr.x == end.x && curr.y == end.y) {
            return true;
        }

        for (int i = 0; i < 4; i++) {
            int row = curr.x + rowNum[i];
            int col = curr.y + colNum[i];

            if (isValid(row, col, maze, visited)) {
                visited[row][col] = true;
                q.enqueue(row * maze[0].size() + col);
            }
        }
    }

    return false;
}

void generateMaze(int N, int M, vector<vector<int>>& maze) {
    srand(time(0));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            maze[i][j] = rand() % 2;
        }
    }
    // Ensure the entrances and exits are open
    for (int i = 0; i < M; i++) {
        maze[0][i] = 0;
        maze[N-1][i] = 0;
    }
}

int main() {
    int N, M;
    cout << "Enter the dimensions of the maze (N M): ";
    cin >> N >> M;

    vector<vector<int>> maze(N, vector<int>(M));
    generateMaze(N, M, maze);

    vector<Point> entrances, exits;
    for (int i = 0; i < M; i++) {
        if (maze[0][i] == 0) {
            entrances.push_back({0, i});
        }
        if (maze[N-1][i] == 0) {
            exits.push_back({N-1, i});
        }
    }

    auto start = high_resolution_clock::now();

    // Проверка, можно ли провести каждого человека от его входа до его выхода
    bool canAllReachTheirExits = true;
    for (int i = 0; i < entrances.size(); i++) {
        if (!bfs(entrances[i], exits[i % exits.size()], maze)) {
            canAllReachTheirExits = false;
            break;
        }
    }

    // Проверка, можно ли вывести каждого человека через любой из выходов
    bool canAllReachAnyExit = true;
    for (int i = 0; i < entrances.size(); i++) {
        bool canReach = false;
        for (int j = 0; j < exits.size(); j++) {
            if (bfs(entrances[i], exits[j], maze)) {
                canReach = true;
                break;
            }
        }
        if (!canReach) {
            canAllReachAnyExit = false;
            break;
        }
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Can all reach their specific exits: " << (canAllReachTheirExits ? "Yes" : "No") << endl;
    cout << "Can all reach any exit: " << (canAllReachAnyExit ? "Yes" : "No") << endl;
    cout << "Time taken for maze solving: " << duration.count() << " microseconds" << endl;

    return 0;
}
