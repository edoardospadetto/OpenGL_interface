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
	
	//projection = glm::perspective(45.0f, 1.3f, 50.0f, 0.1f);
	projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.1f,50.0f);
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
	float delta = glm::sign(x);
	
	//std::cout << glm::sign(x) << std::cos(delta) << std::sin(delta)  << std::endl;
	
	if(std::abs(x)>0.2)
	{
		//look.x = std::cos(delta)*look.x - std::sin(delta)*look.y;
		//look.y = + std::sin(delta)*look.x + std::cos(delta)*look.y;
		yaw+=delta;
		//look = glm::rotateZ(look, delta); 
		
	}
	float front = std::sqrt(std::pow(look.x,2)+std::pow(look.y,2));
	delta = glm::sign(y);
	
	if(std::abs(y)>0.2)
	{
		//front = std::cos(delta)*front - std::sin(delta)*look.z;
		//look.z =  std::sin(delta)*front + std::cos(delta)*look.z; 
		pitch += delta;
		//glm::vec3 hori_tmp = glm::cross(look, glm::vec3(0,0,1));
		//if(glm::l2Norm(hori_tmp) > 0.1)
		//{
		//	horizon = hori_tmp/glm::l2Norm(hori_tmp);
		//}
		if(pitch >= 90.0f)
		  pitch =  90.0f;
		if(pitch <= -90.0f)
		  pitch = -90.0f;
		//look = glm::rotate(look, delta, horizon);
		//look.x= std::cos(delta)*look.x+std::sin(delta)*pow(look.z,2)*look.x;
		//look.y= std::cos(delta)*look.y+std::sin(delta)*pow(look.z,2)*look.y;
		//std::cout << horizon.x << "      " << horizon.y  << "     "<< horizon.z << "     " << delta  <<   std::endl;
	}
	
	look.x= std::cos(glm::radians(yaw)) * std::cos(glm::radians(pitch));
	look.y= std::sin(glm::radians(yaw)) * std::cos(glm::radians(pitch));
	look.z= std::sin(glm::radians(pitch));
	
	
	
	//std::cout << look.x << "      " << look.y  << "     "<< look.z << "     " << delta  <<   std::endl;

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
