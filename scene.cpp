#include "include.hpp"

extern Global *global;

Scene::Scene()
{
    this->cameraRotation = glm::vec3(0.0f,-(M_PI/2.0),0.0f);//pitch, yaw, roll
    this->cameraPosition = glm::vec3(0.0f,0.0f,0.0f);

    this->cameraUp = glm::vec3(0.0,1.0,0.0);
}

void Scene::updateLookingAngle()
{
    glm::vec3 direction;
    direction.x = cos(cameraRotation[1]) * cos(cameraRotation[0]);
    direction.y = sin(cameraRotation[0]);
    direction.z = sin(cameraRotation[1]) * cos(cameraRotation[0]);
    
    this->cameraFront = glm::normalize(direction);
    this->cameraFrontXZ = glm::normalize(glm::vec3(cameraFront.x,0.0,cameraFront.z));
	this->cameraLocalX = glm::normalize(glm::cross(cameraFront,this->cameraUp));

    this->projectionMatrix = glm::perspective(glm::radians(global->cameraFov), global->windowWidth/(float)(global->windowHeight), global->drawStart, global->drawEnd);
    this->viewMatrix = glm::lookAt(cameraPosition,cameraPosition+cameraFront,cameraUp);
    this->projViewMatrix = this->projectionMatrix * this->viewMatrix;
}

void updateCameraPosition()
{
    
}