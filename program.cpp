#include "include.hpp"

extern Global *global;

Program::Program(const char *vertexShader,const char *fragmentShader,const char *geometryShader)
{
    std::cout << "Loading Program: " << vertexShader << " " << fragmentShader;
    if(geometryShader!=NULL) std::cout << " " << geometryShader;
    std::cout << std::endl;
    
    id = glCreateProgram();

    glAttachShader( id, LoadShader(GL_VERTEX_SHADER, vertexShader));
    glAttachShader( id, LoadShader(GL_FRAGMENT_SHADER,fragmentShader));
    if(geometryShader!=NULL) glAttachShader( id, LoadShader(GL_GEOMETRY_SHADER,geometryShader));    

    LinkAndValidateProgram(id);
}

void Program::setLight()
{
    
}

PhongProgram::PhongProgram() : Program("shaders/vertex/uniformTransform.glsl","shaders/fragment/phong.glsl")
{

}

TextProgram::TextProgram() : Program("shaders/vertex/uniformTransform.glsl","shaders/fragment/text.glsl")
{

}