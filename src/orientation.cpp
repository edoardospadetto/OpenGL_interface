#include "orientation.h"
#include <turtle.h>

void Gui::LoadData(Camera *camera)
{

	Enable();
 
 	glBufferData( GL_ARRAY_BUFFER, 36*sizeof(float) , (float*) &(verts[0]), GL_DYNAMIC_DRAW );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, 6*sizeof(int) , ((int*) &(idxs[0])), GL_DYNAMIC_DRAW );
	 
	pos = glGetAttribLocation( program , "svert" );
	col = glGetAttribLocation( program , "color" );
	uhalf = glGetUniformLocation( program , "half" );
	
	 glUniformMatrix4fv(uhalf,1, false,  camera->GetHalfMatrix() );
	 
	 glVertexAttribPointer( pos, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0  );	 
	 glVertexAttribPointer( col, 3, GL_FLOAT, GL_TRUE, 6 * sizeof(float), (void*)(3*sizeof(float)) );
	
	
	 
}

void Gui::Draw(Camera *camera)
{
	LoadData(camera);
	Render();

}


void Gui::Render()
{
	 glEnableVertexAttribArray( pos);
	 glEnableVertexAttribArray( col);
	
	 glDrawElements( GL_LINES,  6 , GL_UNSIGNED_INT, NULL );
	 
	 glDisableVertexAttribArray( pos);
	 glDisableVertexAttribArray( pos);
	 

}
