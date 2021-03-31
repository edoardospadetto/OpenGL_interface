
CC = g++ -pthread
PATHS = -I ./src/base/
LIBS = -lSDL2 -lGL -lGLU -lGLEW
SOURCES = ./src/base/context.cpp ./src/base/shader.cpp ./src/base/drawer.cpp ./src/base/asset.cpp ./src/drawer3d.cpp ./src/base/camera.cpp ./src/orientation.cpp

examples:
	$(CC) -g $(INC) $(PATHS)  $(SOURCES) ./src/open_window.cpp $(LIBS) -o ./bin/open_window
