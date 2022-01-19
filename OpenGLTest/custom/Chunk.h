#pragma once
#include "GameObject.h"
#include "Dirt.h"

class Chunk : public GameObject
{
public:
	Chunk(glm::vec3 SpawnPoint, TextureData TXData, float TXNumber, float r = 1.0f, float g = 1.0f, float b = 1.0f, float alpha = 1.0f);

	void AddpathElementCoords(std::shared_ptr<GameObject> coords);

	std::vector<std::shared_ptr<GameObject>> GetpathElementCoords();
	std::vector<std::shared_ptr<GameObject>> m_pathElementCoords; // make private and add getter

private:
	int m_pathStartPoint;
	
};