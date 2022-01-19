#include "Character.h"

//Dirt::Dirt() {}
Character::Character(glm::vec3 SpawnPoint, TextureData TXData, float TXNumber, float r, float g, float b, float alpha) :
	GameObject(SpawnPoint, TXData, TXNumber, r, g, b, alpha)// :
{
	m_reversedTexture = false;
	m_rotation_angle = 0.0f;
	TXcoords.BottomLeft = { 0.0f, 0.0f };
	TXcoords.BottomRight = { 1.0f, 0.0f };
	TXcoords.TopRight = { 1.0f, 1.0f };
	TXcoords.TopLeft = { 0.0f, 1.0f };
	std::cout << "Derived Character Object is created" << std::endl;
}

void Character::ReverseTexture()
{
	std::swap(TXcoords.BottomLeft, TXcoords.BottomRight);
	std::swap(TXcoords.TopLeft, TXcoords.TopRight);
}

bool Character::IsReversed()
{
	return m_reversedTexture;
}

void Character::SetReversed(bool rev)
{
	m_reversedTexture = rev;
}

TextureCoordinates Character::GetTextureCoordinates()
{
	return TXcoords;
}

void Character::ChangeSize(float x, float y) // fixed 6/29/2021 8:04 pm
{

	float rads = m_rotation_angle * M_PI / 180;
	float rads90 = (m_rotation_angle + 90.0f) * static_cast<float>(M_PI / 180.0f);
	width = width + x;
	height = height + y;


	BottomRight.x = BottomLeft.x + width * std::cos(rads);
	BottomRight.y = BottomLeft.y + height * std::sin(rads);

	TopLeft.x = BottomLeft.x + width * std::cos(rads90);
	TopLeft.y = BottomLeft.y + height * std::sin(rads90);

	TopRight.x = BottomRight.x + (TopLeft.x - BottomLeft.x); // сложение абсолютных с относительными
	TopRight.y = TopLeft.y + (BottomRight.y - BottomLeft.y);

}

void Character::SetRotationAngle(float angle) // // fixed 6/30/2021 11:51 am
{
	m_rotation_angle = angle;
	//this->PrintCoords();
	glm::vec2 ElementCenter((std::abs(TopLeft.x) + std::abs(BottomRight.x)) / 2,
		(std::abs(TopRight.y) + std::abs(BottomLeft.y)) / 2); // центр квадрата при любом повороте
	//float widthTmp = std::sqrt(std::pow((BottomRight.x - BottomLeft.x), 2.0) + std::pow((BottomRight.y - BottomLeft.y), 2.0));
	//float heightTmp = widthTmp;
	//coords before rotation:
	float HalfWidth = width / 2;
	float HalfHeight = height / 2;
	glm::vec2 BottomLeftNoRotaion(ElementCenter.x - HalfWidth, ElementCenter.y - HalfHeight);
	glm::vec2 BottomRightNoRotaion(ElementCenter.x + HalfWidth, ElementCenter.y - HalfHeight);
	glm::vec2 TopRightNoRotaion(ElementCenter.x + HalfWidth, ElementCenter.y + HalfHeight);
	glm::vec2 TopLeftNoRotaion(ElementCenter.x - HalfWidth, ElementCenter.y + HalfHeight);

	//glm::vec2 PivotPoint(BottomLeft.x - width/2, BottomLeft.y - height/ 2);
	double rads = angle * M_PI / 180;
	// translate to origin
	glm::vec2 BottomLeftInit = glm::vec2(-HalfWidth, -HalfHeight);
	glm::vec2 BottomRightInit = glm::vec2(BottomLeftInit.x + width, BottomLeftInit.y);
	glm::vec2 TopRightInit = glm::vec2(BottomLeftInit.x + width, BottomLeftInit.y + height);
	glm::vec2 TopLeftInit = glm::vec2(BottomLeftInit.x, BottomLeftInit.y + height);

	//rotate
	long tmp1 = BottomLeftInit.x * std::cos(rads) - BottomLeftInit.y * std::sin(rads);
	long tmp2 = BottomLeftInit.x * std::sin(rads) + BottomLeftInit.y * std::cos(rads);

	BottomLeftInit.x = tmp1;
	BottomLeftInit.y = tmp2;

	tmp1 = BottomRightInit.x * std::cos(rads) - BottomRightInit.y * std::sin(rads);
	tmp2 = BottomRightInit.x * std::sin(rads) + BottomRightInit.y * std::cos(rads);

	BottomRightInit.x = tmp1;
	BottomRightInit.y = tmp2;

	tmp1 = TopRightInit.x * std::cos(rads) - TopRightInit.y * std::sin(rads);
	tmp2 = TopRightInit.x * std::sin(rads) + TopRightInit.y * std::cos(rads);

	TopRightInit.x = tmp1;
	TopRightInit.y = tmp2;

	tmp1 = TopLeftInit.x * std::cos(rads) - TopLeftInit.y * std::sin(rads);
	tmp2 = TopLeftInit.x * std::sin(rads) + TopLeftInit.y * std::cos(rads);

	TopLeftInit.x = tmp1;
	TopLeftInit.y = tmp2;


	BottomLeft = BottomLeftNoRotaion;
	BottomRight = BottomRightNoRotaion;
	TopRight = TopRightNoRotaion;
	TopLeft = TopLeftNoRotaion;



	BottomLeft += BottomLeftInit + glm::vec2(HalfWidth, HalfHeight);
	BottomRight += BottomRightInit + glm::vec2(-HalfWidth, HalfHeight);
	TopRight += TopRightInit + glm::vec2(-HalfWidth, -HalfHeight);
	TopLeft += TopLeftInit + glm::vec2(HalfWidth, -HalfHeight);

}