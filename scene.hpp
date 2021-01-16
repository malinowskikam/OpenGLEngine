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

        Scene(int windowWidth,int windowHeight, const char *path);
        void updateLookingAngle();

        glm::mat4 getViewMatrix();
        glm::mat4 getProjectionMatrix();

        void updateCameraPosition();
};

#endif