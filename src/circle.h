#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <numbers>

#include "vao.h"

using namespace std;

class Circle : public VAO {
public:
    Circle(float x, float y, float radius, int segments, float red, float green, float blue);
protected:
    float x, y, radius, red, green, blue;
    int segments;
};