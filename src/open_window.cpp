#define STB_IMAGE_IMPLEMENTATION


#include <thread> 

#include <turtle.h>
#include "./drawers/drawer3d.h"
#include "./drawers/orientation.h"
#include "./drawers/terrain.h"
#include "game.cpp"


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

int GraphicLoop(Context* current_context, Drawer3d* drawer, Gui * orientation, Terrain *terrain, GameObj3d* zero, Camera* camera)
{	
		float x,y,z;
		//Drawer3d* drawer1=  dynamic_cast<Drawer3d*>(drawer);
		drawer->SetModel(*zero);
		while(current_context->IsValid())
		{
			current_context->StartFrame();
		
			
			glClearColor( 0.2f, 0.f, 0.f, 0.1f );
			//asset->Rotate();
			
			
			
			drawer->Draw(zero->GetAsset(), camera);
			orientation->Draw(camera);
			terrain->Draw(camera);
			    ImGui_ImplOpenGL3_NewFrame();
		    ImGui_ImplSDL2_NewFrame(current_context->GetWindow());
		    ImGui::NewFrame();
		    ImGui::Begin("Hello, world!");                          
		    ImGui::Text("This is some useful text.");  
		    ImGui::InputFloat("x ", &x, 0.01f, 1.0f, "%.3f"); 
		    ImGui::InputFloat("y ", &y, 0.01f, 1.0f, "%.3f"); 
		    ImGui::InputFloat("z ", &z, 0.01f, 1.0f, "%.3f");         
		    ImGui::End();
	            ImGui::Render();
	            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	            zero->SetRot(x,y,z);
		
			
			
			
			current_context->EndFrame();
		}
		std::cout << "exit graphic thread" << std::endl;
		
return 0;

}



int InputLoop(Context* current_context, Camera* camera)
{	
	GameInput(current_context,camera);
	return 0 ;
}



int main()
{
	
	Context* test = new Context(960,720, "Test");
	Drawer3d* drawer= new Drawer3d();
	Gui* orientation = new Gui();
	Camera* camera = new Camera();
	Terrain * terrain = new Terrain();
	
	terrain->LinkVerts();
	
	GameObj3d zero("./assets/houseplant3.obj","./assets/plant.tga", "plant0");
	
	Shader vertex3d("./shaders/vertexshader.3d", GL_VERTEX_SHADER);
	Shader fragment3d("./shaders/fragmentshader.3d", GL_FRAGMENT_SHADER);
	
	Shader orv("./shaders/orv.3d", GL_VERTEX_SHADER);
	Shader orf("./shaders/orf.3d", GL_FRAGMENT_SHADER);
	
	Shader terrainv("./shaders/terrainv.3d", GL_VERTEX_SHADER);
	Shader terrainf("./shaders/terrainf.3d", GL_FRAGMENT_SHADER);
	
	fragment3d.Compile();
	vertex3d.Compile();
	
	terrainv.Compile();
	terrainf.Compile();
	
	orv.Compile();
	orf.Compile();
	
	orientation->LoadShaders(&orv, &orf);
	drawer->LoadShaders(&vertex3d, &fragment3d);
	terrain->LoadShaders(&terrainv,&terrainf);
	orientation->LoadShaders(&orv,&orf);
	

	std::thread HandleInput(InputLoop,test, camera);
	std::thread HandleWorld(WorldLoop,test,camera );
	GraphicLoop(test,  drawer, orientation, terrain, &zero, camera );
	std::cout << "exit1 " << std::endl;
	HandleInput.join();
	std::cout << "exit2 " << std::endl;
	HandleWorld.join();
	std::cout << "exit3 " << std::endl;
	
	
	delete drawer;
	delete orientation;
	delete test;
	
	return 0;
}
