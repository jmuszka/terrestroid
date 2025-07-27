#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec3 customColor;
out vec2 TexCoord;

void main()
{ 
    gl_Position = vec4(aPos, 1.0); 
    customColor = vec3(1.0, 1.0, 1.0); 
    TexCoord = aTexCoord;
}
