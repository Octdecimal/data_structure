#include "Graph.h"
#include <iostream>

int main() {
    int n, e;
    while (true) {
        std::cout << "Please input n (0 ~ 64)\n=> ";
        std::cin >> n;
        Graph* G = new Graph(n);
        std::cout << "-------------------------\n";
        G->AMprinter();
        std::cout << "-------------------------\n";
        G->ALprinter();
        std::cout << "-------------------------\n";
        G->DFS();
        std::cout << "-------------------------\n";
        G->BFS();

        G->~Graph();
        delete G;
        std::cout << "#########################\n";
    }
    return 0;
}