#ifndef SEEN_GLOBAL
#define SEEN_GLOBAL

class Global{
    public:
        unsigned int drawFrame;
        unsigned int animationFrame;
        float targetFps;
        float calculatedFps;
        unsigned int windowWidth;
        unsigned int windowHeight;

        unsigned int flags;

        float fogStart;
        float fogStrength;

        std::map<int,Model*> models;
        std::map<int,Texture*> textures;
        std::map<int,Program*> programs;
        std::map<int,GlyphSet*> fonts;

        GLFWwindow* window;

        Global();
        void loadAssets();
        unsigned int getFlag(unsigned int mask);
        void setFlagOn(unsigned int mask);
        void setFlagOff(unsigned int mask);
        void flipFlag(unsigned int mask);
};

Global* getGlobal();

#endif