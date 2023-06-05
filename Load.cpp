#include "Load.h"

Mesh* Load::LoadObjFile(const string& path)
{
    ifstream ifile(path);
    if (!ifile.is_open())
    {
        cout << "File could not be opened" << endl;
        return nullptr;
    }

    static vector<Vertex*> p;
    static vector<glm::vec3> p_indices;

    // Read Obj file and store information of vertices and faces
    while (!ifile.eof())
    {
        string header;
        ifile >> header;;

        if (header == "v")
        {
            static float x, y, z = 0;
            ifile >> x >> y >> z;
            p.push_back(new Vertex(x, y, z));
        }
        else if (header == "f")
        {
            static glm::vec3 _pi{};
            ifile >> _pi.x >> _pi.y >> _pi.z;
            p_indices.push_back(_pi);
        }
        else if (header == "#" || header == "o")
        {
            // Placeholder for other cases
            continue;
        }

    }
    
    ifile.close();

    //	Print values onto screen
    cout << "Values in vertex list" << endl;
    //Load::PrintVertVec(p);
    cout << "Values in vertex index list" << endl;
    //Load::PrintVec(p_indices);

    //	Edge list
    static vector<Edge*> edgelist{};
    //  Face list
    static vector<Face*> facelist{};

    /*

                    v3   __
                /   /\  /\
               /   /  \   \
              /e3 /    \ e2\
            |/_  /	    \   \
                /________\
               v1   e1   v2
                --------->

    */

    // Iterate over all vertex list
    for (size_t i = 0; i < p_indices.size(); i++)
    {
        // Indexes start at 1 in OBJ
        unsigned int v1 = p_indices[i].x - 1;
        unsigned int v2 = p_indices[i].y - 1;
        unsigned int v3 = p_indices[i].z - 1;

        unsigned short dir1, dir2, dir3 = 0;

        Edge* e1 = nullptr;
        Edge* e2 = nullptr;
        Edge* e3 = nullptr;

        /*
        Currently it is implied that direction on create is always forward
        This may cause problems on connecting the next edge

                   \       /
             st_ccw \     / st_cw
                     \   /
                      \ /
                 ^     |st   |
                 |     |     |
               2 |     | e   | 1
                 |     |     |
                 |   ed|     v
                      / \
                     /   \
              ed_cw /     \ ed_ccw
                   /       \
        */

        if ((e1 = Edge::FindEdge(edgelist, p[v1], p[v2], &dir1)) == nullptr)
        {
            e1 = new Edge(p[v1], p[v2]);
            e1->ConnectVertexesToEdge();
            edgelist.push_back(e1);
            dir1 = 1;
        }
            
        if ((e2 = Edge::FindEdge(edgelist, p[v2], p[v3], &dir2)) == nullptr)
        {
            e2 = new Edge(p[v2], p[v3]);
            e2->ConnectVertexesToEdge();
            edgelist.push_back(e2);
            dir2 = Edge::GetDirection(e2, e1);
        }
            
        if ((e3 = Edge::FindEdge(edgelist, p[v3], p[v1], &dir3)) == nullptr)
        {
            e3 = new Edge(p[v3], p[v1]);
            e3->ConnectVertexesToEdge();
            edgelist.push_back(e3);
            dir3 = Edge::GetDirection(e3, e2);
        }


        Face* f = new Face(e1);

        // Connect all edges
        e1->ConnectEdges(dir1, e2, e3, f);
        e2->ConnectEdges(dir2, e3, e1, f);
        e3->ConnectEdges(dir3, e1, e2, f);

        facelist.push_back(f);

    }   // Main for loop end
    
    //  No edge should have null pointers
    cout << "-------------------------" << endl;
    Load::PrintEdgeVec(edgelist);
    
    auto m = new Mesh(p, edgelist, facelist);

    return m;
}


Mesh* Load::LoadOffFile(const string& path)
{
    return nullptr;
}


// --------------------------------- //
//          PRINT FUNCTIONS          //
// --------------------------------- //
void Load::PrintVec(const vector<glm::vec3>& vec)
{
    for (size_t i = 0; i < vec.size(); i++)
    {
        cout << vec[i].x << " " << vec[i].y << " " << vec[i].z << endl;
    }
}


void Load::PrintVertVec(const vector<Vertex*>& vec)
{
    for (size_t i = 0; i < vec.size(); i++) 
    { 
        vec[i]->ToString();
    }
}


void Load::PrintEdgeVec(const vector<Edge*>& vec)
{
    for (size_t i = 0; i < vec.size(); i++)
    {
        vec[i]->ToString();
    }
}
