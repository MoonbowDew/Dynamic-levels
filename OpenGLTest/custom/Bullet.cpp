#include "Bullet.h"

//Dirt::Dirt() {}
Bullet::Bullet(glm::vec3 SpawnPoint, TextureData TXData, float TXNumber, float r, float g, float b, float alpha) :
	GameObject(SpawnPoint, TXData, TXNumber, r, g, b, alpha)
{
	//m_destinationX = x;
	//m_destinationY = y;
	std::cout << "Derived Ghost Object is created" << std::endl;
}

float Bullet::GetDestinationX()
{
	return m_destinationX;
}
float Bullet::GetDestinationY()
{
	return m_destinationY;
}

void Bullet::SetDestinationX(float x)
{
	m_destinationX = x;
}
void Bullet::SetDestinationY(float y)
{
	m_destinationY = y;
}