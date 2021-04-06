#include <turtle.h>


#ifndef GUI_
#define GUI_

class Camera;

class Gui: public Drawer
{	

	int col, pos, uhalf;
	
	public: 
	
	float verts[36] = { 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 
	  		    0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 
	  		    0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 
	  		    0.1, 0.0, 0.0, 1.0, 0.0, 0.0, 
	  		    0.0, 0.1, 0.0, 0.0, 1.0, 0.0, 
	  		    0.0, 0.0, 0.1, 0.0, 0.0, 1.0};
	 int  idxs[6] = {0,3,1,4,2,5};
	 
	 void LoadData(Camera* camera);
	 void Draw(Camera *camera); 
	 void Render();
	  

};
#endif


