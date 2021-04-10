#include <turtle.h>
#include <vector>
#include <string>
#include <algorithm>    // std::any_of
#include <cmath>
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



int Asset::LoadObj(std::string &&  path)
{
	printf("Loading OBJ file %s...\n", path.c_str());

	std::vector<int> vertexIndices, uvIndices, normalIndices;
	std::vector<float> temp_vertices; 
	std::vector<float> temp_uvs;
	std::vector<float> temp_normals;
	
	


	FILE * file = fopen(path.c_str(), "r");
	if( file == NULL ){
		printf("Impossible to open the file ! Are you in the right path ? See Tutorial 1 for details\n");
		getchar();
		return false;
	}

	while( 1 )
	{

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF) break; // EOF = End Of File. Quit the loop.

		// else : parse lineHeader
		
		if ( strcmp( lineHeader, "v" ) == 0 )
		{
			float x,y,z;
			fscanf(file, "%f %f %f\n", &x, &y, &z );
			temp_vertices.push_back(x);
			temp_vertices.push_back(y);
			temp_vertices.push_back(z);
		}
		else if ( strcmp( lineHeader, "vt" ) == 0 )
		{
			float x,y;
			fscanf(file, "%f %f\n", &x, &y );
			//uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
			temp_uvs.push_back(x);
			temp_uvs.push_back(-y);
		}
		else if ( strcmp( lineHeader, "vn" ) == 0 )
		{
			float x,y,z;
			fscanf(file, "%f %f %f\n", &x, &y, &z );
			temp_normals.push_back(x);
			temp_normals.push_back(y);
			temp_normals.push_back(z);
		}
		else if ( strcmp( lineHeader, "f" ) == 0 )
		{	
			char* tmpbuffer = (char*)malloc(sizeof(char)*256);
			fgets(tmpbuffer,256,file);
			//fscanf(file, "%s", tmpbuffer);
			int vertexIndex[4], uvIndex[4], normalIndex[4];
			
			
			int check = sscanf(tmpbuffer, "%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d\n", 
		   	    &vertexIndex[0], &uvIndex[0], &normalIndex[0],
			    &vertexIndex[1], &uvIndex[1], &normalIndex[1],
			    &vertexIndex[2], &uvIndex[2], &normalIndex[2],
			    &vertexIndex[3], &uvIndex[3], &normalIndex[3]);
			    
			//printf("%s  %d\n", tmpbuffer, check );
			   
			if (check == 9)
			{
				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);
				uvIndices    .push_back(uvIndex[0]);
				uvIndices    .push_back(uvIndex[1]);
				uvIndices    .push_back(uvIndex[2]);
				normalIndices.push_back(normalIndex[0]);
				normalIndices.push_back(normalIndex[1]);
				normalIndices.push_back(normalIndex[2]);
			}
			else if(check == 12) 
			{
			
	
				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);
				uvIndices    .push_back(uvIndex[0]);
				uvIndices    .push_back(uvIndex[1]);
				uvIndices    .push_back(uvIndex[2]);
				normalIndices.push_back(normalIndex[0]);
				normalIndices.push_back(normalIndex[1]);
				normalIndices.push_back(normalIndex[2]);
						 	
			 	vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[3]);
				vertexIndices.push_back(vertexIndex[2]);
				uvIndices    .push_back(uvIndex[0]);
				uvIndices    .push_back(uvIndex[3]);
				uvIndices    .push_back(uvIndex[2]);
				normalIndices.push_back(normalIndex[0]);
				normalIndices.push_back(normalIndex[3]);
				normalIndices.push_back(normalIndex[2]);
				
				//printf("quad\n");
			 
			 
			 
			 } 
			 else
			 {
			 	printf("Error, format not understood\n"); 
			    	return 1; 
			 }
			 free(tmpbuffer);
			
			
			
		}
		else
		{
			// Probably a comment, eat up the rest of the line
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}

	}
	
	vertnum = vertexIndices.size(); 
	idxnum  = vertexIndices.size();
	idx = new int[idxnum];
	buffer = new float[idxnum*5];
	
	// For each vertex of each triangle
	for( unsigned int i=0; i<idxnum; i++){

		// Get the indices of its attributes
		int vertexIndex = abs(vertexIndices[i]);
		int uvIndex = abs(uvIndices[i]);
		int normalIndex = abs(normalIndices[i]);
		
		idx[i] = i;
		// Get the attributes thanks to the index
		buffer[5*i+0] = temp_vertices[3*(vertexIndex-1)+0];
		buffer[5*i+1] = temp_vertices[3*(vertexIndex-1)+1];
		buffer[5*i+2] = temp_vertices[3*(vertexIndex-1)+2];
		
		buffer[5*i+3] = temp_uvs[2*(uvIndex-1)+0];
		buffer[5*i+4] = temp_uvs[2*(uvIndex-1)+1];
		
		//float nx = temp_normals[3*(normalIndex-1)+0];
		//float ny = temp_normals[3*(normalIndex-1)+1];
		//float nz = temp_normals[3*(normalIndex-1)+2];
		
		// Put the attributes in buffers
		//out_vertices.push_back(vertex);
		//out_uvs     .push_back(uv);
		//out_normals .push_back(normal);
	
	}
	
	ResetOrigin();
	fclose(file);
	printf("Done!\n");
	 
	 return 0;

}

void Asset::ResetOrigin()
{
	float avgx=0.0f, avgy=0.0f, avgz=0.0f ;

	for(int i =0; i<vertnum; i++)
	{
		avgx+=buffer[5*i+0]; 
		avgy+=buffer[5*i+1]; 
		avgz+=buffer[5*i+2]; 
	}
	
	avgx*=(1.0f/float(vertnum));
	avgy*=(1.0f/float(vertnum));
	avgz*=(1.0f/float(vertnum));
	
		for(int i =0; i<vertnum; i++)
	{
		buffer[5*i+0]-=avgx; 
		buffer[5*i+1]-=avgy; 
		buffer[5*i+2]-=avgz; 
	}		
	
	

}

/*
int Asset::LoadObj2( std::string&& path_)
{
	 objl::Loader Loader;
	 Loader.LoadFile(path_);
	 int indices = 0;
	 int offset = 0;
	 int maxidx = 0;
	 vertnum = 0; 
	 idxnum = 0;
	 for (int k = 0; k < Loader.LoadedMeshes.size(); k++)
	 {
	 	objl::Mesh curMesh = Loader.LoadedMeshes[k];
		idxnum+=  curMesh.Indices.size();
		vertnum+= curMesh.Vertices.size();
	 }
	
	 idx = new int[idxnum];
	 buffer = new float[vertnum*5];
	 float avgx =0;
	 float avgy= 0;
	 float avgz =0;
	 float minx,maxx,miny,maxy=0;
	 
	
 	for (int k = 0; k < Loader.LoadedMeshes.size(); k++)
	{
	 objl::Mesh curMesh = Loader.LoadedMeshes[k];
	
	
	 
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
	
	 
	 for(int i=0; i< curMesh.Vertices.size(); ++i)
	 {
	 	buffer[5*i+0] =  ( curMesh.Vertices[i].Position.X);
	 	buffer[5*i+2] = (curMesh.Vertices[i].Position.Y);
	 	buffer[5*i+1] = (curMesh.Vertices[i].Position.Z);
	 	buffer[5*i+3] = curMesh.Vertices[i].TextureCoordinate.X;//-minx)/(maxx-minx);
	 	buffer[5*i+4] = 1- curMesh.Vertices[i].TextureCoordinate.Y;//-miny)/(maxy-miny);
	 	
	 	
				
	 } 
	 for (int j = 0; j < curMesh.Indices.size(); ++j)
	{
		idx[j]= curMesh.Indices[j];//+offset;
		//if(curMesh.Indices[j] > maxidx) maxidx = curMesh.Indices[j];
		//printf("%d \n",  idx[j] );
	}
	offset = maxidx;
	}
	 avgx*=(1.0/vertnum);
	 avgy*= (1.0/vertnum);
	 avgz*=(1.0/vertnum);
	 for(int i=0; i< vertnum; ++i)
	 {
	 	buffer[5*i+0] -= avgx;
	 	buffer[5*i+2] -= avgy;
	 	buffer[5*i+1] -=avgz ;
	 	//buffer[5*i+3] = curMesh.Vertices[i].TextureCoordinate.X;//-minx)/(maxx-minx);
	 	//buffer[5*i+4] = 1- curMesh.Vertices[i].TextureCoordinate.Y;//-miny)/(maxy-miny);			
	 } 
	
	 
	
	 
	 position[0] = avgx;
	 position[1] = avgy;
	 position[2] = avgz;
	 
	 return 0;

}

*/
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

