#include "vertex_array.h"


Vertex_array::Vertex_array(const unsigned int size) : vao_list(size){
	glGenVertexArrays(size, vao_list.data());
}
Vertex_array::~Vertex_array(){
	glDeleteVertexArrays(vao_list.size(), vao_list.data());
}
void Vertex_array::bind(const unsigned int& index) const{
	glBindVertexArray(vao_list[index]);
}
