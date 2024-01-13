#version 430
layout(location = 0) in vec3 vertex;
layout(location = 1) in vec3 normal;

out vec3 v_position;
out vec3 v_normal;

uniform mat4 mvp_matrix;
uniform mat3 normal_matrix;

void main() {
    v_position = vertex.xyz;
    v_normal = normal;//normal_matrix * normal;

    // Calculate vertex position in screen space
    gl_Position = mvp_matrix * vec4(vertex,1.);
}
