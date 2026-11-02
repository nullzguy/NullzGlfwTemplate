#version 410 core

out vec4 FragColor;

uniform vec2 res;
uniform usampler2D computeTex;

// Main
void main() {
    vec2 uv = 2.0*(gl_FragCoord.xy / res - vec2(0.5));
    uv.x *= res.x / res.y;

    vec2 texUV = gl_FragCoord.xy / res;
    vec4 sim = vec4(texture(computeTex, texUV));

    FragColor = vec4(uv, 0.0, 1.0) + sim;
}