#include "turtle.h"

Shader::Shader()
{

}

Shader::Shader(std::string&& path_, GLuint type_ ) 
{	
	Build(std::move(path_), type_ );
	  
}

void Shader::Build(std::string&& path_, GLuint type_)
{
	path = path_;
		
	id = glCreateShader( type_ );
	std::ifstream buffer(path_,std::ios::binary|std::ios::ate);
	if (!buffer) 
	{
		printf("Failed to open :%s  \n ", path_.c_str());
	} 
	else 
	{
	
	  int length = buffer.tellg();
	 
  	  buffer.seekg(std::ios::beg);
  	  source.resize(length,0);
  	 
  	  buffer.read(&source[0],length);
	
	}
	
	

}

GLuint Shader::GetId()
{
	return (id);
}

int Shader::Compile()
{
	const char *shader_input = source.c_str();
	
	glShaderSource( id, 1, &shader_input , NULL );

	//Compile shader source
	glCompileShader(id);

	//Check compile 
	GLint status = GL_FALSE;
	glGetShaderiv( id, GL_COMPILE_STATUS, &status );
	if( status != GL_TRUE )
	{   
	    if(glIsShader( id )) 
	    {
		    int length;	
		    glGetShaderiv( id, GL_INFO_LOG_LENGTH, &length);
		    char* info = new char[ length ];
		    printf( "Unable to compile shader %d, %s!\n", id, path.c_str() );
		    glGetShaderInfoLog( id, length, &length, info );
		    printf("%s", info);
		    delete[] info ;
	     }
	     else {printf("It is not a shader\n");}
	    return 1;       
	}   
	return 0;
	
}


