#version 330 core
in vec3 normal;
in vec3 fragPos;
in vec2 texCoords;

out vec4 fragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 light_position;
uniform vec3 viewPos;

uniform sampler2D texture1;

void main()
{
	float ambientFactor = 0.1;
	vec3 ambient = ambientFactor * lightColor;

	vec3 norm = normalize(normal);
	vec3 lightDirection = normalize(lightPos - fragPos);
	float diffuseFactor = max(dot(lightDirection, norm), 0.0);
	vec3 diffuse = diffuseFactor * lightColor;


	float specularStrength = 0.5;
	vec3 viewDirection = normalize(viewPos - fragPos);
	vec3 reflectionDirection = reflect(-lightDirection, norm);
	float specularFactor = pow(max(dot(-viewDirection, reflectionDirection), 0.0), 32);
	vec3 specular = specularStrength * specularFactor * lightColor;

	vec4 result =  vec4((ambient + diffuse + specular) * objectColor, 1.0);
    fragColor = texture(texture1, texCoords) * result;
}