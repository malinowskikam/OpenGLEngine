#ifndef MODEL_SEEN
#define MODEL_SEEN

class Model
{
    protected:
        GLuint vertexBuffer,indexBuffer,normalBuffer,uvBuffer;
        void setVertexArray(GLfloat *vertices, GLuint vertices_count);
        void setIndexArray(GLuint *indices, GLuint indices_count);
        void setNormalArray(GLfloat *normals, GLuint normals_count);
        void setUvArray(GLfloat *uvs, GLuint uvs_count);

    public:
        GLuint id;
        GLuint indexCount;
        Model(const char *path);
};

class Texture
{
    protected:
    public:
        GLuint id;
        int width,height,channels;
        Texture();
        virtual int getTextureType();
};

class UVTexture : public Texture
{
    public:
        UVTexture(const char *path,GLint repeatMode=GL_REPEAT,GLint filterMode=GL_LINEAR);
        int getTextureType();
};

class CubeMapTexture : public Texture
{
    public:
        CubeMapTexture(const char *paths[6],GLint repeatMode=GL_REPEAT,GLint magFilterMode=GL_NEAREST,GLint minFilterMode=GL_NEAREST_MIPMAP_LINEAR);
        int getTextureType();
};
#endif