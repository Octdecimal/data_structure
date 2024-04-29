#include "Graph.h"
#include <iostream>

int main() {
    int n;
    while (true) {
        std::cout << "Please input n (1 ~ 256)\n=> ";
        std::cin >> n;
        if (n < 1 || n > 256) {
            continue;
        }
        Graph* G = new Graph(n);
        std::cout << "-------------------------\nAdjMatrix:\n";
        G->AMprinter();
        std::cout << "-------------------------\nAdjList:\n";
        G->ALprinter();
        std::cout << "-------------------------\nDFS:\n";
        G->DFS();
        std::cout << "-------------------------\nBFS:\n";
        G->BFS();

        delete G;
        std::cout << "#########################\n";
    }
    return 0;
}