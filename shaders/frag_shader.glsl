#version 330 core

in vec3 normal;
in vec3 FragPos;

out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;

void main()
{

    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // Inverse square law
    float intensity = 3.0/(length(lightPos - FragPos)*length(lightPos - FragPos));

    vec3 result = intensity * (ambient + diffuse) * objectColor; 
    FragColor = vec4(result, 1.0);
}