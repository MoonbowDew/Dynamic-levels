#pragma once
#include "GameObject.h"

class Ghost : public GameObject
{
public:
	Ghost(glm::vec3 SpawnPoint, TextureData TXData, float TXNumber, float r = 1.0f, float g = 1.0f, float b = 1.0f, float alpha = 1.0f);

private:

};