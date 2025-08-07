#version 330 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in vec3 WorldPos[3];
in vec3 LightPos[3];

out vec3 normal;
out vec3 FragPos;
out vec3 lightPos;

vec3 GetNormal()
{
    vec3 a = WorldPos[2] - WorldPos[0];
    vec3 b = WorldPos[1] - WorldPos[0];
    return normalize(cross(a, b));
}

void main()
{
    gl_Position = gl_in[0].gl_Position;
    normal = GetNormal();
    FragPos = WorldPos[0];
    lightPos = LightPos[0];
    EmitVertex();

    gl_Position = gl_in[1].gl_Position;
    normal = GetNormal();
    FragPos = WorldPos[1];
    lightPos = LightPos[1];
    EmitVertex();

    gl_Position = gl_in[2].gl_Position;
    normal = GetNormal();
    FragPos = WorldPos[2];
    lightPos = LightPos[2];
    EmitVertex();
    
    EndPrimitive();
}