#ifndef DRAWER
#define DRAwER

class Asset;


class Drawer{

	protected:
		GLuint program;
		bool active = false;
		GLuint vbo; 
		GLuint ibo;
	public: 
		Drawer();
		~Drawer();
		int LoadShaders(Shader* vertex, Shader* fragment);
		int Enable();
		
		
		
		
		//int Disable();
};

#endif



