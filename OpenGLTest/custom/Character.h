#pragma once
#include "GameObject.h"

struct Point
{
	float x, y;
};

struct TextureCoordinates // relative
{
	Point BottomLeft;
	Point BottomRight;
	Point TopRight;
	Point TopLeft;
};

class Character : public GameObject
{
public:
	Character(glm::vec3 SpawnPoint, TextureData TXData, float TXNumber, float r = 1.0f, float g = 1.0f, float b = 1.0f, float alpha = 1.0f);
	//Dirt(float xAbs, float yAbs);
	void ReverseTexture();
	bool IsReversed();
	void SetReversed(bool rev);
	TextureCoordinates GetTextureCoordinates();

	void ChangeSize(float x, float y);
	void SetRotationAngle(float angle);

	//std::vector<std::shared_ptr<Dirt>> GetpathElementCoords();
private:
	bool m_reversedTexture;
	float m_rotation_angle;
	TextureCoordinates TXcoords;
};