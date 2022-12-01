#version 430 core

#define POINT		0
#define DIRECTIONAL	1
#define SPOTLIGHT	2
 
in vec3 position;
//in vec3 normal;
in vec2 texcoord;
in mat3 tbn;
 
out vec4 fcolor; //pixel to draw
 
uniform sampler2D diffuseMap;
uniform sampler2D normalMap;
 
  uniform struct Light
 {
	int type; 
	vec3 ambient;
	vec3 color;
	vec4 position;
	vec3 direction;
	float cutoff;
	float exponent;
 } light;

 uniform struct Material
 {
	vec3 color;
	float shininess;
	vec2 uv_tiling;
	vec2 uv_offset;
 } material;

void phong(vec3 position, vec3 normal, out vec3 ambient, out vec3 diffuse, out vec3 specular)
{
	//ambient
	ambient = light.ambient * material.color;

	//DIFFUSE
	//calculate light direction (unit vector)
	vec3 light_dir = (light.type == DIRECTIONAL) ? normalize(vec3(light.position) - position);

	//calculate light intesity with dot product (normal * light direction)
	float intensity = max(dot(light_dir, normal), 0);
	diffuse = light.color * material.color * intensity;

	//Specular
	specular = vec3(0);
	if (intensity > 0)
	{
		vec3 reflection = reflect(-light_dir, normal);
		vec3 view_dir = normalize(-vec3(position));
		intensity = max(dot(reflection, view_dir), 0);
		intensity = pow(intensity, material.shininess);
		specular = light.color * material.color * intensity;
	}

	//color = ambient * diffuse + specular;

}


void main()
{
	vec2 ttexcoord = (texcoord * material.uv_tiling * material.uv_offset);
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	vec3 normal = texture(normalMap, ttexcoord).rgb;
	normal = (normal * 2);
	normal = normalize(tbn * normal);

	phong(position, normal, ambient, diffuse, specular);	


	vec4 texture_color = texture(diffuseMap, ttexcoord);
	//vec4 texture_color = mix(texture(texture1, ttexcoord), texture(texture2, ttexcoord), 0.5);

	//fcolor = texture_color;
	fcolor = vec4(ambient + diffuse, 1) * texture_color + vec4(specular, 1)* texture(specular, ttexcoord);
}