#include "WorldManager.h"
#include <glm/gtc/type_ptr.h>
#define TINYLOADEROBJECT_IMPLEMENTATION
#include <tiny_obj_loader.h>
#include <iostream>


static const char* kVS = R"(#version 330 core 
layout(location=0) in vec3 aPos;
layout(location=1) in vec3 aNormal;
layout(location=3) in vec3 aUV;
uniform mat4 uModel, uView, uProj;
out vec3 vN; out vec2 uUV;
void main(){

	vN = mat3(transpose(inverse(uModel)))* aNormal;
	vUV= aUV;
	gl_Position = uProj * uView *uModel * vec4(aPos, 1.0); 
}


)";

static const char* kFS = R"(#version 330 core
in vec3 vN; in vec2 vUV;
out vec4 FragColor;
void main(){
vec3 L = normalize(vec3(0.5,1.0,0.3));
float ndl = max(dot(normalize(vN),L),0.0);
vec3 base = vec3(0.85, 0.85, 0.9);
FragColor = vec4(base *(0.2 + 0.8*ndl), 1.0);

}
)";
static GLuint compile(GLenum type, const char* src){
	GLuint s = glCreateShader(type);
	glShaderSource(s, 1, &src, nullptr);
	glShaderCompile(s);
	GLint ok =0; glGetShaderiv(s, GL_COMPILE_STATUS, &ok);
	if (!ok){char log[2048]; glGetShaderInfoLog(s,2048,nullptr,log); std::cerr <<log<< "\n";}
	return s;
}


GLuint WorldManager::makeProgram(const char* vsSrc, const char* fsSrc){	
	GLuint vs = compile(GL_VERTEX_SHADER, vsSrc);
	GLuint fs = compile(GL_FRAGMENT_SHADER, fsSrc);
	GLuint p = glCreateProgram();
	glAttachShader(p, vs); glAttachShader(p, fs);
	glLinkProgram(p);
	GLint ok = 0; glGetProgramiv(p, GL_LINK_STATUS, &ok);
	if(!ok){char log[2048];glGetProgramInfoLog(p, 2048,nullptr,log);
	std::cerr<< log<< "\n";

}		
	glDeleteShader(vs);
	glDeleteShader(fs);
	return p;

}
bool WorldManager::loadOBJ(const std::string& path, std::vector<float>& intervealed,std::vector<uint32_t>& indices){
	tinyobj::ObjReader reader;
	tinyobj::ObjReaderConfig cfg;
	cfg.triangulate = true;
	if(!reader.ParseFromFile(path,cfg)){ std::cerr<< "OBJ load error"<<reader.Error()<<"\n";
	return false;
}
	if(!reader.Warning().empty())std::cerr << "Warning OBJ"<< reader.Warning()<< "\n";

	const auto& attrib = reader.GetAttrib();
	const auto& shapes = reader.GetShapes();

	struct Key
	{	int v, vt, vn; bool operator==(const Key& o) const{ return v== o.v,}
		
	// here im stopped
	}
}





