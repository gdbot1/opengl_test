#version 330

layout(location = 0) in vec2 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 texCord;

out vec2 fragTexCord;
out vec4 fragColor;

void main() {
    gl_Position = vec4(position.xy, 0, 1);
    fragTexCord = texCord;
    fragColor = vec4(color.rgb, 1);
}