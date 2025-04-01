#version 330 core
struct Light {
 vec3 ambient;
 vec3 diffuse;
 vec3 specular;
};

struct Material {
vec3 ambient;
vec3 diffuse;
vec3 specular;
float shininess;
};

in vec3 fragPos;
in vec3 fragNorm;

out vec4 color;

uniform Material material;
uniform Light light1;
uniform Light light2;
uniform vec3 light1Pos;
uniform vec3 light2Pos;
uniform vec3 viewPos;

void main() {
 vec3 norm = normalize(fragNorm);
 vec3 lightDir = normalize(light1Pos - fragPos);
 float cosTheta = max(dot(norm, lightDir), 0.0);

 float powOfCos;
 if (cosTheta > 0.0) {
   vec3 viewDir = normalize(viewPos - fragPos);
   vec3 lightDirR = reflect(-lightDir, norm);
   powOfCos = pow(max(dot(viewDir, lightDirR), 0.0), material.shininess);
 }
 else
 powOfCos = 0.0;

 vec3 ambient = light1.ambient * material.ambient;
 vec3 diffuse = light1.diffuse * cosTheta * material.diffuse;
 vec3 specular = light1.specular * powOfCos * material.specular;

 vec3 result = ambient + diffuse + specular;

 norm = normalize(fragNorm);
 lightDir = normalize(light2Pos - fragPos);
 cosTheta = max(dot(norm, lightDir), 0.0);

 if (cosTheta > 0.0) {
   vec3 viewDir = normalize(viewPos - fragPos);
   vec3 lightDirR = reflect(-lightDir, norm);
   powOfCos = pow(max(dot(viewDir, lightDirR), 0.0), material.shininess);
 }
 else
   powOfCos = 0.0;

 ambient = light2.ambient * material.ambient;
 diffuse = light2.diffuse * cosTheta * material.diffuse;
 specular = light2.specular * powOfCos * material.specular;

 result += ambient + diffuse + specular;

 color = vec4(result, 1.0);
}