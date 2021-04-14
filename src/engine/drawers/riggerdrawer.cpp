#include <turtle.h>
#include "riggerdrawer.h"


RiggerDrawer::RiggerDrawer()
{

}



void RiggerDrawer::Draw(GameObj3d *obj, Camera *camera)
{
	if(loaded)
	{
		Enable();
		int vals = 6;
		
	 
		 glBufferData( GL_ARRAY_BUFFER, numvert*vals*sizeof(float) , ((float*) &(buffer[0])), GL_DYNAMIC_DRAW );
		
		 glBufferData( GL_ELEMENT_ARRAY_BUFFER, numidx*sizeof(int) , ((int*) &(indices[0])), GL_DYNAMIC_DRAW );
		 
		 pos = glGetAttribLocation( program , "svert" );
		 col = glGetAttribLocation( program , "color" );
		 

		
		 glVertexAttribPointer( pos, 3, GL_FLOAT, GL_FALSE, vals * sizeof(float), 0  );	 
		 glVertexAttribPointer( col, 3, GL_FLOAT, GL_TRUE, vals * sizeof(float), (void*)(3*sizeof(float)) );	
		 
		 
		 view = glGetUniformLocation( program , "sview" );
		 mod = glGetUniformLocation( program , "modl" );

		 glUniformMatrix4fv(view,1, false,  camera->GetViewMatrix() );
		 glUniformMatrix4fv(mod,1, false,  obj->GetModMatrix());
		
		
	    	 glDisable(GL_CULL_FACE); 
		 glEnableVertexAttribArray( pos);
		 glEnableVertexAttribArray( col);

		 
		 glDrawElements( GL_TRIANGLES,  numidx , GL_UNSIGNED_INT, NULL );
		 
		 glDisableVertexAttribArray( col);
		 glDisableVertexAttribArray( pos);
	
	}
	

}


void RiggerDrawer::Init()
{
	Shader rv("./shaders/vrigger.3d", GL_VERTEX_SHADER);
	Shader rf("./shaders/frigger.3d", GL_FRAGMENT_SHADER);
	
	rv.Compile();
	rf.Compile();
	
	LoadShaders(&rv,&rf);
	
}

void RiggerDrawer::LoadAsset(Asset* asset)
{
	
	
	int vals = 8;
	buffer = new float[asset->GetVertNum()*6];
	indices = new int[asset->GetIdxNum()];
	
	numvert = asset->GetVertNum();
	numidx = asset->GetIdxNum();
	
	for (int i =0 ; i<asset->GetVertNum(); ++i )
	{
		buffer[6*i] = *((float*) asset->GetBuffer()+i*vals);
		buffer[6*i+1] = *((float*) asset->GetBuffer()+i*vals+1);
		buffer[6*i+2] = *((float*) asset->GetBuffer()+i*vals+2);
		buffer[6*i+3] = 0.0;
		buffer[6*i+4] = 0.0;
		buffer[6*i+5] = 0.0;
	}
	for (int i =0 ; i<asset->GetIdxNum() ; i++)
	{
		indices[i] = *(asset->GetIdx()+i);	
	}
	
	loaded = true;
	
}

RiggerDrawer::~RiggerDrawer()
{
	delete [] buffer;
	delete [] indices;
}

