#version 330 core

out vec4 FragColor;
in vec3 customColor;

void main()
{ 
    FragColor = vec4(customColor, 1.0); 
}