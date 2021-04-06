#ifndef EDITOR 
#define EDITOR 

class Context; 
class GameObj3d;
class Drawer3d;
class Rigger;

class Editor
{
	private:
		Context * context = nullptr; 
		Camera * camera = nullptr;
		
		//Mods of the Editor
		Rigger rigger; 
		
		
		int watchfromcase = 0; 
		float orthox = 10.0, orthoy = 10.0;
		
	public: 
		Editor(Context *context_, Camera *camera_, std::string&& gsls_version);
		~Editor();
		
		void EditObjModel(GameObj3d * obj);
		void WatchFrom(GameObj3d * obj);
		void StartFrame();
		void EndFrame();
		void Dot();
		
	



};

#endif
