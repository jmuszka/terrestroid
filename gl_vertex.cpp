#include "gl_vertex.h"

GLVertex::GLVertex(GLfloat x0, GLfloat y0, GLfloat z0)
{
    // Default values
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;

    // If point lies within OpenGL coordinate system [-1, 1], add it; otherwise, keep default
    if (-1.0 <= x0 && x0 <= 1.0) x = x0;
    if (-1.0 <= y0 && y0 <= 1.0) y = y0;
    if (-1.0 <= z0 && z0 <= 1.0) z = z0;
}

GLfloat GLVertex::getX()
{
    return x;
}

GLfloat GLVertex::getY()
{
    return y;
}

GLfloat GLVertex::getZ()
{
    return z;
}

void GLVertex::setX(GLfloat x0)
{
    x = x0;
}

void GLVertex::setY(GLfloat y0)
{
    y = y0;
}

void GLVertex::setZ(GLfloat z0)
{
    z = z0;
}