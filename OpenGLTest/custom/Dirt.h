#pragma once
#include "GameObject.h"

class Dirt : public GameObject
{
public:
	Dirt(glm::vec3 SpawnPoint, TextureData TXData, float TXNumber, float r = 1.0f, float g = 1.0f, float b = 1.0f, float alpha = 1.0f);
	~Dirt();
	//Dirt(float xAbs, float yAbs);

	//std::vector<std::shared_ptr<Dirt>> GetpathElementCoords();
private:

};