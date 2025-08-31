#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <memory>
#include <vector>

class Entity;



class WorldManager
{
public:
	bool Init(const std::string& objPath);// 24.08
	bool LoadLevel(const std::string& levelJsonPath);
	void Update(float dt);
	void Render(const glm::mat4& view, const glm::mat4& proj);//24.08
	void Shutdown();// 24.08
	void Draw();
	void Clear();
	const std::vector<std::unique_ptr<Entity>>& GetEntities() const{ return m_Entities;} ;
private:
	std::vector<std::unique_ptr<Entity>> m_Entities;	


	// GL resources
	GLuint m_Vao = 0 , m_VBO = 0 , m_EBO = 0;
	GLuint m_Program = 0;
	GLsizei m_IndexCount = 0;
	glm::mat4 m_Model{1.0f};

	bool loadOBJ(const std::string& path, std::vector<float>& interleaved, std::vector<uint32_t>& indices);
	GLuint makeProgram(const char* vsSrc, const char* fsSrc);
};
