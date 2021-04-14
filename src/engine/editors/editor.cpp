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
    drawrigprocess.Init();
    
    


}

void Editor::Handle(GameObj3d * obj)
{
	
	drawrigprocess.LoadAsset(obj->GetAsset());

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
	 
	 drawrigprocess.Draw(obj, camera);
	 
	
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
	for(int i=0; i< points.size()/6; i++)
	{	
		points[6*i+3] = 0.0;
		points[6*i+4] = 0.0;
		points[6*i+5] = 1.0;
	}
	
	glGenBuffers(1, &evbo);
	glGenBuffers(2, &eibo);
	//std::cout << points.size() << " "  << parents.size() << std::endl;
	GLuint pos, col, view;
	
	glClear(GL_DEPTH_BUFFER_BIT);
	//glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
	
	glLineWidth(5.0);
	glPointSize(12.0);
	
	glUseProgram(EditorProgram);
	glBindBuffer(GL_ARRAY_BUFFER, evbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eibo );
	
	
	
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
	glGetError();
	//glDrawArrays( GL_LINES, 0 , points.size()/6 );
	
	glDrawElements( GL_LINES, parents.size() , GL_UNSIGNED_INT, NULL );
	
	glEnableVertexAttribArray( pos);
	glEnableVertexAttribArray( col);
	
	
	
	for(int i=0; i< points.size()/6; i++)
	{	
		points[6*i+3] = 1.0;
		points[6*i+4] = 0.3;
		points[6*i+5] = 0.3;
	}
	
	
	// DRAW DOTS
	//mouse 
	
	float x,y ;
	int w, h;
	
	context->GetMouseCoords(x,y);
	x=x*2*orthox;
	y=y*2*orthoy;
	
	//Edit Points
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

	glBufferData( GL_ARRAY_BUFFER, points.size()*sizeof(float) , (float*) &(points[0]), GL_DYNAMIC_DRAW );
	

	glClear(GL_DEPTH_BUFFER_BIT);

	
	glEnableVertexAttribArray( pos);
	glEnableVertexAttribArray( col);
	
	glDrawArrays( GL_POINTS, 0 , points.size()/6 );
	
	glDisableVertexAttribArray( pos);
	glDisableVertexAttribArray( col);
	
	
	//PaintClusters
	if(paint_cluster)
	{
	
		
		float square[4*6] = {0.0};
		int wherex, wherey;
		
		switch( watchfromcase ) 
		{	
		case 0:
			wherex = 1;
			wherey = 2;
			break;
		case 1:
			wherex = 0;
			wherey = 2;
			break;
		case 2:
			wherex = 0;
			wherey = 1;
			break;
		}
		
		for (int i = 0; i<4 ; i++ )
		{
			square[6*i+3] = 0.0;
			square[6*i+4] = 1.0;
			square[6*i+5] = 0.0;
		}
		for (int i = -2; i<+2 ; i++ )
		{
			square[ 6*(i+2) + wherex ] = 0.05*orthox*(2*floor(abs((i+0.5)))-1) + x;
			square[ 6*(i+2) + wherey ] = 0.05*orthoy*( (i+0.5)/abs(i+0.5) ) + y;
			
		}
		
		glClear(GL_DEPTH_BUFFER_BIT);
		glBufferData( GL_ARRAY_BUFFER, 4*6*sizeof(float) , (float*) &(square[0]), GL_DYNAMIC_DRAW );
				
		glEnableVertexAttribArray( pos);
		glEnableVertexAttribArray( col);
		
		glDrawArrays( GL_LINE_LOOP , 0 , 4 );
		
		glDisableVertexAttribArray( pos);
		glDisableVertexAttribArray( col);
	

					
	}
	
	}
	
}

void Editor :: RiggerWindow()
{
	 ImGui::Begin("Rigger"); 
	 ImGui ::Checkbox("edit", &edit_points); ImGui::SameLine();
	 ImGui::InputInt("selected point", &selected_point); 
	 ImGui ::Checkbox("fix", &fix_point); ImGui::SameLine();
	 ImGui ::Checkbox("paint cluster", &paint_cluster);
	 if(!fix_point)
	 {
	 	fixed_points = points;
	 	once_weights = true;
	 	
	 }
	 

	 
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
		 ImGui::InputInt("parent", &(parents[2*selected_point+1]));
		 
	 }
	 else {selected_point = points.size()/6 ;}
	 
	 
	 ImGui::End();
}

void Editor :: EditRiggerPoint()
{	

	float x,y;
	camera->GetOrtho(&orthox, &orthoy);
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

float norm(float x, float y, float z)
{
	return std::sqrt(x*x+y*y+z*z);
}


void Editor::FromParent()
{	
	distances.clear();
	for (int i = 0 ; i<parents.size()/2 ; i++)
	{
			
			
		distances.push_back(norm( points[6*i+0]-points[6*parents[2*i+1]+0],
					   points[6*i+1]-points[6*parents[2*i+1] +1], 
					   points[6*i +2]-points[6*parents[2*i+1] +2] ));	
			
		
		
	}

}
//correct
void Editor::NodesHierarchy()
{
	std::vector<int> nodes_at_level;
	
	for (int i = 0 ; i<parents.size()/2 ; i++)
	{
		if(parents[2*i] == parents[2*i+1])
		{	
			parents[2*i+1] = -parents[2*i+1]-1;
			nodes_at_level.push_back(parents[2*i]);	
			
		
		}
	}
	
	
	while(nodes_at_level.size() > 0)
	{
		std::vector<int> temp;
	
		for (int i = 0 ; i<parents.size()/2 ; i++)
		{	for (int j = 0 ; j<nodes_at_level.size() ; j++)
			{
				//std::cout << nodes_at_level[j] << "  ";
				if(parents[2*i+1] == nodes_at_level[j])
				{
					temp.push_back(parents[2*i]);	
	
				}
			}
			//std::cout << std::endl;
		}
		nodes_at_level = temp;
	}
}

void Editor::FindNearest(GameObj3d *obj)
{
	int vals = 8;
	for (int i =0; i<obj->asset->vertnum; i++)
		{
			//compute weights 
			float nearest= norm(obj->asset->buffer[vals*i+0] -points[0], 
					     obj->asset->buffer[vals*i+1] -points[1],
					     obj->asset->buffer[vals*i+2] -points[2] ); 
					  
			int nearest_idx = 0;
			
			for (int j = 0; j <points.size()/6; ++j)
			{
				if(nearest >= norm(obj->asset->buffer[vals*i+0] -fixed_points[6*j], 
						   obj->asset->buffer[vals*i+1] -fixed_points[6*j+1],
						   obj->asset->buffer[vals*i+2] -fixed_points[6*j+2]))
				{
					nearest =  norm(obj->asset->buffer[vals*i+0] -fixed_points[6*j], 
						   obj->asset->buffer[vals*i+1] -fixed_points[6*j+1],
						   obj->asset->buffer[vals*i+2] -fixed_points[6*j+2]);
					nearest_idx = j;
				}	
			}
			 
			nearest_node.push_back(nearest_idx);
			
			drawrigprocess.buffer[i*6+3] = drawrigprocess.colors[(nearest_idx%8)*3]; 
			drawrigprocess.buffer[i*6+4] = drawrigprocess.colors[(nearest_idx%8)*3+1];
			drawrigprocess.buffer[i*6+5] = drawrigprocess.colors[(nearest_idx%8)*3+2];
			/*std::cout << "doin " << nearest_idx % 8<<" "<< drawrigprocess.buffer[i*6+3] << 
			" " << drawrigprocess.buffer[i*6+4] << 
			" " << drawrigprocess.buffer[i*6+5] << std::endl;*/
		
		
		}
}

void Editor::MoveSkeleton(GameObj3d *obj)
{
	
	int vals = 8;
	if(fix_point)
	{	std::vector<float> angle;
		glm::vec3 olddir, newdir;
	
		if(once_weights)
		{
			FromParent();
			once_weights = false;
			FindNearest(obj);
		}
		
		std::vector<float> deltas;
		for(int i=0; i<points.size()/6 ; i++)
		{	
			if( parents[2*i] != i ) printf("Error\n");
			float normtmp = norm( points[6*i +0]-points[6*parents[2*i+1]+0],
					      points[6*i +1]-points[6*parents[2*i+1]+1], 
					      points[6*i +2]-points[6*parents[2*i+1]+2]);
			float fromparent[3] = {
					        points[6*i +0]-points[6*parents[2*i+1]+0],
					        points[6*i +1]-points[6*parents[2*i+1]+1], 
					        points[6*i +2]-points[6*parents[2*i+1]+2]
						
						};
			float fromparent_old[3] = {
				        fixed_points[6*i +0]-points[6*parents[2*i+1]+0],
				        fixed_points[6*i +1]-points[6*parents[2*i+1]+1], 
				        fixed_points[6*i +2]-points[6*parents[2*i+1]+2]
					
					};
						
			newdir = glm::vec3(fromparent[0],fromparent[1], fromparent[2]);
			
			olddir = glm::vec3(fromparent_old[0],fromparent_old[1], fromparent_old[2]);
			
			if(parents[2*i+1]!=parents[2*i])
			{
				newdir *= 1.0 / glm::l2Norm(newdir);
				olddir *= 1.0 / glm::l2Norm(olddir);
			}
			switch(watchfromcase)
			{
				case 0: 
					angle.push_back(glm::orientedAngle(newdir,olddir,glm::vec3(1.0,0.0,0.0)));
				break;
				case 1: 
					angle.push_back(glm::orientedAngle(newdir,olddir,glm::vec3(0.0,1.0,0.0)));
				break;
				case 2: 
					angle.push_back(glm::orientedAngle(newdir,olddir,glm::vec3(0.0,0.0,1.0)));
				break;
			}
 			 //glm::vec3(float(watchfromcase == 0 ), float(watchfromcase == 1 ), float(watchfromcase == 2 ))));
			
			//std::cout << "vecs "  << newdir.x  << "  "<< newdir.y  << "  "<<  newdir.z << " " <<  glm::l2Norm(newdir) << std::endl;
			//std::cout << "vecs "  << olddir.x  << "  "<< olddir.y  << "  "<<  olddir.z << " " <<  glm::l2Norm(olddir) << std::endl;
			//std::cout << angle[angle.size()-1] << "  " << std::endl;
			//glm::vec3 newpoint = glm::vec3() 
			
			/*printf("%f %f %f, %f %f %f\n" , points[6*i +0],points[6*parents[2*i+1]+0],
					      points[6*i +1],points[6*parents[2*i+1]+1], 
					      points[6*i +2],points[6*parents[2*i+1]+2]); 
					      
			std::cout << normtmp << "  " << distances[i] << " " << i << "  " << parents[2*i+1]  << std::endl;*/
			
			if(normtmp >= 1e-3)
			{
				points[6*i+0] = points[6*parents[2*i+1]+0]+fromparent[0]*distances[i]/normtmp;
				points[6*i+1] = points[6*parents[2*i+1]+1]+fromparent[1]*distances[i]/normtmp;
				points[6*i+2] = points[6*parents[2*i+1]+2]+fromparent[2]*distances[i]/normtmp;
			}
			deltas.push_back( points[6*i]-fixed_points[6*i] );
			deltas.push_back( points[6*i+1]-fixed_points[6*i+1] );
			deltas.push_back( points[6*i+2]-fixed_points[6*i+2] );
			
			
		}
		
		
		for (int i =0; i<obj->asset->vertnum; i++)
		{	if(parents[2*nearest_node[i]+1]!=parents[2*nearest_node[i]])
			{
			glm::vec3 tmp_father = glm::vec3(points[parents[2*nearest_node[i]+1]],points[parents[2*nearest_node[i]+1]+1],points[parents[2*nearest_node[i]+1]+2]);
			//glm::vec3 temp = glm::vec3(obj->asset->buffer[vals*i+0],obj->asset->buffer[vals*i+1],obj->asset->buffer[vals*i+2]) -tmp_father;
			glm::vec3 temp = glm::vec3(drawrigprocess.buffer[6*i+0],drawrigprocess.buffer[6*i+1],drawrigprocess.buffer[6*i+2]);
			
			switch(watchfromcase)
			{
				case 0: 
					temp = glm::rotateX(temp, angle[nearest_node[i]]);
				break;
				
				case 1: 
					temp = glm::rotateY(temp, angle[nearest_node[i]]);
				break;
				
				case 2: 
					temp = glm::rotateZ(temp, angle[nearest_node[i]]);
				break;
			}
			//glm::vec3(float(watchfromcase == 0 ), float(watchfromcase == 1 ), float(watchfromcase == 2 ) ));
			//obj->asset->buffer[vals*i+0] = tmp_father.x+temp.x;//deltas[3*nearest_node[i]+0];
			//obj->asset->buffer[vals*i+1] = tmp_father.y+temp.y;//deltas[3*nearest_node[i]+1];  
			//obj->asset->buffer[vals*i+2] = tmp_father.z+temp.z;//deltas[3*nearest_node[i]+2];
			
			drawrigprocess.buffer[6*i+0] = tmp_father.x+temp.x;
			drawrigprocess.buffer[6*i+1] = tmp_father.y+temp.y;
			drawrigprocess.buffer[6*i+2] = tmp_father.z+temp.z;
			}
		
		
		}
		fixed_points = points;
	}	
}

void Editor::PaintCluster()
{
	if(paint_cluster)
	{
		float x,y ;
		context->GetMouseCoords(x,y);
		x=x*2*orthox;
		y=y*2*orthoy;
		
		float square[4*6] = {0.0};
		int wherex, wherey;
		
		switch( watchfromcase ) 
		{	
		case 0:
			wherex = 1;
			wherey = 2;
			break;
		case 1:
			wherex = 0;
			wherey = 2;
			break;
		case 2:
			wherex = 0;
			wherey = 1;
			break;
		}
		
		
	
		for(int i = 0; i<drawrigprocess.numvert ; i++)
		{	
			if( (abs(drawrigprocess.buffer[6*i+wherex]-x) <= 0.05*orthox) &
			    (abs(drawrigprocess.buffer[6*i+wherey]-y) <= 0.05*orthoy)  )
			    {
			    	nearest_node[i] = selected_point;
			    }
			drawrigprocess.buffer[i*6+3] = drawrigprocess.colors[(nearest_node[i]%8)*3]; 
			drawrigprocess.buffer[i*6+4] = drawrigprocess.colors[(nearest_node[i]%8)*3+1];
			drawrigprocess.buffer[i*6+5] = drawrigprocess.colors[(nearest_node[i]%8)*3+2];
		
		}
	
	}
	
}

