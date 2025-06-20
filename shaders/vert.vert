#version 450

layout(location = 0) out vec3 fragColor;

vec2 positions[5] = vec2[](
    vec2(-0.5, -0.5), // bottom left
    vec2(0.5, -0.5),  // bottom right
    vec2(-0.5, 0.5),  // top left
    vec2(0.5, 0.5),   // top right
    vec2(0.7, 0.7) // Hz
);

vec3 colors[5] = vec3[](
    vec3(1.0, 0.0, 0.0),  // Red
    vec3(0.0, 1.0, 0.0),  // Green
    vec3(0.0, 0.0, 1.0),  // Blue
    vec3(1.0, 1.0, 0.0),  // Yellow
    vec3(0.5, 0.5, 0.2)   // Hz
);

void main() {
    gl_Position = vec4(positions[gl_VertexIndex], 0.0, 1.0);
    fragColor = colors[gl_VertexIndex];
} 