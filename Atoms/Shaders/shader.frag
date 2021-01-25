#version 330 core
in vec3 normal;
in vec3 frag_pos;

out vec4 frag_color;

uniform vec3 object_color;
uniform vec3 light_color;
uniform vec3 directional_light_direction;
uniform vec3 view_position;

vec3 compute_directional_light()
{
	float ambient_factor = 0.6;
	vec3 ambient = ambient_factor * light_color;

	vec3 norm = normalize(normal);
	float diffuse_factor = max(dot(normalize(directional_light_direction), norm), 0.0);
	vec3 diffuse = diffuse_factor * light_color;

	vec3 view_direction = normalize(view_position - frag_pos);
	vec3 reflection_direction = reflect(-normalize(directional_light_direction), norm);
	float specular_strength = 0.5;
	float specular_factor = pow(max(dot(view_direction, reflection_direction), 0.0), 32);
	vec3 specular = specular_strength * specular_factor * light_color;
	return ambient + diffuse + specular;
}

void main()
{
	vec4 result = vec4(compute_directional_light() * object_color, 1.0);

	frag_color = result;
}