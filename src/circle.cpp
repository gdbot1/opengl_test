#include "PI.h"

#include "circle.h"

using namespace std;

Circle::Circle(float x, float y, float radius, int segments, float red, float green, float blue) {
    this->x = x;
    this->y = y;
    this->radius = radius;
    this->segments = segments;
    this->red = red;
    this->green = green;
    this->blue = blue;

    //vbo
    vector<float> vertices(segments * 3 * 2), colors(segments * 3 * 3);
    //float vertices[segments * 3 * 2], colors[segments * 3 * 3];

    float deltaTheta = (PI::getPI() * 2) / segments;

    for (int i = 0; i < segments; i++) {
        int i_next = (i + 1) % segments;

	float this_x = cos(deltaTheta * i) * radius + x;
	float this_y = sin(deltaTheta * i) * radius + y;

	float next_x = cos(deltaTheta * i_next) * radius + x;
	float next_y = sin(deltaTheta * i_next) * radius + y;

	vertices[i * 3 * 2] = x;
	vertices[i * 3 * 2 + 1] = y;

	vertices[i * 3 * 2 + 2] = this_x;
	vertices[i * 3 * 2 + 3] = this_y;

	vertices[i * 3 * 2 + 4] = next_x;
	vertices[i * 3 * 2 + 5] = next_y;

	for (int j = 0; j < 3; j++) {
	    colors[i * 3 * 3 + j * 3] = red;
	    colors[i * 3 * 3 + j * 3 + 1] = green;
	    colors[i * 3 * 3 + j * 3 + 2] = blue;
	}
    }

    auto vertex_vbo = make_shared<VBO>(vertices, 2);
    auto color_vbo = make_shared<VBO>(colors, 3);

    vector<shared_ptr<VBO>> vbos = {vertex_vbo, color_vbo};

    //super.vao
    VAO::vao = createVAO(vbos);
    VAO::length = segments * 3;
}