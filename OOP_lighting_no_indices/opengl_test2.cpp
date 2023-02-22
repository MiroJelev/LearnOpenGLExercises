#include "common.h"
#include "Shader.h"
#include "texture.h"
#include "vertex_buffer.h"
#include "vertex_array.h"
#include "element_buffer.h"
#include "camera.h"


sf::ContextSettings settings;

int main(){
	
	settings.majorVersion = 3;
	settings.minorVersion = 3;
	settings.attributeFlags = 1;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 4;
	
	
	sf::Window window(sf::VideoMode(scr_w, scr_h), "OpenGL", sf::Style::Default, settings);
	window.setMouseCursorGrabbed(true);
	//window.setMouseCursorVisible(false);
	
	glewInit();
	
	glEnable(GL_DEPTH_TEST);
	
	//vertices of a cube 40positions
	std::array<float, 216> vertices = {
		//positions				//normals
		 -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};
	
	/*//indices for EBO buffer	
	std::array<unsigned int, 36> indices = {
		0, 1, 2,	//ABC
		2, 3, 0,	//CDA
		
		4, 0, 3,	//EAD
		3, 7, 4,	//DNE
		
		5, 4, 7,	//FEN
		7, 6, 5,	//NMF
		
		1, 2, 6,	//BCM
		6, 5, 1,	//MFB
		
		4, 0, 1,	//EAB
		1, 5, 4,	//BFE
		
		3, 2, 6,	//DCM
		6, 7, 3,	//MND
	};
	*/
	
	//cubes
	glm::vec3 cube_positions[] = {
		glm::vec3( 0.0f,  0.0f,  0.0f), 
		glm::vec3( 2.0f,  5.0f, -15.0f), 
		glm::vec3(-1.5f, -2.2f, -2.5f),  
		glm::vec3(-3.8f, -2.0f, -12.3f),  
		glm::vec3( 2.4f, -0.4f, -3.5f),  
		glm::vec3(-1.7f,  3.0f, -7.5f),  
		glm::vec3( 1.3f, -2.0f, -2.5f),  
		glm::vec3( 1.5f,  2.0f, -2.5f), 
		glm::vec3( 1.5f,  0.2f, -1.5f), 
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};
	
		
	Vertex_buffer vbo{1};
	vbo.bind(0);
	//vbo.insert_data(vertices);
	glBufferData(GL_ARRAY_BUFFER, 		//copy created
				sizeof(vertices), 		//user-def data
				&vertices, 				//to buffer
				GL_STATIC_DRAW);


	//generate VAO
	Vertex_array object_vao{1};
	object_vao.bind(0);
	//linking vertex attributes (how is memory interpreted)
	//position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//normal
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	
	/*//generate EBO buffer
	Element_buffer ebo{1};
	ebo.bind(0);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
				sizeof(indices),
				&indices,
				GL_STATIC_DRAW);
				
			*/
			
			
	Vertex_array light_vao{1};	//light cube
	light_vao.bind(0);			//
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	//ebo.bind(0);
	
			
	////////////////////////////////////////////////			
	
	
	glm::vec3 object_color(1.0f, 0.5f, 0.31f);
	glm::vec3 light_color(1.0f, 1.0f, 1.0f);
	glm::vec3 light_position(1.2f, 1.0f, -5.0f);

	
	Shader object_shaders{"shaders/shader.vs", "shaders/object_shader.fs"};
	object_shaders.use();
	
	object_shaders.set_vec3("object_color", object_color);
	object_shaders.set_vec3("light_color", light_color);
	object_shaders.set_vec3("light_position", light_position);
	
	Shader light_source_shaders{"shaders/shader.vs", "shaders/light_source_shader.fs"};
	//light_source_shaders.use();


	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	
	
	//model matrix
	glm::mat4 model = glm::mat4(1.0f);
	//model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	//model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
	model = glm::mat4(1.0f);

	

	Camera camera;
	camera.face(glm::vec3(0.0, 0.0, -1.0));//face cubes
	camera.add_yaw(-90.0f);
	//view matrix
	glm::mat4 view = glm::mat4(1.0f);
	camera.calculate_view(view);
	
	//projection matrix
	glm::mat4 projection = glm::mat4(1.0f);
	camera.calculate_perspective(projection);
	
	object_shaders.use();
	object_shaders.set_mat4("model", model);
	object_shaders.set_mat4("view", view);
	object_shaders.set_mat4("projection", projection);
	
	
	light_source_shaders.use();
	light_source_shaders.set_mat4("model", model);
	light_source_shaders.set_mat4("view", view);
	light_source_shaders.set_mat4("projection", projection);
	
	
	
	//time between frames
	float delta_time = 0.0f; //time between current frame and last frame
	float last_frame = 0.0f; //time of last frame
	
	//mouse//
	sf::Vector2i screen_center{scr_w/2, scr_h/2};
	sf::Vector2f offset;
	glm::vec3 direction;
	sf::Mouse::setPosition(screen_center, window);
	////////
	
	
	sf::Clock clock;
	glViewport(0, 0, scr_w, scr_h);
	bool running = true;
	while(running){
		sf::Event event;
		while(window.pollEvent(event)){
			if (event.type == sf::Event::KeyPressed)
			{
				if(event.key.code == sf::Keyboard::Escape || event.type == sf::Event::Closed){
					running = false;
				}
				else if(event.type == sf::Event::Resized){
					glViewport(0, 0, event.size.width, event.size.height);
				}
				
			}
			if(event.type == sf::Event::MouseWheelScrolled){
				if(event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel){
					camera.add_fov(event.mouseWheelScroll.delta);
					
					camera.calculate_perspective(projection);
					object_shaders.use();
					object_shaders.set_mat4("projection", projection);
					light_source_shaders.use();
					light_source_shaders.set_mat4("projection", projection);
					
				}
			}
			
		}
		
		//constant speed on all hardware
		sf::Time elapsed_frame = clock.getElapsedTime();
		float current_frame = elapsed_frame.asSeconds();
		delta_time = current_frame - last_frame;
		last_frame = current_frame;
		camera.set_speed(delta_game_speed * delta_time);
		//
		
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
			camera.move_forward();
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
			camera.move_backward();
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
			camera.move_right();
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
			camera.move_left();
		}
		//mouse
		sf::Vector2f mouse_position = (sf::Vector2f)sf::Mouse::getPosition(window);
		offset.x = mouse_position.x - screen_center.x;
		offset.y = mouse_position.y - screen_center.y;
		sf::Mouse::setPosition(screen_center, window);
		
		offset.x *= mouse_sensitivity;
		offset.y *= mouse_sensitivity;
		//////
		//camera
		camera.add_yaw(offset.x);
		camera.add_pitch(offset.y);
		std::cout << camera.get_yaw() << " " << camera.get_pitch() << std::endl;
		
		direction.x = cos(glm::radians(camera.get_yaw())) * cos(glm::radians(camera.get_pitch()));
		direction.y = sin(glm::radians(camera.get_pitch()));
		direction.z = sin(glm::radians(camera.get_yaw())) * cos(glm::radians(camera.get_pitch()));
		camera.face(direction);
		camera.calculate_view(view);
		object_shaders.use();
		object_shaders.set_mat4("view", view);
		light_source_shaders.use();
		light_source_shaders.set_mat4("view", view);
		//
		
		
		//clear buffers
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		//draw...
		model = glm::mat4(1.0f);
		model = glm::translate(model, light_position);
		model = glm::scale(model, glm::vec3(0.2f));
		
		sf::Time elapsed3 = clock.getElapsedTime();
		//model = glm::rotate(model, (float)elapsed1.asSeconds() * glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glm::vec3 circle_around_Y(1.0f);
		circle_around_Y.x = sin(glm::radians(elapsed3.asSeconds() * 40));
		circle_around_Y.y = cos(glm::radians(elapsed3.asSeconds() * 40));
		circle_around_Y.z = ( 0.0f );
		light_position = circle_around_Y;
		model = glm::translate(model, circle_around_Y);
		
		
		light_source_shaders.use();
		light_source_shaders.set_mat4("model", model);
		light_vao.bind(0);
		//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		
		
		object_shaders.use();
		object_shaders.set_vec3("view_position", camera.get_position());
		for(int i = 0; i < 10; i++){
			
			//model matrix
			model = glm::mat4(1.0f);
			model = glm::translate(model, cube_positions[i]);
//			model = glm::translate(model, cube_positions[0]);
			float angle = 20.0f * i;
//			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.0f));
			
			if((i%3) == 0){
				sf::Time elapsed1 = clock.getElapsedTime();
				model = glm::rotate(model, (float)elapsed1.asSeconds() * glm::radians(30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
			}
			
			//object_shaders.use();
			object_shaders.set_mat4("model", model);
			object_shaders.set_vec3("light_position", light_position);
			object_vao.bind(0);
			//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			
			
			
		}
		//end the current frame (internally swaps the front and back buffers)
		window.display();
	}
	
}
