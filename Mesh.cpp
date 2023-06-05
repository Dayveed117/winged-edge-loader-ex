#include "Mesh.h"

Mesh::Mesh(vector<Vertex*> vertices, vector<Edge*> edges, vector<Face*> faces)
{
    this->vertices = vertices;
    this->edges = edges;
    this->faces = faces;
}
