#ifndef PROGRAM_SEEN
#define PROGRAM_SEEN

class Program
{
    public:
        GLuint id;

        Program(const char *vertexShader,const char *fragmentShader, const char *geometrySgader = NULL);
        void virtual setLight();
};

class PhongProgram : public Program
{
    public:
        PhongProgram();
};

class TextProgram : public Program
{
    public:
        TextProgram();
};
#endif
