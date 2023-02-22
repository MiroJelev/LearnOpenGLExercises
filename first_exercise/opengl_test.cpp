//#define GLEW_STATIC
#include <GL/glew.h>

#include <SFML/Window.hpp>
//#include <SFML/OpenGL.hpp>

//#include <GL/gl.h>
//#include <GL/glu.h>
//#include <GL/glut.h>
//#include <GL/glext.h>

#include <iostream>

const char *vertex_shader_source = "#version 330 core\n"
			"layout (location = 0) in vec3 aPos;\n"
			"void main()\n{"
			"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);"
			"}\0";
const char *fragment_shader_source = "#version 330 core\n"
			"out vec4 frag_color;\n"
			"void main()\n{"
			"frag_color = vec4(1.0f, 0.5f, 0.2f, 1.0f);"
			"}\0";
const char *fragment_shader_source2 = "#version 330 core\n"
			"out vec4 frag_color;\n"
			"void main()\n{"
			"frag_color = vec4(1.0f, 1.0f, 0.0f, 1.0f);"
			"}\0";


int scr_w = 800;
int scr_h = 600;


sf::ContextSettings settings;

int main(){
	settings.majorVersion = 3;
	settings.minorVersion = 3;
	settings.attributeFlags = 1;
	
	sf::Window window(sf::VideoMode(scr_w, scr_h), "OpenGL", sf::Style::Default, settings);
	glewInit();
	/*sf::ContextSettings settings2 = window.getSettings();
	std::cout << "depth bits:" << settings2.depthBits << std::endl;
	std::cout << "stencil bits:" << settings2.stencilBits << std::endl;
	std::cout << "antialiasing level:" << settings2.antialiasingLevel << std::endl;
	std::cout << "version:" << settings2.majorVersion << "." << settings2.minorVersion << std::endl;
	*/
	
	/*float vertices[] = {
		 0.0f,  0.5f, 0.0f,
		 0.0f, -0.5f, 0.0f,
		-0.5f,  0.0f, 0.0f,
		 0.1f,  0.5f, 0.0f,
		 0.1f, -0.5f, 0.0f,
		 0.6f,  0.0f, 0.0f
	 };*/
	
	float vertices1[] = {
		 0.5f,  0.5f, 0.0f,	//top right
		 0.5f,  0.0f, 0.0f,	//bottom left
		 0.0f,  0.5f, 0.0f	//top left
	};
	float vertices2[] = {
		-0.5f, -0.5f, 0.0f,	//bottom right
		-0.5f,  0.0f, 0.0f,	//bottom left
		 0.0f, -0.5f, 0.0f	//top left
	};
	
	
	//vertecies we want to render
	/*float vertices[] = {
		 0.5f,  0.5f, 0.0f,	//top right
		 0.5f, -0.5f, 0.0f,	//bottom right
		-0.5f, -0.5f, 0.0f,	//bottom left
		-0.5f,  0.5f, 0.0f	//top left
	};
	//indices for EBO buffer
	unsigned int indices[] = {
		0, 1, 3,	//first triangle
		1, 2, 3		//second triangle
	};*/
	
	
	//vertex shader
	unsigned int vertex_shader;											//shader id
	vertex_shader = glCreateShader(GL_VERTEX_SHADER);					//create type of shader
	glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);		//assoc code with shader
	glCompileShader(vertex_shader);										//compile shader
	//vert sh compilation error check
	int success;
	char info_log[512];
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);			//check for error
	if(!success){
		glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);			//get error message
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
				<< info_log << std::endl;
	}
	
	
	//fragmet shader
	unsigned int fragment_shader;
	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
	glCompileShader(fragment_shader);
	//fr sh compilation error check
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
	if(!success){
		glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
				<< info_log << std::endl;
	}
	//fragmet shader
	unsigned int fragment_shader2;
	fragment_shader2 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader2, 1, &fragment_shader_source2, NULL);
	glCompileShader(fragment_shader2);
	//fr sh compilation error check
	glGetShaderiv(fragment_shader2, GL_COMPILE_STATUS, &success);
	if(!success){
		glGetShaderInfoLog(fragment_shader2, 512, NULL, info_log);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
				<< info_log << std::endl;
	}
	
	//shader program object
	unsigned int shader_program;
	shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glLinkProgram(shader_program);
	glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
	if(!success){
		glGetShaderInfoLog(shader_program, 512, NULL, info_log);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
				<< info_log << std::endl;
	}
	
	glUseProgram(shader_program);		//activate program
	
	
	
	//shader program object
	unsigned int shader_program2;
	shader_program2 = glCreateProgram();
	glAttachShader(shader_program2, vertex_shader);
	glAttachShader(shader_program2, fragment_shader2);
	glLinkProgram(shader_program2);
	glGetProgramiv(shader_program2, GL_LINK_STATUS, &success);
	if(!success){
		glGetShaderInfoLog(shader_program2, 512, NULL, info_log);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
				<< info_log << std::endl;
	}
	
	glUseProgram(shader_program2);		//activate program
	
	
	
	
	
	
	
	
	glDeleteShader(vertex_shader);		//after linking the program the objects should be deleted
	glDeleteShader(fragment_shader);
	
	
	
	//VBO buffer
	unsigned int VBO[2];					//buffer id
	glGenBuffers(2, &VBO[0]);				//generate buffer with id VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);	//bind type(GL_ARRAY_BUFFER)(thats the VBO type) to 
										//the id
	
	glBufferData(GL_ARRAY_BUFFER, 		//copy created
				sizeof(vertices1), 		//user-def data
				vertices1, 				//to buffer
				GL_STATIC_DRAW);		
	
	
	
	//generate VAO
	unsigned int VAO[2];
	glGenVertexArrays(1, &VAO[0]);
	glBindVertexArray(VAO[0]);
	//linking vertex attributes (how is memory interpreted)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
		//VBO buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);	//bind type(GL_ARRAY_BUFFER)(thats the VBO type) to 
										//the id
	
	glBufferData(GL_ARRAY_BUFFER, 		//copy created
				sizeof(vertices2), 		//user-def data
				vertices2, 				//to buffer
				GL_STATIC_DRAW);	
	//generate VAO
	glGenVertexArrays(1, &VAO[1]);
	glBindVertexArray(VAO[1]);
	//linking vertex attributes (how is memory interpreted)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	/*//generate EBO buffer
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices1), indices, GL_STATIC_DRAW);
	*/
	
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
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
		}
		//clear buffers
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		//draw...
		glUseProgram(shader_program);
		glBindVertexArray(VAO[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		
		glUseProgram(shader_program2);
		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		
		
		
		//end the current frame (internally swaps the front and back buffers)
		window.display();
	}
	
	//release resources...
	glDeleteVertexArrays(2, VAO);
	glDeleteBuffers(2, VBO);
	//glDeleteBuffers(1, &EBO);
	glDeleteProgram(shader_program);
}
