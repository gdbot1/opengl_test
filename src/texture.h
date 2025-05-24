#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;

class Texture {
public:
    Texture(const char* path);

    ~Texture();

    GLuint loadTexture(unsigned char* data);

    void bindSampler(int sampler);

    GLuint getTexture();

    int getWidth();

    int getHeight();

    int getCnt();

    void destroy();
private:
    int width, height, cnt;//texture metadata
    GLuint texture;//texture id
};