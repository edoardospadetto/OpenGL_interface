#include "turtle.h"
#include <fstream>
GameObj3d::GameObj3d(std::string&& model,std::string&& texture,std::string&& name_) : 
	name(name_), model_matrix(1.0)
{
	 asset = new Asset(std::move(model) , std::move(texture));


} 

void GameObj3d::Move(float x, float y, float z)
{
	model_matrix = glm::translate(model_matrix,glm::vec3(x,y,z));
}


void GameObj3d::Scale(float x, float y, float z)
{
	model_matrix = glm::scale(glm::vec3(x,y,z));
}

void GameObj3d::Rotate(float x , float y, float z)
{
	if(x!=0)
	{
	model_matrix = glm::rotate(model_matrix,x,glm::vec3(1.0f,0.0f,0.0f));		
	
	}
	if(y!=0)
	{
	model_matrix =  glm::rotate(model_matrix,y,glm::vec3(0.0f,1.0f,0.0f));
	}
	
	if(z!=0)
	{
	model_matrix =  glm::rotate(model_matrix,z,glm::vec3(0.0f,0.0f,1.0f));
	}

}

void GameObj3d::ComputeModelMatrix()
{
	model_matrix = glm::mat4(1.0);
	
	model_matrix = glm::scale(model_matrix, glm::vec3(scale[0],scale[1],scale[2]));
	
	model_matrix = glm::rotate(model_matrix,rot[0],glm::vec3(1.0f,0.0f,0.0f));
	model_matrix = glm::rotate(model_matrix,rot[1],glm::vec3(0.0f,1.0f,0.0f));
	model_matrix = glm::rotate(model_matrix,rot[2],glm::vec3(0.0f,0.0f,1.0f));
	
	model_matrix = glm::translate(model_matrix,glm::vec3(pos[0],pos[1], pos[2]));
	

}

void GameObj3d::SetPos(float x , float y, float z){
	pos[0] = x;
	pos[1] = y;
	pos[2] = z;
	ComputeModelMatrix();
}


void GameObj3d::SetRot(float x , float y, float z){

	rot[0] = x;
	rot[1] = y;
	rot[2] = z;
	ComputeModelMatrix();

}

void GameObj3d::SetScale(float x , float y, float z){

	scale[0] = x;
	scale[1] = y;
	scale[2] = z;
	ComputeModelMatrix();

}



Asset* GameObj3d::GetAsset(){return asset;}
float* GameObj3d::GetModMatrix(){return &(model_matrix[0][0]);}
float* GameObj3d::GetScale(){return &(scale[0]);}
float* GameObj3d::GetRot(){return &(rot[0]);}
float* GameObj3d::GetPos(){return &(pos[0]);}

/*
void GameObj3d::SetSkeleton(std::vector<float> nodes_, std::vector<int> edges_)
{
	skeleton.nodes = nodes;
	skeleton.edges = edges;	

}
void GameObj3d::SaveSkeleton(std::string && file_)
{
	std::ofstream sk_out (path_, std::ofstream::out);
	
	sk_out << skeleton.nodes.size()  << skeleton.edges.size();
	
	for(int i =0 ; i<skeleton.nodes.size()  ; i++)
	{
		sk_out <<  skeleton.nodes[i];
	}
	for(int i =0 ; i<skeleton.edges.size()  ; i++)
	{
		sk_out <<  skeleton.edges[i];
	}
}

void GameObj3d::LoadSkeleton(std::string && path_)
{
	int nodesize, edgesize;
	std::vector<int> edges_tmp;
	std::vector<float> nodes_tmp;
	std::ifstream sk_int (path_, std::ifstream::int);

	sk_in >> skeleton.nodes.size()  >> skeleton.edges.size();
	
	for(int i =0 ; i<nodesize()  ; i++)
	{
		nodes_tmp.push_back(0.0);
		sk_in >> nodes_tmp[in] ;
	}
	for(int i =0 ; i<edgesize()  ; i++)
	{
		nodes_tmp.push_back(0.0);
		sk_in >> nodes_tmp[i] ;
	}
	
	
}

*/


GameObj3d::~GameObj3d()
{
	delete asset;
}

