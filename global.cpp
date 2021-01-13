#include "include.hpp"

Global* _singleton = NULL;

Global::Global()
{
    this->drawFrame = 0;
    this->animationFrame = 0;
    this->targetFps = 60.0;
    this->calculatedFps = 0.0;

	this->windowWidth = 1366;
	this->windowHeight = 768;

    this->flags = 0;
}

Global* getGlobal()
{
    if(_singleton==NULL)
        _singleton = new Global();
    return _singleton;
}

unsigned int Global::getFlag(unsigned int mask)
{
    return this->flags & mask;
}

void Global::setFlagOn(unsigned int mask)
{
    this->flags |= mask;
}

void Global::setFlagOff(unsigned int mask)
{
    this->flags &= ~mask;
}

void Global::flipFlag(unsigned int mask)
{
    this->flags ^= mask;
}

void Global::loadAssets()
{
    this->programs[PROGRAM_PHONH] = new PhongProgram();
    this->programs[PROGRAM_TEXT] = new TextProgram();
}