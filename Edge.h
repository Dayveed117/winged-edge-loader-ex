#pragma once

#include <vector>

#include "Vertex.h"
#include "Face.h"

using namespace std;

class Edge
{
    private:
        static int count;

    public:
        int id;
        Edge(Vertex* st, Vertex* ed);

        //	Direction st -> ed
        Vertex* st;
        Vertex* ed;
        inline void SwapStEd() { auto tmp = this->ed; this->ed = st; this->st = tmp; }

        //	From st -> ed, left and right faces
        Face* fl;
        Face* fr;
        inline void Set_fl(Face* f) { if (this->fl == nullptr) this->fl = f; };
        inline void Set_fr(Face* f) { if (this->fr == nullptr) this->fr = f; };


        Edge* st_ccw;	// go clockwise from start
        Edge* st_cw;	// go counterclockwise from start
        Edge* ed_ccw;	// go counterclockwise from end
        Edge* ed_cw;	// go clockwise from end
        inline void Set_st_ccw(Edge* e) { if (this->st_ccw == nullptr) this->st_ccw = e; }
        inline void Set_st_cw (Edge* e) { if (this->st_cw  == nullptr) this->st_cw  = e; }
        inline void Set_ed_ccw(Edge* e) { if (this->ed_ccw == nullptr) this->ed_ccw = e; }
        inline void Set_ed_cw (Edge* e) { if (this->ed_cw  == nullptr) this->ed_cw  = e; }

        inline void ConnectVertexesToEdge() { this->st->ConnectToEdge(this); this->ed->ConnectToEdge(this); }
        void ConnectEdges(const unsigned short dir, Edge* prox, Edge* ant, Face* f);
        
        bool CompareEdge(const Vertex* v1, const Vertex* v2);
        bool CompareEdge(const Vertex* v1, const Vertex* v2, unsigned short* dir);

        static Edge* FindEdge(const vector<Edge*> vec, const Vertex* v1, const Vertex* v2, unsigned short* dir);
        
        static unsigned short GetDirection(const Edge* cur, const Edge* ant);
        static vector<Vertex*> GetUniqueVertexes(const Edge* cur, const Edge* ant, const Edge* next);

        void ToString();
};

