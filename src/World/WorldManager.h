#pragma once


#include <string>
#include <memory>
#include <vector>

class Entity;



class WorldManager
{
public:
	bool LoadLevel(const std::string& levelJsonPath);
	void Update(float dt);
	void Draw();
	void Clear();
	const std::vector<std::unique_ptr<Entity>>& GetEntities() const{ return m_Entities;} ;
private:
	std::vector<std::unique_ptr<Entity>> m_Entities;	
};
