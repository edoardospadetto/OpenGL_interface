
#ifndef RIGGERDRAWER
#define RIGGERDRAWER

#include <turtle.h>

class GameObj3d;
class Camera;

class RiggerDrawer: public Drawer
{	
	private:
		GLuint pos;
		GLuint col;
		GLuint view;
		GLuint mod;
		
		glm::mat4 model;
		 
		
		
		bool loaded = false;
	
	public:
		
		int numvert = 0;
		int numidx = 0;
		float* buffer;
		int* indices;
			
		float colors[8*3] = {
				1.0f,0.0f,0.0f,//0
				0.0f,0.0f,1.0f,//1
				0.0f,1.0f,0.0f,//2
				1.0f,0.0f,0.0f,//3
				0.0f,1.0f,1.0f,//4
				1.0f,0.0f,1.0f,//5
				1.0f,1.0f,0.0f,//6
				1.0f,1.0f,1.0f//7
				}; 
		RiggerDrawer();
		~RiggerDrawer();
		
		void Init();
			
		void Draw(GameObj3d *obj,Camera* camera);
		
		void LoadAsset(Asset *asset);
		
		
		
	 

};

#endif
