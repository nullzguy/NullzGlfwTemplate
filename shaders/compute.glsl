#version 410 core

out uvec4 FragColor;

uniform float dt;
uniform usampler2D simTexA;

// Main
void main() {
    ivec2 crd = ivec2(gl_FragCoord.xy);

    FragColor = texelFetch(simTexA, crd, 0);
}