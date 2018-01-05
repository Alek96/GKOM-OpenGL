CC = g++
LIBS = -lGL -lGLEW -lglfw -lSOIL
FLAGS = -std=c++11
OBJ = Texture/texture.o Window/window.o Scene/scene.o Scene/render.o Scene/camera.o Model/mesh.o Model/PrimitiveFactory.o Model/simplemodel.o Model/compositemodel.o Shader/shprogram.o

%.o: %.cpp
	$(CC) -c -o $@ $< $(FLAGS) $(LIBS)

all: sawmill

sawmill: main.o $(OBJ)
	$(CC) -o sawmill $^ $(FLAGS) $(LIBS)

.PHONY: clean

clean:
	find . -name \*.o -type f -delete
