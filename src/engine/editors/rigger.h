#ifndef RIGGER_
#define RIGGER_

class Editor; 

class Rigger
{

	private:
		
		float* orthox, orthoy;
	public:	
		Rigger(Camera *camera);
		void Mouse2World();
		std::vector<float> points;
		std::vector<float> colors;
		void SetPoint();
		void SelectPoint();
}		

#endif

