#ifndef PROJ_AED2_GRAPH_H
#define PROJ_AED2_GRAPH_H

#include <vector>
#include <list>
#include <string>
#include <map>
#include "flight.h"
using namespace std;

class Graph{
    struct Edge{
        //aeroporto de destino
        string target;
        //weight neste caso é distância, é automaticamente calculada de cada vez que adicionamos um adjacente
        float distance;
        //códigos das companhias que fazem este voo
        vector<string> airlines;
    };

    struct Node{
        //todos os destinos possiveis
        vector<Edge> adj;
        //possivelmente nao vamos usar
        bool visited;
    };

    //size
    int n;
    //default true, porque os voos podem nao ter volta
    bool hasDir;
    //string é o código do aeroporto, Node é o node correspondente
    map<string, Node> nodes;

public:
    Graph(int nodes, bool dir = true);
    void addEdge(const Flight& f);
};

#endif