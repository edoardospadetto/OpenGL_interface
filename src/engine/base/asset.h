#ifndef ASSET
#define ASSET
#include <fstream>
#include "../external/stb_image.h" 

class Drawer;

struct Texture
{
	GLuint id;
	unsigned char *data;
	int width, height, nrChannels; 
};

class Asset
{

	private:



		float* vert;
		float* textr;
		float* norm;

		int* idx;
		float* buffer;

		int idxnum;
		int vertnum;
		
		float position[3] = {};
	public: 

		Texture texture; 

		Asset();
		Asset(std::string&& model_path,std::string&& texture_path);
		
		
		int LoadObj(std::string&& path_);
		int LoadTexture(const char *path);
		void ResetOrigin();
		float* GetBuffer();
		int* GetIdx();
		int GetIdxNum();
		int GetVertNum();
		float* GetPos();

		~Asset();

};




#endif

/*
[12*3] = {
		
		 0,1,2, 
		 3,1,2,
		 
		 4,5,6, 
		 7,5,6,
		 
		 7,3,6,	
		 2,3,6,
		 
		 5,1,4,  
		 0,1,4,
		 
		 7,3,5,
		 1,3,5,
		 
		 0,2,4,
		 6,2,4}
		[8*3] =  { 
		  0.2f,0.2f,0.2f, 	
		  0.2f,0.2f,-0.2f,	
		  0.2f,-0.2f,0.2f,	
		  0.2f,-0.2f,-0.2f,	
		  
		  -0.2f,0.2f,0.2f,	//back
		  -0.2f,0.2f,-0.2f,
		  -0.2f,-0.2f,0.2f,
		  -0.2f,-0.2f,-0.2f};; */
