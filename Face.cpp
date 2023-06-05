#include "Face.h"

int Face::count = 0;

Face::Face(Edge* edge)
{
    this->edge = edge;
    
    Face::count++;
    this->id = count;
}
