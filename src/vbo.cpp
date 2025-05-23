#include "vbo.h"

using namespace std;

VBO::VBO(vector<float>& buffer, int size) {
    this->length = buffer.size() / size;
    this->size = size;
    this->vbo = createVBO(buffer);
}

VBO::~VBO() {
    destroy();
}

GLuint VBO::createVBO (vector<float>& buffer) {
    GLuint vbo;

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(float), buffer.data(), GL_STATIC_DRAW);

    cout << "Created VBO: " << vbo << endl;

    return vbo;
}

GLuint VBO::getVBO() {
    return this->vbo;
}

int VBO::getSize() {
    return this->size;
}

int VBO::getLength() {
    return this->length;
}

void VBO::destroy() {
    glDeleteBuffers(1, &this->vbo);
}