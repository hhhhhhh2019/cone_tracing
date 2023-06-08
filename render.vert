#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) uniform mat4 projection;
layout (location = 2) uniform mat4 camera_matrix;

out vec3 vertex_pos;

void main() {
	gl_Position = vec4(position, 1.0) * camera_matrix * projection;

	vertex_pos = position;
}
