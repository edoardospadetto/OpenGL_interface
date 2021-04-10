#include "turtle.h"

Drawer::Drawer()
{
	 program = glCreateProgram();
	 glGenBuffers( 1, &vbo );
	 glGenBuffers( 1, &ibo );
 	
}

Drawer::~Drawer()
{

	glDeleteProgram(program);
}

int Drawer::LoadShaders(Shader* vertex, Shader* fragment)
{	
	
        //Attach shader to program 
        glAttachShader( program , vertex->id );
        glAttachShader( program , fragment->id );
        //Link program
        glLinkProgram( program );
	//check link
	GLint status = GL_FALSE;
        glGetProgramiv( program, GL_LINK_STATUS, &status );
        if( status != GL_TRUE )
        {
                printf( "Error linking shaders to program with id %d!\n",program);
  		return 1;
        }
        active = true;
        
	return 0;

}

int Drawer::Enable()
{
	glUseProgram(program);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo );
	return 0;

}
/*
int Drawer::Render()
{
	printf("Define derived class and define your Render");
	
	return 0;
}
int Drawer::LoadAsset()
{
	printf("Define derived class and define your LoadAsset");
	
	return 0;
}


/*
int Drawer::Disable()
{
	glUseProgram(NULL);
	return 0;
}
*/
