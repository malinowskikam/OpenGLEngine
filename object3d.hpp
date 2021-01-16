#ifndef OBJECT3D_SEEN
#define OBJECT3D_SEEN

class Object3D
{
    public:
        int flat;
        int active;
        int trackingMode;
        
        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 scale;

        Model *model;
        Texture *texture;   
        Material *material;     

        Object3D(glm::vec3 position,glm::vec3 rotation,glm::vec3 scale,Model *model,Texture *texture,Material *material);

        glm::mat4 getModelMatrix();
        void draw(Program* program);
};

#endif