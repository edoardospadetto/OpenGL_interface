#include "turtle.h"


# define M_PI           3.14159265358979323846


Camera::Camera() 
{
	view = glm::mat4(1.0);

	
	look.x=0.0;
	look.y=1.0;
	look.z=0.0;
	UpdateViewMatrix();
}

void Camera::SetPosition(float x, float y , float z)
{
	position.x=x;
	position.y=y;
	position.z=z;

}

void Camera::SetLook(float vx, float vy , float vz)
{
	look.x=vx;
	look.y=vy;
	look.z=vz;
}

glm::vec3 * Camera:: GetPosition()
{
	return &position;
	
}
	
glm::vec3 * Camera:: GetLook()
{
	return &look;

}

void Camera::UpdateViewMatrix()
{
	// i want to rotate to  look to become (0,1,0)
	float angle = glm::acos(glm::dot( look , glm::vec3(0.0,1.0,0.0))) ;//* 180.00/M_PI;
	if(angle !=0.0){
		glm::vec3 rot_axis = glm::normalize(glm::vec3(-look.z/look.x, 0, 1));
	
		view = glm::rotate(-angle,rot_axis);
	}
	else view = glm::mat4(1.0);

	/*for (int i=0; i<4; i++)
	{
		for (int j=0; j<4; j++)
		{
			std::cout << view[i][j] << "  " ; 
		}
		std::cout << std::endl;
	}*/
	//std::cout << std::endl;
	half = view;
	view = glm::translate(view, -position);
	
	//view = glm::lookAt   ( position, look , glm::vec3(0,0,1));

	
}


float* Camera::GetViewMatrix()
{
	return &(view[0][0]);
}


float* Camera::GetHalfMatrix()
{
	return &(half[0][0]);
}



void Camera::Mouse2Look(float x, float y)
{
	float delta = 0.01*glm::sign(x);
	
	if(std::abs(x)>0.2)
	{
		look.x = std::cos(delta)*look.x - std::sin(delta)*look.y;
		look.y = + std::sin(delta)*look.x + std::cos(delta)*look.y; 
		
	}
	float front = std::sqrt(std::pow(look.x,2)+std::pow(look.y,2));
	delta =- 0.01*glm::sign(y);
	if(std::abs(y)>0.2)
	{
		front = std::cos(delta)*front - std::sin(delta)*look.z;
		look.z =  std::sin(delta)*front + std::cos(delta)*look.z; 
		
		//look.x= std::cos(delta)*look.x+std::sin(delta)*pow(look.z,2)*look.x;
		//look.y= std::cos(delta)*look.y+std::sin(delta)*pow(look.z,2)*look.y;
	}
	
	
	/*look.x *= 1.0/std::sqrt(std::pow(look.x,2)+std::pow(look.y,2)+std::pow(look.z,2));
	look.y *= 1.0/std::sqrt(std::pow(look.x,2)+std::pow(look.y,2)+std::pow(look.z,2));
	look.z *= 1.0/std::sqrt(std::pow(look.x,2)+std::pow(look.y,2)+std::pow(look.z,2));
	*/
	UpdateViewMatrix();
	
	std::cout << look.x << "      " << look.y  << "     "<< look.z << "     " << delta  <<   std::endl;

}


void Camera::debuginput(SDL_Event e)
{
	switch(e.type)
	{
		case SDL_KEYDOWN : 
			switch(e.key.keysym.sym)
        		{
			    case SDLK_w:
			        move = true;
				speed = 0.5;
				break;
			    
			     case SDLK_s:
			    	move = true;
				speed = -0.5;
				break;
			 }
		break;
		case SDL_KEYUP : 
			switch(e.key.keysym.sym)
        		{
			    case SDLK_w:
			    
				move = false;
			    	break;
			     case SDLK_s:
			    
				move = false;
				break;
			 }
		break;
	}
	
	
		
		

}

void Camera::Move()
{
	if(move)
	{
		position.x += speed*0.2*look.x;
		position.y += speed*0.2*look.y;
		position.z += speed*0.2*look.z;
	
	}


}
