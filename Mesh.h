#pragma once

#include <vector>

#include "Vertex.h"
#include "Edge.h"
#include "Face.h"

using namespace std;

class Mesh
{
    public:
        vector<Vertex*> vertices;
        vector<Edge*> edges;
        vector<Face*> faces;

        inline int GetVerticesSize() { return vertices.size(); }
        inline int GetEdgesSize() { return edges.size(); }
        inline int GetFacesSize() { return faces.size(); }

        Mesh(vector<Vertex*> vertices, vector<Edge*> edges, vector<Face*> faces);
};
