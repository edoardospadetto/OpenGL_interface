#include "turtle.h"


# define M_PI           3.14159265358979323846

float getAngle(const glm::vec3 & A, const glm::vec3 & B )
{
	glm::vec3 crossp = glm::cross(A,B);
	float anglec=glm::dot(A,B);
	float angles = glm::l2Norm(crossp) ;
	float angle;
	
	if( anglec < M_PI*0.5 )
	{
		angle = angles;
		/*if(angles < 0)
		{
			angle = 2* M_PI - angles;
		}*/
	}
	else if( anglec >= M_PI*0.5 )
	{
		angle = M_PI -angles;
	}
	return angle;
}
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
	
	look*= 1/glm::l2Norm(look);
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
	
	view = glm::lookAt(position, look+position, glm::vec3(0,0,1) );
	
	half = glm::translate(view, +position);
	
	if(design)
	{
		projection = glm::ortho(-orthox,orthox,-orthoy,orthoy,0.1f,50.0f);
	}
	else
	{
		projection = glm::perspective(45.0f, 1.3f, 50.0f, 0.1f);
	}
	
	view = projection*view;
	

	
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
	if(free)
	{
	float delta = glm::sign(x);
	
	if(std::abs(x)>0.2) yaw+=delta;
	
	
	delta = glm::sign(y);
	
	if(std::abs(y)>0.2) pitch += delta;
	
		
	if(pitch >= 89.5f)
	  pitch =  89.5f;
	if(pitch <= -89.5f)
	  pitch = -89.5f;

	look.x= std::cos(glm::radians(yaw)) * std::cos(glm::radians(pitch));
	look.y= std::sin(glm::radians(yaw)) * std::cos(glm::radians(pitch));
	look.z= std::sin(glm::radians(pitch));
	}
	
	
}


void Camera::debuginput(SDL_Event e)
{
	float speed= 0.0; 
	
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
	if(!free)
	{	
		
		orthox += speed*0.2;
		orthoy += speed*0.2;

		move = false;
		speed = 0;
	}
	
	
	
		
		

}

void Camera::Design() {design = true;}
void Camera::Panorama() {design = false;}

void Camera::Move()
{
	if(move)
	{
		position.x += speed*0.2*look.x;
		position.y += speed*0.2*look.y;
		position.z += speed*0.2*look.z;
	
	}

}

void Camera::Free(){free = true;}
void Camera::Prisoner(){free = false;}
