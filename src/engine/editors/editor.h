#ifndef EDITOR 
#define EDITOR 

#include "../drawers/riggerdrawer.h"
class Context; 
class GameObj3d;
class Drawer3d;
class Rigger;
class Shader;
class RiggerDrawer;

class Editor
{
	private:
		Context * context = nullptr; 
		Camera * camera = nullptr;
		
		//Mods of the Editor
		int watchfromcase = 0; 
		float orthox = 10.0, orthoy = 10.0;
		
		//Render Editor Info
		Shader EditorVertex;
		Shader EditorFragment;
		GLuint EditorProgram;
		GLuint evbo; 
		GLuint eibo;
		
		//RiggerDrawer
		RiggerDrawer drawrigprocess;
		//Current GameObj
		GameObj3d* object;
		
		//RIGGER TOOL
		int selected_point=0;
		bool edit_points = false;
		bool fix_point = false;
		bool once_weights = true;
		bool paint_cluster = false;
		std::vector<int> nearest_node;
		std::vector<int> parents;
		std::vector<float> fixed_points;
		std::vector<float> points;
		std::vector<float> colors;
   
		std::vector<float> distances;
		
	public: 
		Editor(Context *context_, Camera *camera_, std::string&& shaderv_ , std::string&& shaderf_,std::string&& gsls_version);
		~Editor();
		
		void Handle(GameObj3d * obj);
		
		void EditObjModel(GameObj3d * obj);
		void WatchFrom(GameObj3d * obj);
		void MoveSkeleton(GameObj3d * obj);
		void FindNearest(GameObj3d * obj);
		
		void StartFrame();
		void EndFrame();
		void Dot();
		
		//rigger
		void EditRiggerPoint();
		void RiggerWindow();
		void NodesHierarchy();
		void FromParent();
		void PaintCluster();

	



};

#endif
