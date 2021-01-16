#include "include.hpp"

extern Global *global;

Object3D::Object3D(glm::vec3 position,glm::vec3 rotation,glm::vec3 scale,Model *model,Texture *texture,Material* material)
{
    this->active = 1;
    this->flat = 0;
    this->trackingMode = TRACKING_NONE;

    this->position = position;
    this->rotation = rotation;
    this->scale = scale;

    this->texture = texture;
    this->model = model;
    this->material = material;
}

glm::mat4 Object3D::getModelMatrix()
{
    glm::mat4 modelMatrix;

    switch (this->trackingMode)
    {
    case TRACKING_CAMERA_XZ:
        modelMatrix = glm::inverse(glm::lookAt(
            this->position,
            glm::vec3(global->scene->cameraPosition.x,this->position.y,global->scene->cameraPosition.z),
            global->scene->cameraUp
        ));
        break;
    case TRACKING_CAMERA_XYZ:
        modelMatrix = glm::inverse(glm::lookAt(
            this->position,
            global->scene->cameraPosition,
            global->scene->cameraUp
        ));
        break;

    case TRACKING_CAMERA_PARALELL:
        modelMatrix = glm::inverse(glm::lookAt(
            this->position,
            this->position+global->scene->cameraFront,
            global->scene->cameraUp
        ));
        break;

    case TRACKING_CAMERA_PLANE_XZ:
        modelMatrix = glm::inverse(glm::lookAt(
            this->position,
            this->position-global->scene->cameraFront+glm::vec3(0.0,global->scene->cameraFront[1],0.0),
            global->scene->cameraUp
        ));
        break;
    
    default:
        modelMatrix = glm::mat4(1.0);
        modelMatrix = glm::translate(modelMatrix,position);
        modelMatrix = glm::rotate(modelMatrix,rotation[1],glm::vec3(0.0,1.0,0.0));
        modelMatrix = glm::rotate(modelMatrix,rotation[0],glm::vec3(1.0,0.0,0.0));
        modelMatrix = glm::rotate(modelMatrix,rotation[2],glm::vec3(0.0,0.0,1.0));
        break;
    }
    
    return glm::scale(modelMatrix,scale);
}

void Object3D::draw(Program* program)
{
    glBindVertexArray(this->model->id);
    
    glUseProgram(program->id);
    program->setLight();
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(this->texture->getTextureType(), this->texture->id);
    
    glm::mat4 model = this->getModelMatrix();
    glm::mat4 imodel = glm::inverse(model);
        
    glUniform1i(glGetUniformLocation(program->id, "modelTexture"), 0);
    
    glUniform1ui(glGetUniformLocation(program->id, "keyframe"),global->animationFrame);
    glUniform1i(glGetUniformLocation(program->id, "modelFlat"),this->flat);
    
    glm::vec3 ambient = this->material->ambientColor+global->sceneAmbience;
    glUniform3fv(glGetUniformLocation(program->id, "modelAlbedo"),1,glm::value_ptr(this->material->albedoColor));
    glUniform3fv(glGetUniformLocation(program->id, "modelAmbient"),1,glm::value_ptr(ambient));
    glUniform3fv(glGetUniformLocation(program->id, "modelDiffuse"),1,glm::value_ptr(this->material->diffuseColor));
    glUniform3fv(glGetUniformLocation(program->id, "modelSpecular"),1,glm::value_ptr(this->material->specularColor));
    glUniform1f(glGetUniformLocation(program->id, "modelRoughness"),this->material->roughness);
    glUniform1i(glGetUniformLocation(program->id, "envMode"),this->material->envMode);
    glUniform1f(glGetUniformLocation(program->id, "reflectColorPercentage"),this->material->reflectColorPercentage);
    glUniform1f(glGetUniformLocation(program->id, "refractColorPercentage"),this->material->refractColorPercentage);
    glUniform1f(glGetUniformLocation(program->id, "refractCoeff"),this->material->refractCoeff);
    
    glUniformMatrix4fv(glGetUniformLocation(program->id, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(program->id, "itmodel"), 1, GL_TRUE, glm::value_ptr(imodel));
    
    glDrawElements( GL_TRIANGLES, (this->model->indexCount)*3 , GL_UNSIGNED_INT, NULL );
}