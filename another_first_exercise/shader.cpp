#include "Shader.h"

Shader::Shader(const char* vertex_path, const char* fragment_path){
	//1. retrieve the vertex/fragment source from filepath
	std::string vertex_source;
	std::string fragment_source;
	std::ifstream v_shader_file;
	std::ifstream f_shader_file;
	
	try{
		v_shader_file.open(vertex_path);
		f_shader_file.open(fragment_path);
		std::stringstream v_shader_stream, f_shader_stream;
		
		v_shader_stream << v_shader_file.rdbuf();
		f_shader_stream << f_shader_file.rdbuf();
		
		v_shader_file.close();
		f_shader_file.close();
		
		vertex_source = v_shader_stream.str();
		fragment_source = f_shader_stream.str();
		
	}
	catch(std::ifstream::failure e){
		std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ\n\t" << e.what() << std::endl;
	}
	
	const char* v_shader_source = vertex_source.c_str();
	const char* f_shader_source = fragment_source.c_str();
	
	//2. compile shaders
	unsigned int vertex, fragment;
	int success;
	char info_log[512];
	
	//vertex Shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &v_shader_source, NULL);
	glCompileShader(vertex);
	
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if(!success){
		glGetShaderInfoLog(vertex, 512, NULL, info_log);
		std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << info_log << std::endl;
		
	}
	
	//fragment shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &f_shader_source, NULL);
	glCompileShader(fragment);
	
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if(!success){
		glGetShaderInfoLog(fragment, 512, NULL, info_log);
		std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << info_log << std::endl;
		
	}
	
	//shader Program
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if(!success){
		glGetProgramInfoLog(ID, 512, NULL, info_log);
		std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << info_log << std::endl;
	}
	
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	
}

Shader::~Shader(){
	glDeleteProgram(ID);
}

void Shader::use(){
	glUseProgram(ID);
}

void Shader::set_bool(const std::string &name, bool value) const{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::set_int(const std::string &name, int value) const{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::set_float(const std::string &name, float value) const{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

























