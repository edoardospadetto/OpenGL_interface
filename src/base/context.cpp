
#include "turtle.h"



Context::Context(int _width, int _height, const std::string& _name ) : width(_width) , height(_height)
{	
   if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Failed to initialize the SDL2 library\n");
      
    }
    //Use OpenGL 2.1
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
            
    title = _name;
    window = SDL_CreateWindow(title.c_str(),
    				SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED,
				_width, _height,
				SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    if(!window)
    {
        printf("Failed to create window\n");
     
    }
    
  
     glContext = SDL_GL_CreateContext( window );
    
    if(glContext == NULL)
    {
        printf("Failed to create OpenGL context\n");
     
    }
    
    //Initialize GLEW
    glewExperimental = GL_TRUE; 
    GLenum glewError = glewInit();
    
    if( glewError != GLEW_OK ) 
    {
	printf( "Error initializing GLEW! %s\n", glewGetErrorString( glewError ) );
    }
    if( SDL_GL_SetSwapInterval( 1) < 0 )
    {
        printf( "Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError() );
    }
    
    //CUSTOM INIT
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_FALSE);  
    glDepthFunc(GL_LESS); 
    
    //Imgui
    Imgui(); 
    
}

Context::~Context()
{
	SDL_DestroyWindow(window);
   	SDL_Quit();
}


void Context::SetMouseCoords()
{	int x, y;
	SDL_GetMouseState(&x,&y);
	xMouse = float(x)/float(width) -0.5;
	yMouse = - float(y)/float(height) +0.5;
		
}

void Context::GetMouseCoords(float &x, float&y)
{
	x = xMouse;
	y = yMouse;
}



void Context::Quit()
{
	quit = true;

}


bool Context::IsValid()
{
	
	return (!quit);
}


void Context::SetFramexSec(int framexsec)
{
	int delay = int(1.0/float(framexsec));

}
void Context::StartFrame()
{
	start = SDL_GetTicks();
	glClear( GL_COLOR_BUFFER_BIT );
	glClear( GL_DEPTH_BUFFER_BIT );
		
}

void Context::EndFrame()
{	
	int end;
	end = SDL_GetTicks();
	if( end-start < delay )
	{
		SDL_Delay(delay - (end-start));
	}
	//std::cout << "end frame" << std::endl;
	SDL_GL_SwapWindow(window);
}


void Context::Imgui()
{
    const char* glsl_version = "#version 330";
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsClassic();
    ImGui_ImplSDL2_InitForOpenGL(window, glContext);
    ImGui_ImplOpenGL3_Init(glsl_version);


}

SDL_Window* Context::GetWindow(){return window;}




