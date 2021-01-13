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

        GLFWwindow* window;

        Global();
        void loadData();
        unsigned int getFlag(unsigned int mask);
        void setFlagOn(unsigned int mask);
        void setFlagOff(unsigned int mask);
        void flipFlag(unsigned int mask);
};

Global* getGlobal();

#endif