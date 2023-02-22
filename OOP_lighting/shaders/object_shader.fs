#version 330 core
out vec4 frag_color;
//in vec3 normal;

uniform vec3 object_color;
uniform vec3 light_color;

uniform vec3 light_position;


void main(){
	float ambient_strenght = 0.1;
	vec3 ambient_light = ambient_strenght * light_color;
	frag_color = vec4(ambient_light * object_color, 1.0);
	
	/*
	vec3 norm = normalize(normal);
	vec3 light_direction = normalize(light_position - fragment_position);
	
	float diff = max(dot(norm, light_direction), 0.0);
	vec3 diffuse = diff * light_color;
	vec3 result = (ambient + diffuse) * object_color;
	frag_color = vec4(result, 1.0);
	*/
}
