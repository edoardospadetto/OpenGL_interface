#define STB_IMAGE_IMPLEMENTATION


#include <thread> 

#include "./base/turtle.h"
#include "drawer3d.h"
#include "orientation.h"

int WorldLoop(Context* current_context, Camera* camera)
{
	
	while(current_context->IsValid())
	{
		camera->Move();	
		SDL_Delay(20);	
	
	}
	std::cout << "exit world thread " << std::endl;
	return 0;
}

int GraphicLoop(Context* current_context, Drawer3d* drawer, Gui * orientation, Asset* asset, Camera* camera)
{
		//Drawer3d* drawer1=  dynamic_cast<Drawer3d*>(drawer);
		
		while(current_context->IsValid())
		{
			current_context->StartFrame();
		
			
			glClearColor( 0.2f, 0.f, 0.f, 0.1f );
			//asset->Rotate();
			
			
			drawer->Draw(asset, camera);
			orientation->Draw(camera);
			
			current_context->EndFrame();
		}
		std::cout << "exit graphic thread" << std::endl;
		
return 0;

}



int InputLoop(Context* current_context, Camera* camera)
{	
	int xMouse, yMouse;
	SDL_Event event;
	while(current_context->IsValid()){
	
		SDL_Delay(20);
		
		while( SDL_PollEvent( &event ))
		{
			switch (event.type) 
			{
				case SDL_QUIT :
					current_context->Quit();
					std::cout << "exit input thread" << std::endl;
					return 0; 
					break;
				
				case SDL_MOUSEMOTION:
				    current_context->SetMouseCoords();
				
				case SDL_KEYDOWN:
				   camera->debuginput(event);
				    break;
				
				case SDL_KEYUP:
				    camera->debuginput(event);;
				    break;
			}
		}
		float x, y;
		current_context->GetMouseCoords(x,y);
		camera->Mouse2Look(x,y);	
		
	}
	
	return 0 ;
}



int main()
{
	
	Context* test = new Context(960,720, "Test");
	Drawer3d* drawer= new Drawer3d();
	Gui* orientation = new Gui();
	Camera* camera = new Camera();
	
	Asset zero;
	zero.LoadObj("./assets/houseplant3.obj");
	zero.LoadTexture("./assets/plant.tga");	
	
	Shader vertex3d("./shaders/vertexshader.3d", GL_VERTEX_SHADER);
	Shader fragment3d("./shaders/fragmentshader.3d", GL_FRAGMENT_SHADER);
	
	Shader orv("./shaders/orv.3d", GL_VERTEX_SHADER);
	Shader orf("./shaders/orf.3d", GL_FRAGMENT_SHADER);
	
	fragment3d.Compile();
	vertex3d.Compile();
	
	orv.Compile();
	orf.Compile();
	
	orientation->LoadShaders(&orv, &orf);
	drawer->LoadShaders(&vertex3d, &fragment3d);
	
	orientation->LoadShaders(&orv,&orf);
	

	std::thread HandleInput(InputLoop,test, camera);
	std::thread HandleWorld(WorldLoop,test,camera );
	GraphicLoop(test,  drawer, orientation, &zero, camera );
	std::cout << "exit1 " << std::endl;
	HandleInput.join();
	std::cout << "exit2 " << std::endl;
	HandleWorld.join();
	std::cout << "exit3 " << std::endl;
	
	
	delete drawer;
	delete test;
	delete orientation;
	delete test;
	
	return 0;
}
