//#define GLEW_STATIC
#include <GL/glew.h>

//SFML
#include <SFML/Window.hpp>

//STB image library
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

//GLM
#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/matrix_transform.hpp"
#include "glm/glm/gtc/type_ptr.hpp"

//standard library
#include <iostream>
#include <cmath>




#include "Shader.h"

int scr_w = 800;
int scr_h = 600;


sf::ContextSettings settings;

int main(){
	
	settings.majorVersion = 3;
	settings.minorVersion = 3;
	settings.attributeFlags = 1;
	
	sf::Window window(sf::VideoMode(scr_w, scr_h), "OpenGL", sf::Style::Default, settings);
	glewInit();
	
	
	//vertecies we want to render
	float vertices[] = {
		//positions				//colors			//texture coords
		 0.5f,  0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	1.0f, 1.0f,		//top right
		 0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	1.0f, 0.0f,		//bottom right
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f, 1.0f,	0.0f, 0.0f,		//bottom left
		-0.5f,  0.5f, 0.0f,		1.0f, 1.0f, 0.0f,	0.0f, 1.0f
	};
	//indices for EBO buffer	
	unsigned int indices[] = {
		0, 1, 3,	//first triangle
		1, 2, 3
	};
	
	
	//texture
	unsigned int texture[2]; //tex id
	glGenTextures(2, texture);
	//bind texture
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	//set texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	int width, height, nrChannels;
	unsigned char *data = stbi_load("assets/container.jpg", 
									&width, 
									&height, 
									&nrChannels, 
									0);
	if(!data){
		std::cerr << "Failed to load texture" << std::endl;
	}else{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
					 GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	stbi_image_free(data);



	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
		//load image with stb_image.h

	stbi_set_flip_vertically_on_load(true); 
	unsigned char *data2 = stbi_load("assets/awesomeface.png", 
									&width, 
									&height, 
									&nrChannels, 
									0);
	if(!data2){
		std::cerr << "Failed to load texture" << std::endl;
	}else{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
					 GL_RGBA, GL_UNSIGNED_BYTE, data2);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	stbi_image_free(data2);
	
	
	
	
	Shader v_fr_shader{"shaders/shader.vs", "shaders/shader.fs"};
	v_fr_shader.use();
	glUniform1i(glGetUniformLocation(v_fr_shader.ID, "ourTexture1"), 0); //set manually
	v_fr_shader.set_int("ourTexture2", 1);		//or with shader class
	
	float tex_mix_factor = 0.2f;
	v_fr_shader.set_float("tex_mix", tex_mix_factor);
	
	
	//VBO buffer
	unsigned int VBO;					//buffer id
	glGenBuffers(1, &VBO);				//generate buffer with id VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);	//bind type(GL_ARRAY_BUFFER)(thats the VBO type) to the id					
	glBufferData(GL_ARRAY_BUFFER, 		//copy created
				sizeof(vertices), 		//user-def data
				vertices, 				//to buffer
				GL_STATIC_DRAW);		
	
	//generate VAO
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	//linking vertex attributes (how is memory interpreted)
	//position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	
	//generate EBO buffer
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	
	
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	//scale and rotate
	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
	trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
	//pass transform to vertex shader
	unsigned int transform_loc = glGetUniformLocation(v_fr_shader.ID, "transform");
	glUniformMatrix4fv(transform_loc, 1, GL_FALSE, glm::value_ptr(trans));
	
	
	sf::Clock clock;
	glViewport(0, 0, scr_w, scr_h);
	bool running = true;
	while(running){
		sf::Event event;
		while(window.pollEvent(event)){
			if(event.key.code == sf::Keyboard::Escape || event.type == sf::Event::Closed){
				running = false;
			}
			else if(event.type == sf::Event::Resized){
				glViewport(0, 0, event.size.width, event.size.height);
			}
			
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && tex_mix_factor < 1.0){
				tex_mix_factor = tex_mix_factor + 0.1f;
				v_fr_shader.set_float("tex_mix", tex_mix_factor);
				std::cout << tex_mix_factor << "\n";
			}else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && tex_mix_factor > 0.001){
				tex_mix_factor = tex_mix_factor- 0.1f;
				v_fr_shader.set_float("tex_mix", tex_mix_factor);
				std::cout << tex_mix_factor << "\n";
			}
		}
		//clear buffers
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		//draw...
		//glUseProgram(shader_program);
		v_fr_shader.use();
		//v_fr_shader.set_float("offset", 0.5f);
		
		/*sf::Time elapsed = clock.getElapsedTime();
		float green_val = std::sin(elapsed.asSeconds()) / 2.0f + 0.5f;
		int vertex_color_location = glGetUniformLocation(shader_program, "our_color");
		glUniform4f(vertex_color_location, 0.0f, green_val, 0.0f, 1.0f);*/
		
		glm::mat4 trans = glm::mat4(1.0f);
		sf::Time elapsed = clock.getElapsedTime();
		trans = glm::rotate(trans, (float)elapsed.asSeconds(), glm::vec3(0.0f, 0.0f, 1.0f));
		trans = glm::translate(trans, glm::vec3(0.5f, 0.5f, 0.0f));
		glUniformMatrix4fv(transform_loc, 1, GL_FALSE, glm::value_ptr(trans));
		
		
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture[1]);
		
		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		
		
		glm::mat4 trans1 = glm::mat4(1.0f);
		sf::Time elapsed1 = clock.getElapsedTime();
		trans1 = glm::translate(trans1, glm::vec3(std::sin((float)elapsed1.asSeconds()), -0.5f, 0.0f));
		trans1 = glm::rotate(trans1, (float)elapsed1.asSeconds(), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(transform_loc, 1, GL_FALSE, glm::value_ptr(trans1));
		
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		
		trans1 = glm::mat4(1.0f);
		elapsed1 = clock.getElapsedTime();
		trans1 = glm::scale(trans1, glm::vec3(std::sin((float)elapsed1.asSeconds())));
		trans1 = glm::rotate(trans1, (float)elapsed1.asSeconds(), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(transform_loc, 1, GL_FALSE, glm::value_ptr(trans1));
		
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		
		
		//end the current frame (internally swaps the front and back buffers)
		window.display();
	}
	
	//release resources...
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(2, &VBO);
	glDeleteBuffers(1, &EBO);
}
