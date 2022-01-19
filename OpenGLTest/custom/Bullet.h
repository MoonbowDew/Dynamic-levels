#pragma once
#include "GameObject.h"

class Bullet : public GameObject
{
public:
	Bullet(glm::vec3 SpawnPoint, TextureData TXData, float TXNumber,  float r = 1.0f, float g = 1.0f, float b = 1.0f, float alpha = 1.0f);

	float GetDestinationX();
	float GetDestinationY();

	void SetDestinationX(float x);
	void SetDestinationY(float y);

private:
	float m_destinationX;
	float m_destinationY;
};