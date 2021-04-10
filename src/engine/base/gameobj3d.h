#ifndef GAMEOBJ3D__
#define GAMEOBJ3D_

class Asset;

struct skeleton
{
	int* edges ; 
	float* nodes;		
};

class GameObj3d
{
    float pos[3] = {0.0,0.0,0.0};
    float rot[3] = {0.0,0.0,0.0};
    float scale[3] = {1.0,1.0,1.0};
    glm::mat4 model_matrix;
    Asset *asset= nullptr;
    std::string name;
    
    public:
        
        GameObj3d(std::string&& model, std::string&& texture, std::string&& name);
        ~GameObj3d();
        
	void ComputeModelMatrix();
	float* GetModMatrix();
        void Move(float x, float y, float z);
        void Scale(float x, float y, float z);
        void Rotate(float x, float y, float z); 
 
        void SetScale(float x , float y, float z);
        void SetRot(float x , float y, float z);
        void SetPos(float x , float y, float z);
        
        float* GetScale();
        float* GetRot();
        float* GetPos();
        
        
        Asset* GetAsset();


};


#endif
