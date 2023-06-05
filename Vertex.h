#pragma once

#include <iostream>

#include <glm/glm.hpp>

class Edge;

using namespace std;

class Vertex
{
    public:
        //	Coordinates of a vertex
        float x, y, z;
        Edge* edge;
        
        Vertex(float x, float y, float z);
        void ToString();

        bool CompareVertex(const Vertex* v);
        inline bool SameVertex(const Vertex* v) { return this == v; }

        inline void ConnectToEdge(Edge* e) { this->edge = e; }
        inline glm::vec3 GetCoords() { return glm::vec3{ this->x, this->y, this->z }; }
};

