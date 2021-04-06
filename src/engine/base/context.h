
#ifndef CONTEXT_
#define CONTEXT_

class Drawer;
class Asset;
class Camera;
class Editor; 
class Context {

	private:
		int window_width, window_height; 
		int viewport_x, viewport_y, viewport_width, viewport_height; 
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
		
		
		
		void movecameradebug(SDL_Event e);
		
		void StartFrame();
		void EndFrame();
		void Quit();
		bool IsValid();
		void SetViewPort(int x , int y , int w , int h);
		void SetFramexSec(int framexsec);
		void SetMouseCoords();
		void GetWindowSize(int & w, int & h);
		
		void GetMouseCoords(float& x, float& y);
		
		SDL_GLContext GetSDLGLcontext();
		
		
		SDL_Window* GetWindow(); 
		
	
};

#endif
