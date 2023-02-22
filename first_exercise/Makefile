
OBJS = opengl_test.cpp

CC = g++


LINKER_FLAGS = -lsfml-window -lsfml-system -lGL -lGLEW
#	-lGLU
# -lsfml-audio

EX_NAME = test

all:$(OBJS)
	$(CC) $(OBJS) $(LINKER_FLAGS) -o $(EX_NAME)

clean:
	rm $(EX_NAME)
