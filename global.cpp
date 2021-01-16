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

    this->drawStart = 0.01f;
    this->drawEnd = 150.0f;
    this->cameraFov = 80.0f;

    this->sceneAmbience = glm::vec3(0.1f);

    this->flags = 0;

    this->scene = new Scene();
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
    const char *paths1[] = {
		"data/tex/space-skybox/space_rt.png",
		"data/tex/space-skybox/space_lf.png",
		"data/tex/space-skybox/space_up.png",
		"data/tex/space-skybox/space_dn.png",
		"data/tex/space-skybox/space_bk.png",
		"data/tex/space-skybox/space_ft.png",	
	};

	const char *paths2[] = {
		"data/tex/corona-skybox/corona_rt.png",
		"data/tex/corona-skybox/corona_lf.png",
		"data/tex/corona-skybox/corona_up.png",
		"data/tex/corona-skybox/corona_dn.png",
		"data/tex/corona-skybox/corona_bk.png",
		"data/tex/corona-skybox/corona_ft.png",	
	};

    this->programs[PROGRAM_PHONH] = new PhongProgram();
    this->programs[PROGRAM_TEXT] = new TextProgram();

    this->models[MODEL_CUBE] = new Model("data/obj/cube.obj");
    this->models[MODEL_SCREEN] = new Model("data/obj/screen.obj");
    this->models[MODEL_BOW] = new Model("data/obj/bow.obj");
    this->models[MODEL_CHERRY_TREE] = new Model("data/obj/cherrytree.obj");
    this->models[MODEL_CHERRY_TREE_BLOSSOM] = new Model("data/obj/cherrytreeblossom.obj");
    this->models[MODEL_ISLAND] = new Model("data/obj/island.obj");
    this->models[MODEL_LANTERN] = new Model("data/obj/lantern.obj");
    this->models[MODEL_TORII_GATE] = new Model("data/obj/toriigate.obj");

    this->textures[TEXTURE_CUBE_SPACE] = new CubeMapTexture(paths1);
    this->textures[TEXTURE_CUBE_CORONA] = new CubeMapTexture(paths2);
    this->textures[TEXTURE_UV_BOW] = new UVTexture("data/tex/bow.png");
    this->textures[TEXTURE_UV_CHERRY_TREE] = new UVTexture("data/tex/cherrytree.png");
    this->textures[TEXTURE_UV_CHERRY_TREE_BLOSSOM] = new UVTexture("data/tex/cherryblossom.png");
    this->textures[TEXTURE_UV_GRASS] = new UVTexture("data/tex/groundgrass.jpg");
    this->textures[TEXTURE_UV_LANTERN] = new UVTexture("data/tex/lantern.png");
    this->textures[TEXTURE_UV_TORII_GATE] = new UVTexture("data/tex/toriigate.png");

    this->materials[MATERIAL_DEFAULT] = new Material(MATERIAL_COLOR_UV,MATERIAL_ENV_NONE,glm::vec3(0.0f),glm::vec3(0.05f),glm::vec3(1.0f),glm::vec3(0.8f),32,0.01f,0.01f,1.0f);
}