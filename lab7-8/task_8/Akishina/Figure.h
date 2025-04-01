#pragma once
#include <glm\glm.hpp>
#include <glad\glad.h>
#include <vector>

using namespace glm;

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct vertex {
	vec3 position;
	vec3 normal;
};

class mesh {
public:
	GLuint vertexArray;
	std::vector<vertex> vertices;
	std::vector<GLuint> indices;
	Material material;
	mesh(std::vector<vertex> verts, std::vector<GLuint> inds, Material mat) {
		vertices = verts;
		material = mat;
		indices = inds;
		setupMesh();
	}
private:
	GLuint vertexBuffer;
	GLuint elementBuffer;

	void setupMesh() {
		glGenVertexArrays(1, &vertexArray);
		glGenBuffers(1, &vertexBuffer);
		glGenBuffers(1, &elementBuffer);
		glBindVertexArray(vertexArray);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertex), &vertices[0], GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)offsetof(vertex, normal));
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
};

class model {
public:
	std::vector<mesh> figure;
	mat4 modelM;
	model(std::vector<mesh> fig, mat4 mat) {
		figure = fig;
		modelM = mat;
	}
};