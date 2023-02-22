
OBJS = opengl_test2.cpp shader.cpp texture.cpp vertex_buffer.cpp vertex_array.cpp element_buffer.cpp camera.cpp

CC = g++


LINKER_FLAGS = -lsfml-window -lsfml-system -lGL -lGLEW
#	-lGLU
# -lsfml-audio

EX_NAME = test2

all:$(OBJS)
	$(CC) $(OBJS) $(LINKER_FLAGS) -o $(EX_NAME)

clean:
	rm $(EX_NAME)
