#include "include.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stbi.h"

const int cubeMapTarget[] = {
    GL_TEXTURE_CUBE_MAP_POSITIVE_X,
	GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
	GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
	GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
	GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
	GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
};

Model::Model(const char *path)
{
    std::cout << "Loading Model: " << path << std::endl;
    glGenVertexArrays(1,&(this->id));
	
    ObjData *data = loadOBJ(path);

	this->indexCount = data->indexCount;

    setVertexArray((GLfloat*)&(data->vertices[0]),data->vertexCount);
	setNormalArray((GLfloat*)&(data->normals[0]),data->vertexCount);
    setIndexArray((GLuint*)&(data->indices[0]),data->indexCount);
    setUvArray((GLfloat*)&(data->uvs[0]),data->vertexCount);

    delete data;
}

void Model::setVertexArray(GLfloat *vertices, GLuint vertices_count)
{
    glBindVertexArray(this->id);
	glGenBuffers(1,&(this->vertexBuffer));

	glBindBuffer(GL_ARRAY_BUFFER,this->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat)*vertices_count*3,vertices,GL_STATIC_DRAW);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,NULL );
	glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

void Model::setIndexArray(GLuint *indices, GLuint indices_count)
{
    glBindVertexArray(this->id);
    glGenBuffers(1,&(this->indexBuffer));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,this->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(GLuint)*indices_count,indices,GL_STATIC_DRAW);

    glBindVertexArray(0);
}

void Model::setNormalArray(GLfloat *normals, GLuint normals_count)
{
    glBindVertexArray(this->id);
	glGenBuffers(1,&(this->normalBuffer));

	glBindBuffer(GL_ARRAY_BUFFER,this->normalBuffer);
	glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat)*normals_count*3,normals,GL_STATIC_DRAW);
	glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,0,NULL);
	glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void Model::setUvArray(GLfloat *uvs, GLuint uvs_count)
{
    glBindVertexArray(this->id);
	glGenBuffers(1,&(this->uvBuffer));

	glBindBuffer(GL_ARRAY_BUFFER,this->uvBuffer);
	glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat)*uvs_count*2,uvs,GL_STATIC_DRAW);
	glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,0,NULL);
	glEnableVertexAttribArray(2);

    glBindVertexArray(0);

}

Texture::Texture()
{
    glGenTextures(1, &(this->id));
}

int Texture::getTextureType()
{
    return 0;
}

UVTexture::UVTexture(const char *path,GLint repeatMode,GLint filterMode) : Texture()
{
    std::cout << "Loading UV Texture: " << path << std::endl;
    stbi_set_flip_vertically_on_load(1);
    glBindTexture(GL_TEXTURE_2D, this->id);

    unsigned char *textureData = stbi_load(path,&width,&height,&channels,0);

    if(textureData == NULL)
    {
        std::cout << "EXCEPTION: Cant load image: " << path << std::endl;
    }

    if(channels==3)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
    else if(channels==4)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
    else
    {
        std::cout << "Unsupported texture: " << path << std::endl;
    }

    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, repeatMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, repeatMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMode);

    stbi_image_free(textureData);
}

int UVTexture::getTextureType()
{
    return GL_TEXTURE_2D;
}

CubeMapTexture::CubeMapTexture(const char *paths[6],GLint repeatMode,GLint magFilterMode,GLint minFilterMode)
{
    std::cout << "Loading Cube Texture: " << std::endl <<
        "   " << paths[0] << std::endl <<
        "   " << paths[1] << std::endl <<
        "   " << paths[2] << std::endl <<
        "   " << paths[3] << std::endl <<
        "   " << paths[4] << std::endl <<
        "   " << paths[5] << std::endl;
        

    int width,height,channels;
    // stbi_set_flip_vertically_on_load(1);

    glBindTexture(GL_TEXTURE_CUBE_MAP, this->id);

    for (int i=0; i < 6; ++i)
	{
        unsigned char *textureData = stbi_load(paths[i],&width,&height,&channels,0);

        if(textureData == NULL)
        {
            std::cout << "EXCEPTION: Cant load image: " << paths[i] << std::endl;
        }

        if(channels==3)
            glTexImage2D(cubeMapTarget[i], 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
        else if(channels==4)
            glTexImage2D(cubeMapTarget[i], 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
        else
            std::cout << "Unsupported texture: " << paths[i] << std::endl;

        stbi_image_free(textureData);
    }
    
    glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, magFilterMode );
    glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, minFilterMode );
	glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, repeatMode );
	glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, repeatMode );
    glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, repeatMode );
	glGenerateMipmap( GL_TEXTURE_CUBE_MAP );
}

int CubeMapTexture::getTextureType()
{
    return GL_TEXTURE_CUBE_MAP;
}

Material::Material(
            GLint colorMode,
            GLint envMode,
            glm::vec3 albedoColor,
            glm::vec3 ambientColor,
            glm::vec3 diffuseColor,
            glm::vec3 specularColor,
            GLfloat roughness,
            GLfloat reflectColorPercentage,
            GLfloat refractColorPercentage,
            GLfloat refractCoeff) 
{
    this->colorMode = colorMode;
    this->envMode = envMode;
    this->albedoColor = albedoColor;
    this->ambientColor = ambientColor;
    this->diffuseColor = diffuseColor;
    this->specularColor = specularColor;
    this->roughness = roughness;
    this->reflectColorPercentage = reflectColorPercentage;
    this->refractColorPercentage = refractColorPercentage;
    this->refractCoeff = refractCoeff;
}

Material* Material::copy()
{
    return new Material(this->colorMode,this->envMode,this->albedoColor,this->ambientColor,
                        this->diffuseColor,this->specularColor,this->roughness,this->reflectColorPercentage,
                        this->refractColorPercentage,this->refractCoeff);
}
