#ifndef GRAPH_H
#define GRAPH_H

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

    int AdjMatrix[64][64] = { 0 };
    List AdjList[64];

    void AMmaker();
    void ALmaker();

    void DFSVisit(fs*, int, int&);
    void BFSVisit(fs*, int, int&);
    void tree(fs*);
public:
    Graph(int = 0);

    void AMprinter();
    void ALprinter();
    
    void DFS();

    void BFS();

    ~Graph();
};

#endif