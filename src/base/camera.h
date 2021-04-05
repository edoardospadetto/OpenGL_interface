#ifndef CAMERA
#define CAMERA
#include "turtle.h"
#include <math.h>

#include <iostream>
class Camera
{	
	private :

		glm::vec3 position {0.0,-5.0,2.0};
		glm::vec3 look {0.0,1.0,0.0} ;
		glm::mat4 projection, view , half;
		glm::vec3 horizon ;
		float yaw=0, pitch=0; 
		
		
		
	public: 
		
		Camera();
		//~Camera();	
		void SetPosition(float x, float y , float z);
		glm::vec3 * GetPosition();
		
		void SetLook(float x, float y , float z);
		glm::vec3 * GetLook();
		void Move();
		void Mouse2Look(float x, float y);
		void UpdateViewMatrix();
		void debuginput(SDL_Event e);
		float* GetViewMatrix();
		float* GetHalfMatrix();
		
		bool move = false;
		float speed; 
};


#endif

