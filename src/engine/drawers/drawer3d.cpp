
#include "drawer3d.h"

Drawer3d::Drawer3d()
{

}

void Drawer3d::LoadUniforms(Camera * camera)
{
	
	 view = glGetUniformLocation( program , "sview" );
	 mod = glGetUniformLocation( program , "modl" );

	 glUniformMatrix4fv(view,1, false,  camera->GetViewMatrix() );
	 glUniformMatrix4fv(mod,1, false,  obj->GetModMatrix());
}



void Drawer3d::Draw(Asset *asset, Camera *camera )
{
	LoadAsset(asset,camera);
	LoadUniforms(camera);
	Render(asset);
	
		

}

int Drawer3d::LoadAsset(Asset *asset, Camera *camera)
{
	Enable();
	int vals = 8;
	
 	if (asset->texture.data)
	{
	    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, asset->texture.width, asset->texture.height, 0, GL_RGB, GL_UNSIGNED_BYTE, asset->texture.data);
	    glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
	    std::cout << "Failed to load texture" << std::endl;
	}
	
		
	
	 glBufferData( GL_ARRAY_BUFFER, asset->GetVertNum()*vals*sizeof(float) , ((float*) asset->GetBuffer()), GL_DYNAMIC_DRAW );
	
	 glBufferData( GL_ELEMENT_ARRAY_BUFFER, asset->GetIdxNum()*sizeof(int) , ((int*) asset->GetIdx()), GL_DYNAMIC_DRAW );
	 
	 pos = glGetAttribLocation( program , "svert" );
	 tex = glGetAttribLocation( program , "stex" );
         norm = glGetAttribLocation( program , "norm" );

	
	 glVertexAttribPointer( pos, 3, GL_FLOAT, GL_FALSE, vals * sizeof(float), 0  );	 
	 glVertexAttribPointer( tex, 2, GL_FLOAT, GL_TRUE, vals * sizeof(float), (void*)(3*sizeof(float)) );	
	 glVertexAttribPointer( norm, 3, GL_FLOAT, GL_TRUE, vals * sizeof(float), (void*)(5*sizeof(float)) );
	
	 return 0;

}

int Drawer3d::Render(Asset* asset)
{
	
	 glEnable(GL_TEXTURE_2D); 
    	 glDisable(GL_CULL_FACE); 
	 glEnableVertexAttribArray( pos);
	 glEnableVertexAttribArray( tex);
	 glEnableVertexAttribArray( norm);
	 
	 glDrawElements( GL_TRIANGLES,  asset->GetIdxNum(), GL_UNSIGNED_INT, NULL );
	 
	 glDisableVertexAttribArray( norm);
	 glDisableVertexAttribArray( pos);
	 glDisableVertexAttribArray( tex);
	 glDisable( GL_TEXTURE_2D ); 
	
	return 0;
}

void Drawer3d::SetModel(GameObj3d& mod)
{
	obj = &mod;
}





