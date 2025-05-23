#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

#include "vbo.h"

using namespace std;

class VAO {
public:
    VAO(vector<shared_ptr<VBO>>& vbos, int length);

    virtual ~VAO();

    virtual GLuint createVAO(vector<shared_ptr<VBO>> &vbos);

    virtual GLuint getVAO();

    virtual int getLength();

    virtual void destroy();

    virtual void bind();

    virtual void unbind();

    virtual void draw();
protected:
    GLuint vao;//айди VAO
    int length;//кол-во вершин

    VAO();
};