#include "Graph.h"
#include <iostream>
#include <random>
#include <queue>

void Graph::ELcalculate () {
    double value = 1;
    for(int index = 0; index < 2; index++) {
        value *= (value - index);
    }
    value /= 4;
    // C(vertex, 2)/2 => vertex * (vertex - 1) / 4
    edgeLimit = (int)value;
}

void Graph::setEdge() {
    std::cin >> edge; 
}

Graph::Graph (int n) : vertex(n) {
    ELcalculate();
    std::cout << "the range of edge is from 0 to " << edgeLimit << ".\n"; 
    do {
        setEdge();
        if(edge > edgeLimit) {
            std::cout << "the number is too large, please retype.\n";
        }
        if(edge < 0) {
            std::cout << "the number is too small, please retype.\n";
        }
    }while ((edge > edgeLimit) || (edge < 0));
}

void Graph::AMmaker() {
    int total_size = (vertex * (vertex - 1)) / 2;
    int list[total_size];

    random_device rd;
    mt19937 gen(rd());
    limit = 1 << (total_size) - 1;
    uniform_int_distribution<int> dist(0, limit);
    int random = dist(gen);

    for(int i = 0; i < total_size; i++) {
        list[i] = (random >> (total_size - i - 1)) & 1;
    }

    for(int i = 0; i < vertex; i++) {
        AdjMatrix[i][i] = 0;
    }

    int row = 0;
    int col = row + 1;
    int resist = vertex - 1;
    int count = 0;
    while(true) {
        AdjMatrix[row][col] = list[count];
        AdjMatrix[col][row] = list[count];
        count++;
        if(count == total_size) {
            break;
        }

        if(col + 1 > resist) {
            row++;
            col = row + 1;
        }else {
            col++;
        }
    }
}

void Graph::ALmaker() {
    for(int i = 0; i < vertex; i++) {
        AdjList[i].v = i;
        AdjList[i].next = nullptr;
    }

    for(int i = 0; i < vertex; i++) {
        for(int j = 0; j < vertex; j++) {
            if(AdjMatrix[i][j] == 1) {
                List *temp = new List;
                temp->v = j;
                temp->next = nullptr;
                List *current = &AdjList[i];
                while(current->next != nullptr) {
                    current = current->next;
                }
                current->next = temp;
            }
        }
    }
}

void Graph::AMprinter() {
    for(int i = 0; i < vertex; i++) {
        for(int j = 0; j < vertex; j++) {
            std::cout << AdjMatrix[i][j] << " ";
        }
        std::cout << "\n";
    }
}

void Graph::ALprinter() {
    for(int i = 0; i < vertex; i++) {
        List *current = &AdjList[i];
        while(current != nullptr) {
            std::cout << current->v << " -> ";
            current = current->next;
        }
        std::cout << "\n";
    }
}

void Graph::DFS() {
    fs *Darray = new fs[vertex];
    for(int i = 0; i < vertex; i++) {
        Darray[i].color = 0;
        Darray[i].d = 0;
        Darray[i].pi = -1;
    }

    int time = 0;
    for(int i = 0; i < vertex; i++) {
        if(Darray[i].color == 0) {
            DFSVisit(Darray, i, time);
        }
    }

    tree(Darray);
}

void Graph::DFSVisit(fs *Darray, int u, int &time) {
    time++;
    Darray[u].d = time;
    Darray[u].color = 1;
    List *temp = &AdjList[u];
    while(temp != nullptr) {
        if(Darray[temp->v].color == 0) {
            Darray[temp->v].pi = u;
            DFSVisit(Darray, temp->v, time);
        }
        temp = temp->next;
    }
    Darray[u].color = 2;
    time++;
}

void Graph::BFS() {
    fs *Barray = new fs[vertex];
    for(int i = 0; i < vertex; i++) {
        Barray[i].color = 0;
        Barray[i].d = 0;
        Barray[i].pi = -1;
    }

    int time = 0;
    for(int i = 0; i < vertex; i++) {
        if(Barray[i].color == 0) {
            BFSVisit(Barray, i, time);
        }
    }

    BFStree(Barray);
}

void Graph::BFSVisit(fs *Barray, int u, int &time) {
    std::queue<int> q;
    q.push(u);
    Barray[u].color = 1;
    while(!q.empty()) {
        int current = q.front();
        q.pop();
        List *temp = &AdjList[current];
        while(temp != nullptr) {
            if(Barray[temp->v].color == 0) {
                Barray[temp->v].color = 1;
                Barray[temp->v].d = Barray[current].d + 1;
                Barray[temp->v].pi = current;
                q.push(temp->v);
            }
            temp = temp->next;
        }
        Barray[current].color = 2;
    }
}

void Graph::tree(fs *Barray) {
    for(int i = 0; i < vertex; i++) {
        if(Barray[i].pi != -1) {
            std::cout << i << " -> " << Barray[i].pi << "\n";
        }
    }
}