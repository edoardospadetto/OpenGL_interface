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
		Shader();
		Shader(std::string&& path, GLuint type_);
		void Build(std::string&& path, GLuint type_);
		int Compile();
		GLuint GetId();
	

};
#endif



