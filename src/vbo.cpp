#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

using namespace std;

class VBO {
public:
    VBO(vector<float>& buffer, int size) {
	this->length = buffer.size() / size;
	this->size = size;
	this->vbo = createVBO(buffer);
    }

    ~VBO() {
	destroy();
    }

    GLuint createVBO (vector<float>& buffer) {
	GLuint vbo;

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(float), buffer.data(), GL_STATIC_DRAW);

	cout << "Created VBO: " << vbo << endl;

	return vbo;
    }

    GLuint getVBO() {
	return this->vbo;
    }

    int getSize() {
	return this->size;
    }

    int getLength() {
	return this->length;
    }

    void destroy() {
	glDeleteBuffers(1, &this->vbo);
    }
private:
    GLuint vbo;//vbo id
    int size, length;//size - кол-во чисел на 1 вершину, length - кол-во вершин в бафере
};