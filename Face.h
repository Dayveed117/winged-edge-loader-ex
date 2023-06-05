#pragma once

#include <vector>

class Edge;
class Vertex;

using namespace std;

class Face
{
    private:
        static int count;

    public:
        int id;

        Edge* edge;
        Face(Edge* edge);

}; 
