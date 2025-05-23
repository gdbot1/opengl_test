#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

#include "vbo.cpp"

using namespace std;

class VAO {
public:
    VAO(const vector<shared_ptr<VBO>>& vbos, int length) {
	this->vao = createVAO(vbos);
	this->length = length;

	cout << "length:" << length << endl;
    }

    ~VAO() {
	destroy();
    }

    GLuint createVAO(const vector<shared_ptr<VBO>> &vbos) {
        GLuint vao;
        glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	for (int i = 0; i < vbos.size(); i++) {
	    glBindBuffer(GL_ARRAY_BUFFER, vbos[i]->getVBO());
	    glVertexAttribPointer(i, vbos[i]->getSize(), GL_FLOAT, GL_FALSE, vbos[i]->getSize() * sizeof(float), nullptr);
	    glEnableVertexAttribArray(i);
	}
	
	glBindVertexArray(0);

	cout << "Created VAO: " << vao << endl; 

	return vao;
    }

    GLuint getVAO() {
	return this->vao;
    }

    int getLength() {
	return this->length;
    }

    void destroy() {
	glDeleteVertexArrays(1, &this->vao);
    }

    void bind() {
	glBindVertexArray(this->vao);
    }

    void unbind() {
	glBindVertexArray(0);
    }

    void draw() {
	bind();

	glDrawArrays(GL_TRIANGLES, 0, this->length);
	
	unbind();
    }
protected:
    GLuint vao;//айди VAO
    int length;//кол-во вершин
};