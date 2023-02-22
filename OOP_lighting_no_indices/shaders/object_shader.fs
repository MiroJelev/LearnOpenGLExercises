#version 330 core
out vec4 frag_color;
in vec3 normal;
in vec3 fragment_position;

uniform vec3 object_color;
uniform vec3 light_color;
uniform vec3 light_position;
uniform vec3 view_position;


void main(){
	//ambient
	float ambient_strenght = 0.1;
	vec3 ambient_light = ambient_strenght * light_color;
	//frag_color = vec4(ambient_light * object_color, 1.0);
	
	//normal and vector to light
	vec3 norm = normalize(normal);
	vec3 light_direction = normalize(light_position - fragment_position);
	//diffusion
	float diff = max(dot(norm, light_direction), 0.0);
	vec3 diffuse = diff * light_color;
	//vec3 result = (ambient_light + diffuse) * object_color;
	//frag_color = vec4(result, 1.0);
	
	//specular
	float specular_strength = 0.5f;
	vec3 view_direction = normalize(view_position - fragment_position);
	vec3 reflection_direction = reflect(-light_direction, norm);
	
	float spec = pow(max(dot(view_direction, reflection_direction), 0.0), 32);
	vec3 specular = specular_strength * spec * light_color;
	
	vec3 result = (ambient_light + diffuse + specular) * object_color;
	frag_color = vec4(result, 1.0);
}
