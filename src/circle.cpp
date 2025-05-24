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
    vector<float> vertices(segments * 3 * 2), colors(segments * 3 * 3),  texCords(segments * 3 * 2);

    float deltaTheta = (PI::getPI() * 2) / segments;

    for (int i = 0; i < segments; i++) {
        int i_next = (i + 1) % segments;

	float dif_x = cos(deltaTheta * i);
	float dif_y = sin(deltaTheta * i);

	float next_dif_x = cos(deltaTheta * i_next);
	float next_dif_y = sin(deltaTheta * i_next);

	float this_x = dif_x * radius + x;
	float this_y = dif_y * radius + y;

	float next_x = next_dif_x * radius + x;
	float next_y = next_dif_y * radius + y;

	vertices[i * 3 * 2] = x;
	vertices[i * 3 * 2 + 1] = y;

	vertices[i * 3 * 2 + 2] = this_x;
	vertices[i * 3 * 2 + 3] = this_y;

	vertices[i * 3 * 2 + 4] = next_x;
	vertices[i * 3 * 2 + 5] = next_y;

	float tex_radius = 1 / max(abs(dif_x), abs(dif_y));
	float next_tex_radius = 1 / max(abs(next_dif_x), abs(next_dif_y));

	cout << tex_radius << " so: " <<  (deltaTheta * i * 180 / PI::getPI()) << " and: c:" << dif_x << " s:" << dif_y << endl;

	float tex_x = (dif_x * tex_radius + 1) / 2;
	float tex_y = 1 - (dif_y * tex_radius + 1) / 2;

	float next_tex_x = (next_dif_x * next_tex_radius + 1) / 2;
	float next_tex_y = 1 - (next_dif_y * next_tex_radius + 1) / 2;

	texCords[i * 3 * 2] = 0.5f;
	texCords[i * 3 * 2 + 1] = 0.5f;

	texCords[i * 3 * 2 + 2] = tex_x;
	texCords[i * 3 * 2 + 3] = tex_y;

	texCords[i * 3 * 2 + 4] = next_tex_x;
	texCords[i * 3 * 2 + 5] = next_tex_y;

	for (int j = 0; j < 3; j++) {
	    colors[i * 3 * 3 + j * 3] = red;
	    colors[i * 3 * 3 + j * 3 + 1] = green;
	    colors[i * 3 * 3 + j * 3 + 2] = blue;
	}
    }

    auto vertex_vbo = make_shared<VBO>(vertices, 2);
    auto color_vbo = make_shared<VBO>(colors, 3);
    auto texCord_vbo = make_shared<VBO>(texCords, 2);

    vector<shared_ptr<VBO>> vbos = {vertex_vbo, color_vbo, texCord_vbo};

    //super.vao
    VAO::vao = createVAO(vbos);
    VAO::length = segments * 3;
}