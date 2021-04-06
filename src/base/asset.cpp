#include "turtle.h"
#include <vector>
#include <string>
#include <algorithm>    // std::any_of
#include <iostream>
#include "../external/OBJ_Loader.h"
Asset::Asset()
{
	//vert = new float[8];
	//idxs = new int[12];
	//norms = new float[];


}

Asset::Asset(std::string&& model_path, std::string&& texture_path )
{
	LoadObj(std::move(model_path));
	LoadTexture(texture_path.c_str());	

}

Asset::~Asset()
{
	//delete[] vert;
	delete[] idx; 
	//delete[] norm;
	//delete[] textr;
	delete[] buffer;
	stbi_image_free(texture.data);


}

void swapiflower(float &a, float &b)
{
	if(a<b){b=a;}	
}
void swapiflarger(float &a, float &b)
{
	if(a>b){b=a;}
}




int Asset::LoadObj( std::string&& path_)
{
	 objl::Loader Loader;
	 Loader.LoadFile(path_);
	 objl::Mesh curMesh = Loader.LoadedMeshes[0];
	 idxnum = curMesh.Indices.size();
	 vertnum = curMesh.Vertices.size();
	 idx = new int[curMesh.Indices.size()];
	 buffer = new float[curMesh.Vertices.size()*5];
	 
	 float avgx =0;
	 float avgy= 0;
	 float avgz =0;
	 float minx,maxx,miny,maxy=0;
	 
	
	 
	  for(int i=0; i< curMesh.Vertices.size(); ++i)
	 {
	 	avgx+=curMesh.Vertices[i].Position.X;
	 	avgy+=curMesh.Vertices[i].Position.Y;
	 	avgz+=curMesh.Vertices[i].Position.Z;
	 	swapiflower( curMesh.Vertices[i].TextureCoordinate.X, minx);
	 	swapiflarger(curMesh.Vertices[i].TextureCoordinate.X, maxx);
	 	swapiflower(curMesh.Vertices[i].TextureCoordinate.Y, miny);
	 	swapiflarger(curMesh.Vertices[i].TextureCoordinate.Y, maxy);
		
				
	 } 
	 
	 avgx*=(1.0/curMesh.Vertices.size());
	 avgy*= (1.0/curMesh.Vertices.size());
	 avgz*=(1.0/curMesh.Vertices.size());
	 
	 position[0] = avgx;
	 position[1] = avgy;
	 position[2] = avgz;
	 
	 
	 for(int i=0; i< curMesh.Vertices.size(); ++i)
	 {
	 	buffer[5*i+0] =  ( curMesh.Vertices[i].Position.X -avgx)/25.0;
	 	buffer[5*i+2] = -(curMesh.Vertices[i].Position.Y-avgy)/25.0;
	 	buffer[5*i+1] = (curMesh.Vertices[i].Position.Z-avgz)/20.0;
	 	buffer[5*i+3] = curMesh.Vertices[i].TextureCoordinate.X;//-minx)/(maxx-minx);
	 	buffer[5*i+4] = 1- curMesh.Vertices[i].TextureCoordinate.Y;//-miny)/(maxy-miny);
	 	
	 	
				
	 } 
	 for (int j = 0; j < curMesh.Indices.size(); ++j)
	{
		idx[j]= curMesh.Indices[j];
		//printf("%d \n",  idx[j] );
	}
	 return 0;

}


int Asset::LoadTexture( const char * path_)
{

	glGenTextures(1, &(texture.id));
	glBindTexture(GL_TEXTURE_2D, (texture.id));
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
		// load and generate the texture
	
	(texture.data) = stbi_load(path_, &(texture.width), &(texture.height), &(texture.nrChannels), 0);

return 0;

}

 float* Asset::GetBuffer()
 {
 
 	return(&(buffer[0]));
 }
 
 int* Asset::GetIdx()
 {
 
 	return(&(idx[0]));
 }
 
 int Asset::GetIdxNum()
 {
 
 	return(idxnum);
 }
 
 
 int Asset::GetVertNum()
 {
 	return(vertnum);
 }
 
 float* Asset::GetPos()
 {
 
 	return &(position[0]);
 
 }

