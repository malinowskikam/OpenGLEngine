#include "include.hpp"

using namespace std;

ObjData* loadOBJ(string path)
{
    vector<glm::vec3> vertices;
    vector<glm::vec3> normals;
    vector<glm::vec2> uvs;
    vector<glm::highp_ivec3> indices;

    ifstream file(path);
    if(!file)
    {
        cout << "OBJParser: Can't open file: " << path << endl;
        exit(1);
    }

    for (string line; getline(file, line); )
    {
        vector<string> words = split(line,' ');

        string type = words[0];
        
        if(type == "v")
            vertices.push_back(glm::vec3(stof(words[1]),stof(words[2]),stof(words[3])));
        else if (type == "vt")
            uvs.push_back(glm::vec2(stof(words[1]),stof(words[2])));
        else if (type == "vn")
            normals.push_back(glm::vec3(stof(words[1]),stof(words[2]),stof(words[3])));
        else if (type == "f")
            for(int i=1;i<4;i++)
            {
                vector<string> face = split(words[i],'/');
                indices.push_back(glm::vec<3,int,glm::packed_highp>(stoi(face[0])-1,stoi(face[1])-1,stoi(face[2])-1));
            }

    }
    
    vector<glm::vec3> converted_vertices;
    vector<glm::vec3> converted_normals;
    vector<glm::vec2> converted_uvs;
    vector<int> converted_indices;

    map<tuple<int,int,int>,int> index_buffer;

    int next_index = 0;
    for(int i=0; i<indices.size();i++)
    {
        int new_index;
        tuple<int,int,int> key (indices[i][0],indices[i][1],indices[i][2]);
        map<tuple<int,int,int>,int>::iterator pos = index_buffer.find(key);
        if(pos != index_buffer.end())
        {
            new_index = pos->second;
        }
        else
        {
            new_index = next_index;
            index_buffer[key]=new_index;
            next_index++;

            converted_vertices.push_back(vertices[indices[i][0]]);
            converted_uvs.push_back(uvs[indices[i][1]]);
            converted_normals.push_back(normals[indices[i][2]]);

        }
        converted_indices.push_back(new_index);
    }

    ObjData *data = new ObjData;
    data->indexCount = converted_indices.size();
    data->vertexCount = converted_vertices.size();
    data->indices = converted_indices;
    data->vertices = converted_vertices;
    data->uvs = converted_uvs;
    data->normals = converted_normals;

    return data;
}
