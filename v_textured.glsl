#version 330 core

// Zmienne jednorodne
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;

// Atrybuty
layout (location = 0) in vec4 vertex;       // Wspó³rzêdne wierzcho³ka w przestrzeni modelu
layout (location = 1) in vec2 texCoord;     // Wspó³rzêdne tekstur

// Zmienne interpolowane
out vec2 fragTexCoord;

void main(void) {
    gl_Position = P * V * M * vertex;
    fragTexCoord = texCoord;
}
