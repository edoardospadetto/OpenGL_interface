#include <turtle.h> 


Editor::Editor(Context * context_, Camera * camera_ , std::string&& vshpath, std::string&& fshpath, std::string&& gsls_version) : context(context_), camera(camera_)
{

   // const char* glsl_version = "#version 330";
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui_ImplSDL2_InitForOpenGL(context->GetWindow(), context->GetSDLGLcontext());
    ImGui_ImplOpenGL3_Init(gsls_version.c_str());
    ImGui::StyleColorsClassic();
    context->Bind(this);
    EditorProgram = glCreateProgram();
    EditorVertex.Build(std::move(vshpath), GL_VERTEX_SHADER);
    EditorFragment.Build(std::move(fshpath), GL_FRAGMENT_SHADER);
    
    EditorVertex.Compile();
    EditorFragment.Compile();
    
    glAttachShader( EditorProgram , EditorVertex.GetId());
    glAttachShader( EditorProgram , EditorFragment.GetId());
    
    glLinkProgram( EditorProgram );
    
    GLint status = GL_FALSE;
    glGetProgramiv( EditorProgram, GL_LINK_STATUS, &status );
    
    if( status != GL_TRUE )
    {
	printf( "Error linking Editor Shader %d!\n",EditorProgram);
    }
    
    selected_point = 0;
    //context->SetViewPort(100,100, 400, 400);
    //set tools
    //rigger()
    
    


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

void Editor::WatchFrom(GameObj3d * obj)
{

	int t_= watchfromcase;
	 ImGui::Begin("View");  
	 
	
        ImGui::RadioButton("x", &watchfromcase, 0); ImGui::SameLine();
        ImGui::RadioButton("y", &watchfromcase, 1); ImGui::SameLine();
        ImGui::RadioButton("z", &watchfromcase, 2); ImGui::SameLine();
        ImGui::RadioButton("free", &watchfromcase, 3);
        
        ImGui::End();
	if(t_ != watchfromcase){
		camera->Design();
		camera->Prisoner();
		switch( watchfromcase ) 
		{
			case 0:
				camera->SetPosition(+5,0,0);
				camera->SetLook(-1,0,0);
				break;
			case 1 : 
				camera->SetPosition(0,+5,0);
				camera->SetLook(0,-1,0);
				break;
			case 2 :
				camera->SetPosition(0,0,+5);
				camera->SetLook(0,0.001,-1);
				break;
			case 3 : 
				camera->Free();
				camera->Panorama();
		}	
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
{	if(points.size() >0)
	{
	// DRAW EDGES 
	GLuint pos, col, view;
	
	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
	
	glUseProgram(EditorProgram);
	glBindBuffer(GL_ARRAY_BUFFER, evbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eibo );
	glPointSize(5.0);
	view = glGetUniformLocation( EditorProgram , "sview" );
	pos = glGetAttribLocation( EditorProgram , "pos" ); 
	col = glGetAttribLocation( EditorProgram , "col" );
	  
	glUniformMatrix4fv(view,1, false,  camera->GetViewMatrix() );
	glVertexAttribPointer( pos, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0  );	 
	glVertexAttribPointer( col, 3, GL_FLOAT, GL_TRUE, 6 * sizeof(float), (void*)(3*sizeof(float)) );
	
	glBufferData( GL_ARRAY_BUFFER, points.size()*sizeof(float) , (float*) &(points[0]), GL_DYNAMIC_DRAW );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, parents.size()*sizeof(int) , &(parents[0]), GL_DYNAMIC_DRAW );
	  
	glEnableVertexAttribArray( pos);
	glEnableVertexAttribArray( col);
	
	glDrawElements( GL_LINE_STRIP, parents.size() , GL_UNSIGNED_INT, NULL );
	
	glEnableVertexAttribArray( pos);
	glEnableVertexAttribArray( col);
	
	
	
	
	
	
	// DRAW DOTS
	//mouse 
	
	float x,y ;
	int w, h;
	
	context->GetMouseCoords(x,y);
	x=x*2*orthox;
	y=y*2*orthoy;
	
	if(edit_points )
	{
		points[selected_point*6+3] = 0.0;
		points[selected_point*6+4] = 1.0;
		points[selected_point*6+5] = 0.0;
		
	switch( watchfromcase ) 
	{
		case 0:
			
			
			
			points[selected_point*6+1] = x;
			points[selected_point*6+2] = y;
			
			
			break;
		case 1:
			
			points[selected_point*6+0] = -x;
			
			points[selected_point*6+2] = y;
			
			
			break;
		case 2:
			
			
			points[selected_point*6+0] = x;
			points[selected_point*6+1] = y;
			
			
			break;
	}
	}	
	
	 //

	
	

	  

	
	glEnableVertexAttribArray( pos);
	glEnableVertexAttribArray( col);
	
	
	
	
	glDrawArrays( GL_POINTS, 0 , points.size()/6 );
	
	glDisableVertexAttribArray( pos);
	glDisableVertexAttribArray( col);
	
	 //Erase mouse point
	 for (int i=0; i<parents.size() ; i++)
	 {
	 std::cout << i << "  "<<  parents[i] << std::endl;
	 }
	 std::cout << std::endl;
	}
	
}

void Editor :: RiggerWindow()
{
	 ImGui::Begin("Rigger"); 
	 ImGui ::Checkbox("edit", &edit_points); ImGui::SameLine();
	 ImGui::InputInt("selected point", &selected_point); 
	 
	 
	 //point, color 6 entries, parents two entries
	 if( ImGui::Button("Add point") )
	 {
	 	for (int i=0; i<6; i++) {points.push_back(0.0);}
	 	points[points.size()-2] = 1.0f;
	 	selected_point = points.size()/6-1;
	 	parents.push_back(points.size()/6-1);
	 	parents.push_back(points.size()/6-1);
	 	//parents.push_back(points.size()/6);
	 }
	 
	 if( ImGui::Button("Delete this point") )
	 {
	 points.erase (points.begin()+selected_point, 
	 		points.begin()+selected_point+6 ) ;
	 parents.erase(parents.begin()+selected_point);
	 }
	 	
	 
	 
	 if(selected_point < points.size()/6 )
	 {
		 ImGui::InputFloat("X ", &(points[selected_point*6]), 0.01f, 1.0f, "%.3f"); 
		 ImGui::InputFloat("Y ", &(points[selected_point*6+1]), 0.01f, 1.0f, "%.3f"); 
		 ImGui::InputFloat("Z ", &(points[selected_point*6+2]), 0.01f, 1.0f, "%.3f");
		 ImGui::InputInt("parent", &(parents[selected_point+2]));
		 
	 }
	 else {selected_point = points.size()/6 ;}
	 
	 
	 ImGui::End();
}

void Editor :: EditRiggerPoint()
{	

	float x,y;
	context->GetMouseCoords(x,y);
	x = x*2*orthox;
	y = y*2*orthoy;
	if(points.size() <= 0 ) edit_points = false;
	//std::cout << x << "  " << y<<  "  " << std::endl;
	if(edit_points)
	{	
		points[selected_point*6+3] =0.0;
		points[selected_point*6+4] =0.0;
		points[selected_point*6+5] =1.0;
		switch( watchfromcase ) 
		{	
			
			
			case 0:
			edit_points = false;
			points[selected_point*6+1] =x;
			points[selected_point*6+2] =y;
			break;
			case 1:
			edit_points = false;
			points[selected_point*6+0] =x;
			points[selected_point*6+2] =y;
			break;
			case 2:
			edit_points = false;
			points[selected_point*6+0] =x;
			points[selected_point*6+1] =y;
			break;
		}	
	}


}

Editor::~Editor()
{
	
	ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();

}





