#include "common.h"


class Vertex_buffer{
public:
	Vertex_buffer(const unsigned int size);
	~Vertex_buffer();
	void bind(const unsigned int& index) const;
	//void insert_data(vertices_array& vertices);
private:
	std::vector<unsigned int> vbo_list;
};
