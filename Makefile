
IMGUI_DIR = ./src/external/imgui

CC = g++ -pthread
PATHS = -I ./src/engine/ -I ./src/external/ -I ./src/external/imgui
LIBS = -lSDL2 -lGL -lGLU -lGLEW

BASE = ./src/engine/base/context.cpp ./src/engine/base/shader.cpp ./src/engine/base/drawer.cpp ./src/engine/base/asset.cpp ./src/engine/base/camera.cpp ./src/engine/base/gameobj3d.cpp 
DRAWERS = ./src/engine/drawers/drawer3d.cpp  ./src/engine/drawers/orientation.cpp ./src/engine/drawers/terrain.cpp 
EDITORS =  ./src/engine/editors/editor.cpp

SOURCES = $(BASE)  $(EDITORS) $(DRAWERS) 
SOURCES += $(IMGUI_DIR)/imgui.cpp $(IMGUI_DIR)/imgui_demo.cpp $(IMGUI_DIR)/imgui_draw.cpp $(IMGUI_DIR)/imgui_tables.cpp $(IMGUI_DIR)/imgui_widgets.cpp
SOURCES += $(IMGUI_DIR)/backends/imgui_impl_sdl.cpp $(IMGUI_DIR)/backends/imgui_impl_opengl3.cpp

examples:
	$(CC) -g $(INC) $(PATHS)  $(SOURCES) ./src/open_window.cpp $(LIBS) -o ./bin/open_window
