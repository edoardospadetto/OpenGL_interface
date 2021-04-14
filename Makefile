
IMGUI_DIR = ./src/external/imgui

CC = g++ -pthread
PATHS = -I ./src/engine/ -I ./src/external/ -I ./src/external/imgui
LIBS = -lSDL2 -lGL -lGLU -lGLEW
FLAGS = -ggdb3

BASE = context shader drawer asset camera gameobj3d
BASEDIR = ./src/engine/base/

DRAWERS = drawer3d orientation terrain riggerdrawer
DRAWERSDIR = ./src/engine/drawers/

EDITORS =editor
EDITORSDIR = ./src/engine/editors/

IMGUI = imgui imgui_widgets imgui_demo imgui_tables imgui_draw 
IMGUIBACKENDS =  imgui_impl_opengl3 imgui_impl_sdl
SOURCES = $(addprefix ./build/, $(shell ls ./build/)) 


all : editors drawers base
editors:$(EDITORS)
drawers:$(DRAWERS)
base:$(BASE)
externals:$(IMGUI) 

it: 
	$(CC) -c $(FLAGS) $(INC) $(PATHS)  ./src/open_window.cpp $(LIBS) -o ./build/open_window.o
	$(CC) $(FLAGS) $(INC) $(PATHS)  $(SOURCES)  $(LIBS) -o ./bin/open_window
examples:
	$(CC) $(FLAGS) $(INC) $(PATHS)  $(SOURCES) ./src/open_window.cpp $(LIBS) -o ./bin/open_window
	
$(IMGUI): $(IMGUIBACKENDS)
	$(CC) -c $(FLAGS) $(INC) $(PATHS) ./src/external/imgui/$@.cpp $(LIBS) -o ./build/$@.o
	
$(IMGUIBACKENDS):
	$(CC) -c $(FLAGS) $(INC) $(PATHS) ./src/external/imgui/backends/$@.cpp $(LIBS) -o ./build/$@.o
	
	
$(EDITORS): 
	$(CC) -c $(FLAGS) $(EDITORSDIR)$@.cpp $(INC) $(PATHS) -o ./build/$@.o
	
$(DRAWERS):
	$(CC) -c $(FLAGS) $(INC) $(PATHS) $(DRAWERSDIR)$@.cpp -o ./build/$@.o 

$(BASE):
	$(CC) -c $(FLAGS) $(INC) $(PATHS) $(BASEDIR)$@.cpp -o ./build/$@.o 
