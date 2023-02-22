#pragma once
#include "common.h"



class Texture2D{
public:
	Texture2D(const unsigned int tex_count);
	void bind(const unsigned int& index)const;
	//void set_parameters();
	void flip_on_load(const bool& flip) const;
	void load_texture(const std::string& name);
	
private:
	std::vector<unsigned int> texture_list;
};
