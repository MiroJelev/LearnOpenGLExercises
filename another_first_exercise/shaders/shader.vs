#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 our_color;
out vec3 our_pos;
out vec2 TexCoord;

uniform mat4 transform;


void main(){
	gl_Position = transform * vec4(aPos.xyz, 1.0);
	our_color = aColor;
	our_pos = aPos;
	TexCoord = aTexCoord;
}
