#include "WorldManager.h"
#include <glm/gtc/type_ptr.hpp>
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
	glCompileShader(s);
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
	};
	struct H { size_t operator() (const Key& k)const{return((k.v*73856093) ^ (k.vt*19349663) ^ (k.vn*83492791));}}

	std::unordered_map<Key, uint32_t, H> map;
	intervealed.clear(); indices.clear();
	auto pushVertex = [&](const Key& k)->uint32_t{
		auto it = map.find(k);
		if(it!=map.end()) return it->second;
	 
	 int vi = k.v*3;
	 float px = attrib.vertices[vi+0];
	 float py = attrib.vertices[vi+1];
	 float pz = attrib.vertices[vi+2];

	 float nx = 0, ny =0 ,nz =0;
	 if(k.vn >=0){
	 	int ni = k.vn*3;
	 	nx = attrib.normals[ni+0];
	 	nx = attrib.normals[ni+1];
	 	nx = attrib.normals[ni+2];

	 }
	 float u=0,v= 0;
	 if(k.vt >=0){
	 	int ti = k.vt*2;
	 	u = attrib.texcoords[ti+0];
	 	v = attrib.texcoords[ti+1];

	 } 

	 uint32_t idx = (uint32_t)(intervealed.size()/8);
	 intervealed.insert(intervealed.end(),{px,py,pz, nx,ny,nz, u,v});
	 map.emplace(k, idx);
	 return idx;
	 for( const auto& sh : shapes){
	 	size_t off = 0;
	 	for(size_t f=0 ; f<sh.mesh.num_face_vertices.size(); ++f){
	 		int fv = sh.mesh.num_face_vertices[f];
	 		for (int i=0; i<fv;i++){
	 			const auto& idx = sh.mesh.indices[off + i];

	 			Key k{idx.vertex_index, idx.texcoord_index, idx.normal_index };
	 			indices.push_back(pushVertex(k));

	 		}
	 		off +=fv;


	 	}
	 }
	 return true;
}
bool WorldManager::Init(const std::string& path){
	std::vector<float> inter; std::vector<uint32_t> idx;
	if (!loadOBJ(path, inter, idx))
	{
		return false;//
	}
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_EBO);
	glBindVertexArrays(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, inter.size()*sizeof(float), inter.data(), GL_STATIC_DRAW );

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, idx.size()*sizeof(uint32_t),idx.data(), GL_STATIC_DRAW);


	GLsizei stride = 8 * sizeof(float);
	glEnableVertexAttribArray(0);

	m_IndexCount = (GLsizei)idx.size();
	m_Program = makeProgram(kVS,kFS);
	m_Model = glm::mat4(1.0f);


return true;}
void WorldManager::Render(const glm::mat4& view, const glm::mat4& proj){
 if(!m_Program 
|| !m_VAO ||m_IndexCount==0)return;
 	glUseProgram(m_Program);
 GLint uM = glGetUniformLocation(m_Program, "uModel");


}




