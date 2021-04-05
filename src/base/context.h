
#ifndef CONTEXT_
#define CONTEXT_

class Drawer;
class Asset;
class Camera;
class Context {

	private:
		int width, height; 
		std::string title;
		SDL_Window* window = nullptr;
		SDL_GLContext glContext;
		float xMouse=0.0, yMouse=0.0;
		bool quit = false;
		
		int delay=20;
		int start = 0;
 	public: 
 		
 		Context(int _width, int _height, const std::string& _name );
		~Context();
		
		void Imgui();
		
		void movecameradebug(SDL_Event e);
		
		void StartFrame();
		void EndFrame();
		void SetFramexSec(int framexsec);
		
		void SetMouseCoords();
		void GetMouseCoords(float& x, float& y);
		
		bool IsValid();
		void Quit();
		SDL_Window* GetWindow(); 
		
	
};

#endif
