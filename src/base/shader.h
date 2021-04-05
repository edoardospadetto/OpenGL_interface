#ifndef SHADER
#define SHADER


class Shader
{
	friend class Drawer;
	
	private:
		GLuint id=0;
		std::string source;
		std::string path;
	public:
		Shader(std::string&& path, GLuint type_);
		int Compile();
	

};
#endif



