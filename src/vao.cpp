#include "vao.h"

using namespace std;

VAO::VAO() {

}

VAO::VAO(vector<shared_ptr<VBO>>& vbos, int length) {
    this->vao = createVAO(vbos);
    this->length = length;

    cout << "length:" << length << endl;
}

VAO::~VAO() {
    destroy();
}

GLuint VAO::createVAO(vector<shared_ptr<VBO>> &vbos) {
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

GLuint VAO::getVAO() {
    return this->vao;
}

int VAO::getLength() {
    return this->length;
}

void VAO::destroy() {
    glDeleteVertexArrays(1, &this->vao);
}

void VAO::bind() {
    glBindVertexArray(this->vao);
}

void VAO::unbind() {
    glBindVertexArray(0);
}

void VAO::draw() {
    bind();

    glDrawArrays(GL_TRIANGLES, 0, this->length);
    
    unbind();
}