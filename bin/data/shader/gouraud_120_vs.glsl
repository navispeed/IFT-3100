#version 150 core

uniform mat4 modelViewProjectionMatrix;
uniform mat4 projectionMatrix;

in vec4 position;
in vec4 normal;

//light and material properties
uniform vec3 light_pos = vec3(100.0,100.0,100.0);
uniform vec3 diffuse_albedo = vec3(0.5,0.2,0.7);
uniform vec3 specular_albedo = vec3(0.7);
uniform float specular_power = 128.0;
uniform vec3 ambient = vec3(0.1,0.1,0.1);

out vec3 color;

void main()
{
	//calculate the view-space coordinate
	vec4 P = modelViewProjectionMatrix * position;

	//calculate the normal in view space
	vec3 N = mat3(modelViewProjectionMatrix) * vec3(normal);

	//calculate the view-space light vector
	vec3 L = light_pos - P.xyz;

	//calculate view vector
	//simply the negative of the
	//view-space position
	vec3 V = -P.xyz;

	//normalize all the vectors
	N = normalize(N);
	L = normalize(L);
	V = normalize(V);

	//calculate R  by reflecting -L around the plane defined by N
	vec3 R = reflect(-L,N);

	//calculate the diffuse and specular contributions
	vec3 diffuse = max(dot(N,L),0.0) * diffuse_albedo;

	vec3 specular = pow(max(dot(R,V),0.0),specular_power) * specular_albedo;

	//send the color output to the fragment shader
	color = ambient + diffuse + specular;

	//calculate the clip-space position of each vertex
	gl_Position = projectionMatrix * P;
}