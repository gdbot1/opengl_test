#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

using namespace std;

class VBO {
public:
    VBO(vector<float>& buffer, int size);

    ~VBO();

    GLuint createVBO (vector<float>& buffer);

    GLuint getVBO();
    int getSize();

    int getLength();

    void destroy();
private:
    GLuint vbo;//vbo id
    int size, length;//size - кол-во чисел на 1 вершину, length - кол-во вершин в бафере
};