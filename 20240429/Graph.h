#ifndef GRAPH_H
#define GRAPH_H

#include <fstream>
class Graph {
private:
    struct List
    {
        int v;
        List *next;
    };

    struct fs
    {
        int color;
        int d;
        int pi;
    };

    int vertex;
    int edge;
    int edgeNumLimit;

    int total_size;

    fs* Darray = nullptr;
    fs* Barray = nullptr;
    int* list = nullptr;

    void ENLcal();
    void setEdge();

    int AdjMatrix[256][256] = { 0 };
    int treeMatrix[256][256] = { 0 };
    List AdjList[256];

    void AMmaker();
    void ALmaker();

    void DFSVisit(fs*, int, int&);
    void BFSVisit(fs*, int, int&);
    void tree(fs*);

    int FScount;
    void FSMatrix(std::fstream*);
public:
    Graph(int = 0);

    void AMprinter();
    void ALprinter();
    
    void DFS();

    void BFS();

    ~Graph();
};

#endif