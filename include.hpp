#ifndef INCLUDE_SEEN
#define INCLUDE_SEEN

#include <GL/glew.h>
#include <GL/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <cstdlib>
#include <ctime>
#include <cctype>
#include <cmath>

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <thread>
#include <limits>
#include <chrono>

#define __CHECK_FOR_ERRORS 	{GLenum errCode; if ((errCode = glGetError()) != GL_NO_ERROR) printf("Error (%d): %s in file %s at line %d !\n", errCode, gluErrorString(errCode), __FILE__,  __LINE__);}
#include "const.hpp"

class Global;
class Scene;
class Object3D;
class Model;
class Texture;
class Program;
class GlyphSet;
class Material;

#include "common.hpp"
#include "objParser.hpp"

#include "object3d.hpp"
#include "scene.hpp"
#include "graphics.hpp"
#include "program.hpp"
#include "global.hpp"
#include "main.hpp"
#include "window.hpp"

#endif