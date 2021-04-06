#ifndef EDITOR 
#define EDITOR 

class Context; 
class GameObj3d;

class Editor
{
	private:
		Context * context = nullptr; 
		int watchfromcase = 0; 
		float orthox = 10.0, orthoy = 10.0;
	public: 
		Editor(Context *context_, std::string&& gsls_version);
		~Editor();
		void Mouse();
		void EditObjModel(GameObj3d * obj);
		void WatchFrom(GameObj3d * obj, Camera * camera);
		void StartFrame();
		void EndFrame();
		void Dot();
		
	



};

#endif
