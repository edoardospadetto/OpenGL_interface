#include <turtle.h> 


Editor::Editor(Context * context_, std::string&& gsls_version) : context(context_)
{

   // const char* glsl_version = "#version 330";
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsClassic();
    ImGui_ImplSDL2_InitForOpenGL(context->GetWindow(), context->GetSDLGLcontext());
    ImGui_ImplOpenGL3_Init(gsls_version.c_str());
    
    //context->SetViewPort(100,100, 400, 400);


}

void Editor::EditObjModel(GameObj3d * obj)
{	
	 float rot[3]={},pos[3]={} ,scale[3]={};
	 for (int i = 0; i<3; i++)
	 {
	 	rot[i] = *(obj->GetRot()+i);
	 	pos[i] = *(obj->GetPos()+i);
	 	scale[i] = *(obj->GetScale()+i);
	 }
	 

	
	 ImGui::Begin("Edit");  

	   	
	 ImGui::InputFloat("rot X ", &(rot[0]), 0.01f, 1.0f, "%.3f"); 
	 ImGui::InputFloat("rot Y ", &(rot[1]), 0.01f, 1.0f, "%.3f"); 
	 ImGui::InputFloat("rot Z ", &(rot[2]), 0.01f, 1.0f, "%.3f");
	 
	 ImGui::InputFloat("x ", &(pos[0]), 0.01f, 1.0f, "%.3f"); 
	 ImGui::InputFloat("y ", &(pos[1]), 0.01f, 1.0f, "%.3f"); 
	 ImGui::InputFloat("z ", &(pos[2]), 0.01f, 1.0f, "%.3f");
	 
	 ImGui::InputFloat("scale X ", &(scale[0]), 0.01f, 1.0f, "%.3f"); 
	 ImGui::InputFloat("scale Y ", &(scale[1]), 0.01f, 1.0f, "%.3f"); 
	 ImGui::InputFloat("scale Z ", &(scale[2]), 0.01f, 1.0f, "%.3f");
	 
	    
	 ImGui::End();

	 //ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	 
	 obj->SetRot(rot[0],rot[1],rot[2]);
	 obj->SetPos(pos[0],pos[1], pos[2]);
	 obj->SetScale(scale[0],scale[1],scale[2]);
}

void Editor::WatchFrom(GameObj3d * obj, Camera * camera)
{


	 ImGui::Begin("View");  
	 
	
        ImGui::RadioButton("x", &watchfromcase, 0); ImGui::SameLine();
        ImGui::RadioButton("y", &watchfromcase, 1); ImGui::SameLine();
        ImGui::RadioButton("z", &watchfromcase, 2); ImGui::SameLine();
        ImGui::RadioButton("free", &watchfromcase, 3);
        
         ImGui::End();

        switch( watchfromcase ) 
        {
        	case 0:
        		camera->SetPosition(-5,0,0);
        		camera->SetLook(1,0,0);
        		break;
        	case 1 : 
        		camera->SetPosition(0,-5,0);
        		camera->SetLook(0,1,0);
        		break;
        	case 2 :
        		camera->SetPosition(0,0,-5);
        		camera->SetLook(0,0.001,+1);
        		break;
	}	
	


}
void Editor::StartFrame()
{
 	ImGui_ImplOpenGL3_NewFrame();
         ImGui_ImplSDL2_NewFrame(context->GetWindow());
         ImGui::NewFrame();
         
}
void Editor::EndFrame()
{
	
	 ImGui::Render();
	 ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Editor::Dot()
{
	float x,y ;
	int w, h;
	glColor3f(1.0f, 0.0f, 0.0f);
	context->GetMouseCoords(x,y); //
	context->GetWindowSize(w,h);
	std::cout << x << "   " << y << std::endl;
	x =  x*2.0f*orthox; 
	y =  y*2.0f*orthoy;
	

	glBegin(GL_POINTS);
	glPointSize(0.5);
	glVertex3f(x,0.5,y);
	glColor3f(0.0f, 0.0f, 0.0f);
	glEnd();
}

Editor::~Editor()
{
	ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();

}


