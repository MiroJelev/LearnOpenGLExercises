//STB image library
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "texture.h"
/*
Texture2D::Texture2D() : texture_list(1){
	glGenTextures(1, &texture_list[0]);
	
}*/
Texture2D::Texture2D(const unsigned int tex_count) : texture_list(tex_count){
	glGenTextures(tex_count, texture_list.data());
	
}
void Texture2D::bind(const unsigned int& index)const{
	glBindTexture(GL_TEXTURE_2D, texture_list[index]);
}
/*
void Texture2D::set_parameters(){
	//set texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
}
*/

void Texture2D::flip_on_load(const bool& flip) const{
	stbi_set_flip_vertically_on_load(flip);
}
void Texture2D::load_texture(const std::string& name){
	int width, height, nrChannels;
	unsigned char *data = stbi_load(name.c_str(), &width, &height, &nrChannels, 0);
	if(!data){
		std::cerr << "Failed to load texture" << std::endl;
		//throw exception
	}else{
		int pos = name.find_last_of('.');
		if(name.substr(pos+1) == "jpg"){
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
						 GL_RGB, GL_UNSIGNED_BYTE, data);
		}else if(name.substr(pos+1) == "png"){
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
						 GL_RGBA, GL_UNSIGNED_BYTE, data);	//Alpha channel for png GL_RGBA
		}else{
			//throw invalid argument ?
		}

		glGenerateMipmap(GL_TEXTURE_2D);
	}
	stbi_image_free(data);
}

