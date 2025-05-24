#version 330

in vec4 fragColor;
in vec2 fragTexCord;

uniform sampler2D tex;

out vec4 exitColor;

void main() {
    exitColor = fragColor * texture(tex, fragTexCord);
}