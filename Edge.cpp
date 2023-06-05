#include "Edge.h"

int Edge::count = 0;

Edge::Edge(Vertex* st, Vertex* ed)
{
    this->st = st;
    this->ed = ed;

    this->st_ccw = nullptr;
    this->st_cw = nullptr;
    this->ed_ccw = nullptr;
    this->ed_cw = nullptr;

    this->fl = nullptr;
    this->fr = nullptr;

    Edge::count++;
    this->id = count;
}


bool Edge::CompareEdge(const Vertex* v1, const Vertex* v2)
{
    return
        (
            this->st->CompareVertex(v1) &&
            this->ed->CompareVertex(v2)
        )
            ||
        (
            this->st->CompareVertex(v2) &&
            this->ed->CompareVertex(v1)
        );
}


bool Edge::CompareEdge(const Vertex* v1, const Vertex* v2, unsigned short* dir)
{
    /*
    1 - Same Direction when edge was created
    2 - Reverse Direction from when edge was created
    */

    //	Original direction
    if (this->st->SameVertex(v1) && this->ed->SameVertex(v2))
    {
        *dir = 1;
        return true;
    }

    //	Reverse direction
    if (this->st->SameVertex(v2) && this->ed->SameVertex(v1))
    {
        *dir = 2;
        return true;
    }

    return false;
}


Edge* Edge::FindEdge(const vector<Edge*> vec, const Vertex* v1, const Vertex* v2, unsigned short* dir)
{
    for (Edge* e : vec)
    {
        if (e->CompareEdge(v1, v2, dir))
            return e;
    }

    return nullptr;
}


void Edge::ConnectEdges(const unsigned short dir, Edge* prox, Edge* ant, Face* f)
{
    switch (dir)
    {
        case 1:
            this->Set_ed_ccw(prox);
            this->Set_st_cw(ant);
            this->Set_fl(f);
            /*
            if (this->fl == nullptr)
                this->Set_fl(f);
            else
                this->Set_fr(f);
            */

            break;
    
        case 2:
            this->Set_st_ccw(prox);
            this->Set_ed_cw(ant);
            this->Set_fr(f);
            /*
            if (this->fr == nullptr)
                this->Set_fr(f);
            else
                this->Set_fl(f);
            */

            break;
    
        default:
            break;
    }
}


unsigned short Edge::GetDirection(const Edge* cur, const Edge* ant)
{
    /*
    1 - Same Direction when edge was created
    2 - Reverse Direction from when edge was created
    */

    if (ant->ed->SameVertex(cur->st) || ant->st->SameVertex(cur->st))
        return 1;
    else if (ant->ed->SameVertex(cur->ed) || ant->st->SameVertex(cur->ed))
        return 2;
    else
        return 0;
}


vector<Vertex*> Edge::GetUniqueVertexes(const Edge* cur, const Edge* ant, const Edge* next)
{
    // 1 1 1
    // 1 1 2
    // 1 2 1
    // 1 2 2
    // 2 1 1
    // 2 1 2
    // 2 2 1
    // 2 2 2
    unsigned short dir2 = Edge::GetDirection(next, cur);
    unsigned short dir3 = Edge::GetDirection(ant, cur);

    // Fix one of the vertices
    vector<Vertex*> tmp = { cur->st };

    if (dir2 == 1)
    {
        tmp.push_back(next->st);

        if (dir3 == 1)
            tmp.push_back(ant->st);
        else
            tmp.push_back(ant->ed);
    }
    else
    {
        tmp.push_back(next->ed);
        if (dir3 == 1)
            tmp.push_back(ant->ed);
        else
            tmp.push_back(ant->st);
    }

    return tmp;
}


void Edge::ToString()
{
    cout << "Edge " << this->id << endl
        << "  rev next is Edge " << this->st_ccw->id << endl
        << "  og ant is Edge " << this->st_cw->id << endl
        << "  og next is Edge " << this->ed_ccw->id << endl
        << "  rev ant is Edge " << this->ed_cw->id << endl
        << "  face left is Face " << this->fl->id << endl
        << "  face right is Face " << this->fr->id << endl;
}

