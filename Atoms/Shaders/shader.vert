#version 330 core
layout (location = 0) in vec3 array_pos;
layout (location = 1) in vec3 array_normal;

out vec3 normal;
out vec3 frag_pos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	// position and normals are transformed in an inverted manner with respect to each other
    gl_Position = projection * view * model * vec4(array_pos.xyz, 1.0);
	normal = mat3(transpose(inverse(model))) * array_normal;
	frag_pos = vec3(model * vec4(array_pos.xyz, 1.0));
}