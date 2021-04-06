#ifndef RIGGER_
#define RIGGER_

class Editor; 

class Rigger
{

	private:
		float* orthox, orthoy;
	public:	
		Rigger(Camera *camera);
		void NewSession();
	

}

#endif

