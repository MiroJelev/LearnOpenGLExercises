#ifndef SHADER_H
#define SHADER_H
#include <GL/glew.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>



class Shader{
public:
	unsigned int ID;	//the program ID
	//constructor reads and build the shader
	Shader(const char* vertex_path, const char* fragment_path);
	~Shader();
	//use/activate the shader
	void use();
	//utility uniform functions
	void set_bool(const std::string &name, bool value) const;
	void set_int(const std::string &name, int value) const;
	void set_float(const std::string &name, float value) const;
};

#endif
