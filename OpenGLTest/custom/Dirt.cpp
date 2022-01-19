#include "Dirt.h"

//Dirt::Dirt() {}
Dirt::Dirt(glm::vec3 SpawnPoint, TextureData TXData, float TXNumber, float r, float g, float b, float alpha) :
	GameObject(SpawnPoint, TXData, TXNumber, r, g, b, alpha)// :
{
	std::cout << "Derived Dirt Object is created" << std::endl;
}

Dirt::~Dirt()
{
	std::cout << "Destructing derived Dirt Game Object \n"; //check if virtual destructor works properly
}