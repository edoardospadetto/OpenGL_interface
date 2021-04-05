
#include "drawer3d.h"

Drawer3d::Drawer3d()
{

}

void Drawer3d::Draw(Asset *asset, Camera *camera )
{
	LoadAsset(asset,camera);
	Render(asset);

}

int Drawer3d::LoadAsset(Asset *asset, Camera *camera)
{
	Enable();

	
 	if (asset->texture.data)
	{
	    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, asset->texture.width, asset->texture.height, 0, GL_RGB, GL_UNSIGNED_BYTE, asset->texture.data);
	    glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
	    std::cout << "Failed to load texture" << std::endl;
	}
	
		
	 //std::cout << asset->GetVertNum() << "  "  << asset->GetIdxNum() << "  "   << *asset->GetBuffer() << "  "   << *asset->GetIdx() << "  "   << std::endl;
	 glBufferData( GL_ARRAY_BUFFER, asset->GetVertNum()*5*sizeof(float) , ((float*) asset->GetBuffer()), GL_DYNAMIC_DRAW );
	
	 glBufferData( GL_ELEMENT_ARRAY_BUFFER, asset->GetIdxNum()*sizeof(int) , ((int*) asset->GetIdx()), GL_DYNAMIC_DRAW );
	 
	 

	 pos = glGetAttribLocation( program , "svert" );
	 tex = glGetAttribLocation( program , "stex" );
	 view = glGetUniformLocation( program , "sview" );

	 glUniformMatrix4fv(view,1, false,  camera->GetViewMatrix() );
	
	 glVertexAttribPointer( pos, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0  );	 
	 glVertexAttribPointer( tex, 2, GL_FLOAT, GL_TRUE, 5 * sizeof(float), (void*)(3*sizeof(float)) );	
	
	
	 return 0;

}

int Drawer3d::Render(Asset* asset)
{
	
	 glEnable(GL_TEXTURE_2D); 
    	 glDisable(GL_CULL_FACE); 
	 glEnableVertexAttribArray( pos);
	 glEnableVertexAttribArray( tex);
	
	 glDrawElements( GL_TRIANGLES,  asset->GetIdxNum(), GL_UNSIGNED_INT, NULL );
	 
	 glDisableVertexAttribArray( pos);
	 glDisableVertexAttribArray( tex);
	 glDisable( GL_TEXTURE_2D ); 
	
	return 0;
}





