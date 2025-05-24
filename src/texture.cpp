#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "texture.h"

Texture::Texture(const char* path) {
    unsigned char* data = stbi_load(path, &width, &height, &cnt, 0);

    this->texture = loadTexture(data);
}

Texture::~Texture() {
    destroy();
}

GLuint Texture::loadTexture(unsigned char* data) {
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, cnt == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);

    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(data);

    return texture;
}


void Texture::bindSampler(int sampler) {
    glActiveTexture(GL_TEXTURE0 + sampler);

    glBindTexture(GL_TEXTURE_2D, texture);
}

GLuint Texture::getTexture() {
    return this->texture;
}

int Texture::getWidth() {
    return this->width;
}

int Texture::getHeight() {
    return this->height;
}

int Texture::getCnt() {
    return this->cnt;
}

void Texture::destroy() {
    glDeleteTextures(1, &this->texture);
}