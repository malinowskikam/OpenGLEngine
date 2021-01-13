#ifndef OBJPARSER_SEEN
#define OBJPARSER_SEEN

typedef struct _objData
{
    int indexCount;
    int vertexCount;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> uvs;
    std::vector<int> indices;
} ObjData;

ObjData* loadOBJ(std::string path);

#endif