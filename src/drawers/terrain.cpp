#include "terrain.h"

void ComputeNormal(float &  A, float &  B ,  float & C )
{
	glm::vec3 one = glm::vec3( (C-A), *(&C+1) - *(&A+1),  *(&C+2) - *(&A+2) );
	glm::vec3 two = glm::vec3( (C-B), *(&C+1) - *(&B+1),  *(&C+2) - *(&B+2) );
	
	glm::vec3 norm = glm::cross(one, two);
	
	norm = norm / glm::l2Norm(norm);
	
	*(&C+6)+= 0.25* norm.x;
	*(&C+7)+= 0.25* norm.y;
	*(&C+8)+= 0.25* norm.z;
	
	*(&A+6)+= 0.25* norm.x;
	*(&A+7)+= 0.25* norm.y;
	*(&A+8)+= 0.25* norm.z;
	
	*(&B+6)+= 0.25* norm.x;
	*(&B+7)+= 0.25* norm.y;
	*(&B+8)+= 0.25* norm.z;
	
	
}



void Terrain::LinkVerts()
{
	for(int i =0; i<100; i++)
	{
		for (int j=0; j<100; j++)
		{
			verts[9*(i*100+j)]= i*2.0;
			verts[9*(i*100+j)+1]= j*2.0;
			verts[9*(i*100+j)+2]= rand()%2;
			verts[9*(i*100+j)+3]= 0.5;
			verts[9*(i*100+j)+4]= 0.5;
			verts[9*(i*100+j)+5]= 0.5;
			
			verts[9*(i*100+j)+6]= 0.0;
			verts[9*(i*100+j)+7]= 0.0;
			verts[9*(i*100+j)+8]= 0.0;
		
		}
	}
	
	for(int i =0; i<99; i++)
	{
		for (int j=0; j<99; j++)
		{
			idxs[6*(i*99+j)] = i*100+j;
			idxs[6*(i*99+j)+1] = i*100+j+1;
			idxs[6*(i*99+j)+2] = (i+1)*100+j;
			
			idxs[6*(i*99+j)+3] = (i+1)*100+j;
			idxs[6*(i*99+j)+4] = (i+1)*100+j+1;
			idxs[6*(i*99+j)+5] = i*100+j+1;
			
			
			ComputeNormal( verts[9*(i*100+j)], verts[9*(i*100+j+1)], verts[9*((i+1)*100+j)]);
			
			ComputeNormal( verts[9*((i+1)*100+j)], verts[9*(i*100+j+1)], verts[9*((i+1)*100+j+1)]);
			
			//...............................
			
			
			
			
		
		}
	}
	
	for(int i =0; i<100; i++)
	{
		for (int j=0; j<100; j++)
		{
			
			
			std::cout << verts[9*(i*100+j)+6]<< std::endl;
			std::cout << verts[9*(i*100+j)+7]<< std::endl;
			std::cout <<  verts[9*(i*100+j)+8] << std::endl;
		
		}
	}
	


}

void Terrain::LoadData(Camera *camera)
{

	Enable();
 
 	glBufferData( GL_ARRAY_BUFFER, 100*100*3*9*sizeof(float) , (float*) &(verts[0]), GL_DYNAMIC_DRAW );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, 99*99*3*2*sizeof(int) , ((int*) &(idxs[0])), GL_DYNAMIC_DRAW );
	 
	pos = glGetAttribLocation( program , "svert" );
	col = glGetAttribLocation( program , "color" );
	norms = glGetAttribLocation( program , "norms" );
	view = glGetUniformLocation( program , "sview" );
	
	 glUniformMatrix4fv(view,1, false,  camera->GetViewMatrix() );
	 
	 glVertexAttribPointer( pos, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), 0  );	 
	 glVertexAttribPointer( col, 3, GL_FLOAT, GL_TRUE, 9 * sizeof(float), (void*)(3*sizeof(float)) );
	  glVertexAttribPointer( norms, 3, GL_FLOAT, GL_TRUE, 9 * sizeof(float), (void*)(6*sizeof(float)) );
	
	
	 
}

int Terrain::Render()
{
	
	 glEnable(GL_TEXTURE_2D); 
    	 glDisable(GL_CULL_FACE); 
	 glEnableVertexAttribArray( pos);
	 glEnableVertexAttribArray( col);
	 glEnableVertexAttribArray( norms);
	
	 glDrawElements( GL_TRIANGLES,  99*99*2, GL_UNSIGNED_INT, NULL );
	 
	 glDisableVertexAttribArray( pos);
	 glDisableVertexAttribArray( col);
	 glDisableVertexAttribArray( norms);
	 glDisable( GL_TEXTURE_2D ); 
	
	return 0;
}

void Terrain::Draw(Camera* camera)
{
LoadData(camera);
Render();
}
