#include "Ghost.h"

//Dirt::Dirt() {}
Ghost::Ghost(glm::vec3 SpawnPoint, TextureData TXData, float TXNumber, float r, float g, float b, float alpha) :
	GameObject(SpawnPoint, TXData, TXNumber, r, g, b, alpha)// :
{
	std::cout << "Derived Ghost Object is created" << std::endl;
}

