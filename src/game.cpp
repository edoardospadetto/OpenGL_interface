int GameInput(Context* current_context, Camera* camera)
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
				    
				case SDL_MOUSEBUTTONDOWN:
				  	current_context->SetMouseButton(event.button);
				
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
	return 0;
	
}
