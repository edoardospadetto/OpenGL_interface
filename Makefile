
IMGUI_DIR = ./src/external/imgui

CC = g++ -pthread
PATHS = -I ./src/base/ -I ./src/external/ -I ./src/external/imgui
LIBS = -lSDL2 -lGL -lGLU -lGLEW
SOURCES = ./src/base/context.cpp ./src/base/shader.cpp ./src/base/drawer.cpp ./src/base/asset.cpp ./src/drawers/drawer3d.cpp ./src/base/camera.cpp ./src/drawers/orientation.cpp ./src/drawers/terrain.cpp ./src/base/gameobj3d.cpp ./src/base/editor.cpp

SOURCES += $(IMGUI_DIR)/imgui.cpp $(IMGUI_DIR)/imgui_demo.cpp $(IMGUI_DIR)/imgui_draw.cpp $(IMGUI_DIR)/imgui_tables.cpp $(IMGUI_DIR)/imgui_widgets.cpp
SOURCES += $(IMGUI_DIR)/backends/imgui_impl_sdl.cpp $(IMGUI_DIR)/backends/imgui_impl_opengl3.cpp

examples:
	$(CC) -g $(INC) $(PATHS)  $(SOURCES) ./src/open_window.cpp $(LIBS) -o ./bin/open_window
