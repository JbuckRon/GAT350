#version 430 core

in vec3 refract_dir;
in vec3 reflect_dir;

out vec4 fcolor;

uniform samplerCube Cubemap;
uniform float interpolation;

void main()
{
	// set fragment color
	vec3 reflect_color = texture(???).rgb;
	vec3 refract_color = texture(???).rgb;

	vec3 color = mix(???); 

	fcolor = texture(Cubemap, refract_dir);
}
