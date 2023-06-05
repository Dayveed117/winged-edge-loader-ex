#include "Vertex.h"

Vertex::Vertex(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;

    this->edge = nullptr;
}

void Vertex::ToString()
{
    cout << "Vertex :" << endl
        << "  x = " << this->x << endl
        << "  y = " << this->y << endl
        << "  z = " << this->z << endl;
}

bool Vertex::CompareVertex(const Vertex* v)
{
    return
        this->x == v->x && 
        this->y == v->y && 
        this->z == v->z;
}
