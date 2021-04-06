
#include <turtle.h>


#ifndef TERRAIN
#define TERRAIN

class Camera;

class Terrain : public Drawer
{	

	GLuint pos;
	GLuint col;
	GLuint view;
	GLuint norms;
	
	public: 
	
	float verts[100*100*9]; 
	int  idxs[99*99*2*3];
	 
	 void LoadData(Camera* camera);
	 void Draw(Camera *camera); 
	 int Render();
	 void LinkVerts();
	  

};


#endif


