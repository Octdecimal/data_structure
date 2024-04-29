#include "Graph.h"
#include <iostream>
#include <random>
#include <queue>
#include <fstream>
//#include <crtdbg.h>

void Graph::ENLcal() {
    double value = 1;
    for(int index = 0; index < 2; index++) {
        value *= (vertex - index);
    }
    value /= 2;
    edgeNumLimit = (int)value;
}

void Graph::setEdge() {
    std::cin >> edge;
}

Graph::Graph(int n) : vertex(n) {
    FScount = 0;
    ENLcal();
    int e = 0;
    std::cout << "Please input e (0 ~ " << edgeNumLimit << ")\n=> "; 
    do {
        setEdge();
        if(edge > edgeNumLimit) {
            std::cout << "the number is too large, please retype.\n=> ";
        }
        if(edge < 0) {
            std::cout << "the number is too small, please retype.\n=> ";
        }
    }while ((edge > edgeNumLimit) || (edge < 0));
    AMmaker();
}

void Graph::AMmaker() {
    total_size = (vertex * (vertex - 1)) / 2;
    int *list = new int[total_size];

    std::random_device rd;
    std::mt19937 gen(rd());
    int limit = (1 << total_size) - 1;
    std::uniform_int_distribution<int> dist(0, limit);
    // reference by: https://learn.microsoft.com/en-us/cpp/standard-library/random?view=msvc-170

    int pos_count;
    int random;
    do {
        pos_count = 0;
        random = dist(gen);
        for (int i = 0; i < total_size; i++) {
            list[i] = (random >> (total_size - i - 1)) & 1;
            if (list[i] == 1) {
                pos_count++;
            }
        }
    } while (pos_count != edge);

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
    delete[] list;

    std::fstream file;
    file.open("matrix.csv", std::ios::out | std::ios::trunc);
    for (int i = 0; i < vertex; i++) {
        file << "," << i;
    }
    file << "\n";
    for(int i = 0; i < vertex; i++) {
        for(int j = 0; j < vertex; j++) {
            if(j == 0) {
                file << i;
            }
            file << "," << AdjMatrix[i][j]; 
        }
        file << ",\n";
    }
    ALmaker();
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
            std::cout << current->v;
            if (current->next != nullptr) {
                std::cout << " -> ";
            }
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

    FScount = 1;
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

    FScount = 2;
    tree(Barray);
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

void Graph::tree(fs *array) {
    for(int i = 0; i < vertex; i++) {
        if(array[i].pi != -1) {
            treeMatrix[array[i].pi][i] = 1;
        }
    }
    for (int i = 0; i < vertex; i++) {
        for (int j = 0; j < vertex; j++) {
            std::cout << treeMatrix[i][j] << " ";
        }
        std::cout << "\n";
    }

    std::fstream file;
    if (FScount == 1) {
        file.open("DFSMatrix.csv", std::ios::out | std::ios::trunc);
    }
    if (FScount == 2) {
        file.open("BFSMatrix.csv", std::ios::out | std::ios::trunc);
    }
    FSMatrix(&file);

    if (FScount == 1) {
        delete[] Darray;
    }
    if (FScount == 2) {
        delete[] Barray;
    }
}

void Graph::FSMatrix(std::fstream* file) {
    for (int i = 0; i < vertex; i++) {
        *file << "," << i;
    }
    *file << "\n";
    for (int i = 0; i < vertex; i++) {
        for (int j = 0; j < vertex; j++) {
            if (j == 0) {
                *file << i;
            }
            *file << "," << treeMatrix[i][j];
            treeMatrix[i][j] = 0;
        }
        *file << "\n";
    }
    file->close();
}


Graph::~Graph() {
    for (int i = 0; i < vertex; i++) {
        List* current = &AdjList[i];
        while (current != nullptr) {
            List* temp = current;
            current = current->next;
            //if (_CrtIsValidHeapPointer(temp)) { // ugly processing method
                delete temp;
            //}
            // if use command `g++ -o` on window terminal, can't use <crtdbg.h> and _CrtIsValidHeapPointer
            
            // what is _CrtIsValidHeapPointer()?, reference by: https://learn.microsoft.com/zh-tw/cpp/c-runtime-library/reference/crtisvalidheappointer?view=msvc-170
            // some information about _CrtIsValidHeapPointer(), reference by: https://stackoverflow.com/questions/64418624/why-do-i-get-crtisvalidheappointerblock-and-or-is-block-type-validheader-b
        }
    }
}