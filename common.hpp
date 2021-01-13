#ifndef MATH_SEEN
#define MATH_SEEN

float frand(float min,float max);
float logisticCurve(float asimptote, float midPoint, float scale, float x);
glm::vec3 rotateEulersAngles(glm::vec3 rotation, glm::vec3 axis, float angles);
float sign (glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);
std::vector<std::string> split (const std::string &s, char delim);
unsigned long getFileLength(std::ifstream& file);
GLchar * LoadShaderFile(const char* filename);
void CheckForErrors_Shader(GLuint shader);
void CheckForErrors_Program(GLuint program, GLenum mode);
GLuint LoadShader( GLuint MODE, const char *filename  );
void LinkAndValidateProgram(GLuint program);

#endif