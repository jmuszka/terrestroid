#include <GL/glew.h>

class GLVertex 
{
private:
    GLfloat x;
    GLfloat y;
    GLfloat z;
public:
    GLVertex(GLfloat x0, GLfloat y0, GLfloat z0);
    GLfloat getX();
    GLfloat getY();
    GLfloat getZ();
    void setX(GLfloat x0);
    void setY(GLfloat y0);
    void setZ(GLfloat z0);
};