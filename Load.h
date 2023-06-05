#pragma once

#include <string>
#include <iostream>
#include <fstream>

#include <glm/glm.hpp>

#include "Mesh.h"

using namespace std;

class Load
{
    public:
        static Mesh* LoadObjFile(const string& path);
        static Mesh* LoadOffFile(const string& path);
        static void PrintVec(const vector<glm::vec3>& vec);
        static void PrintVertVec(const vector<Vertex*>& vec);
        static void PrintEdgeVec(const vector<Edge*>& vec);
};

