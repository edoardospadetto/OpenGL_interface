
#ifndef DRAWER3D
#define DRAWER3D

#include <turtle.h>

class GameObj3d;
class Camera;

class Drawer3d: public Drawer
{	
	private:
		GLuint pos;
		GLuint tex;
		GLuint view;
		GLuint mod;
		GameObj3d *obj;
	public: 
		Drawer3d();
		
		void SetModel(GameObj3d &obj_);
		void LoadUniforms(Camera * camera);
		
		const void* GetVert(const Asset *asset);
		const void* GetIdx(const Asset *asset);
		
		int GetNumVert(const Asset *asset);
		int GetNumIdx(const Asset *asset);
		
		void Draw(Asset *asset, Camera* camera);
		int Render(Asset *asset);
		int LoadAsset(Asset *asset, Camera *camera);
		
		
		
	 

};

#endif


