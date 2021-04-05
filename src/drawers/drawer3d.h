

#ifndef DRAWER3D
#define DRAWER3D
#include <turtle.h>

class Camera;

class Drawer3d: public Drawer
{	
	private:
		GLuint pos;
		GLuint tex;
		GLuint view;
	public:
		Drawer3d();
		
		
		const void* GetVert(const Asset *asset);
		const void* GetIdx(const Asset *asset);
		int GetNumVert(const Asset *asset);
		int GetNumIdx(const Asset *asset);
		int Render(Asset *asset);
		int LoadAsset(Asset *asset, Camera *camera);
		void Draw(Asset *asset, Camera* camera);
		
		
	 

};

#endif


