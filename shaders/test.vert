#version 330

layout(location = 0) in vec2 position;
layout(location = 1) in vec3 color;

out vec4 fragColor;

void main() {
    gl_Position = vec4(position.xy, 0, 1);
    fragColor = vec4(color.rgb, 1);
}