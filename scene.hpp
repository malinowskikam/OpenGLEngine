#ifndef SCENE_SEEN
#define SCENE_SEEN

class Scene
{
    public:
        glm::vec3 cameraPosition;
        glm::vec3 cameraRotation;

        glm::vec3 cameraFront;
        glm::vec3 cameraUp;
        glm::vec3 cameraFrontXZ;
	    glm::vec3 cameraLocalX;

        glm::mat4 projectionMatrix;
        glm::mat4 viewMatrix;
        glm::mat4 projViewMatrix;

        Scene();
        void updateLookingAngle();
        void updateCameraPosition();
};

#endif