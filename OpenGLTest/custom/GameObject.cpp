#pragma once
#include "GameObject.h"

	


	GameObject::GameObject(glm::vec3 SpawnPoint, /*const void* VertexData,*/ TextureData TXData, float TXNumber, float r, float g, float b, float alpha)
		: BottomLeft(SpawnPoint.x, SpawnPoint.y), BottomRight(SpawnPoint.x + TXData.textureWidth, SpawnPoint.y),
		TopRight(SpawnPoint.x + TXData.textureWidth, SpawnPoint.y + TXData.textureHeight), TopLeft(SpawnPoint.x, SpawnPoint.y + TXData.textureHeight), width (BottomRight.x - BottomLeft.x), height(TopLeft.y - BottomLeft.y), m_textureID(TXData.textureID), m_YVelocity(0),
		m_TXNumber(TXNumber),
		m_r(r), m_g(g), m_b(b), m_alpha_channel(alpha)
	{
		std::cout << "Base Object is created" << std::endl;

	}



	glm::vec3 GameObject::GetCurrentPosition()
	{
		return glm::vec3(BottomLeft, 0.0f);
	}	

	void GameObject::SetCurrentPosition(glm::vec3 newVec3)
	{
		BottomLeft.x = newVec3.x;
		BottomLeft.y = newVec3.y;
		BottomRight.x = newVec3.x + width;
		BottomRight.y = newVec3.y;

		TopRight.x = newVec3.x + width;
		TopRight.y = newVec3.y + height;
		TopLeft.x = newVec3.x;
		TopLeft.y = newVec3.y + height;
	}

	void GameObject::SetXPosition(float xPos)// fixed 6 / 29 / 2021 6:38 pm
	{
		BottomLeft.x = xPos;
		BottomRight.x = xPos + width;
		TopRight.x = xPos + width;
		TopLeft.x = xPos;
	}

	void GameObject::SetYPosition(float yPos) // fixed 6/29/2021 6:39 pm
	{
		BottomLeft.y = yPos;
		BottomRight.y = BottomLeft.y;
		TopRight.y = BottomLeft.y + height;
		TopLeft.y = BottomLeft.y + height;

	}

	void GameObject::PrintCoords()
	{
		std::cout << "BottomLeft: " << BottomLeft.x << " " << BottomLeft.y << "\n"
			<< "BottomRight: " << BottomRight.x << " " << BottomRight.y << "\n"
			<< "TopRight: " << TopRight.x << " " << TopRight.y << "\n"
			<< "TopLeft: " << TopLeft.x << " " << TopLeft.y << "\n"
			<< "Width: " << width << " "  << "\n"
			<< "Height: " << height << " " << "\n\n";
	}

	void GameObject::SetTextureID(unsigned int ID)
	{
		m_textureID = ID;
	}


	int GameObject::GetXLength()
	{
		return BottomRight.x - BottomLeft.x;
	}

	int GameObject::GetYLength()
	{
		return TopLeft.y - BottomLeft.y;
	}

	int GameObject::GetXBorder()
	{
		return BottomRight.x - BottomLeft.x;
	}

	int GameObject::GetYBorder()
	{
		return TopLeft.y - BottomLeft.y;
	}

	void GameObject::MoveLeft(float xPos)
	{
		BottomLeft.x -= xPos;
		BottomRight.x -= xPos;
		TopRight.x -= xPos;
		TopLeft.x -= xPos;
	}

	void GameObject::MoveRight(float xPos)
	{
		BottomLeft.x += xPos;
		BottomRight.x += xPos;
		TopRight.x += xPos;
		TopLeft.x += xPos;
	}

	void GameObject::MoveUp(float yPos)
	{
		BottomLeft.y += yPos;
		BottomRight.y += yPos;
		TopRight.y += yPos;
		TopLeft.y += yPos;
	}

	void GameObject::SetSpriteResolution(float x, float y) // fixed 6/29/2021 8:12 pm
	{
		float widthTmp = x / width;
		float heightTmp = y / height;
		width = width * widthTmp;
		height = height * heightTmp;

		BottomRight.x = BottomLeft.x + width;
		TopRight.x = BottomLeft.x + width;
		TopRight.y = BottomLeft.y + height;
		TopLeft.y = BottomLeft.y + height;
	}




	
	
	double GameObject::GetYVelocity()
	{
		return m_YVelocity;
	}
	
	void GameObject::SetYVelocity(double yVel)
	{
		m_YVelocity = yVel;
	}
	
	void GameObject::Jump()
	{
		m_YVelocity = 420;
	}

	void GameObject::SetAlphaChannel(float alpha)
	{
		m_alpha_channel = alpha;
	}



	GameObject::~GameObject()
	{
		std::cout << "Destructing base Game Object \n";
	}

	