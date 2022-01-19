#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <memory>
#include "../Texture.h"
#include "../VertexBufferLayout.h"
#include "UVBuffer.h"

#include <string>
#include <iostream>
#include <sstream>

#include "../stb_image.h"

#define _USE_MATH_DEFINES
#include <math.h>



struct TextureData
{
	unsigned int textureID;
	int textureWidth;
	int textureHeight;
};

//struct TextureCoordinates
//{
//	
//	int textureWidth;
//	int textureHeight;
//};

class GameObject
{
public:
	//GameObject();
	GameObject(glm::vec3 SpawnPoint, TextureData TXData, float TXNumber, float r = 1.0f, float g = 1.0f, float b = 1.0f, float alpha = 1.0f);
	glm::vec3 GetCurrentPosition();
	void SetCurrentPosition(glm::vec3 xPos);
	int GetXLength();
	int GetYLength();
	double GetYVelocity();

	int GetXBorder(); // length
	int GetYBorder(); // height


	void SetXPosition(float xPos);
	void SetYPosition(float yPos);
	void SetYVelocity(double yVel);

	//void LoadFrames(const char* filename);
	//void PlayFrames(Texture& spritetexture, VertexArray& rectangle, double deltatime);



	void SetAlphaChannel(float alpha);



	void Jump();

	void MoveLeft(float xPos);

	void MoveRight(float xPos);

	void MoveUp(float yPos);

	void SetSpriteResolution(float x, float y);

	void PrintCoords();


	inline unsigned int GetTextureID() { return m_textureID; }

	void SetTextureID(unsigned int ID);

	inline float GetAlphaChannel() { return m_alpha_channel; }
	inline float GetX() { return BottomLeft.x; }
	inline float GetY() { return BottomLeft.y; }
	inline float GetColorR() { return m_r; }
	inline float GetColorG() { return m_g; }
	inline float GetColorB() { return m_b; }
	inline float GetTXNumber() { return m_TXNumber; }


	inline glm::vec2 GetBottomLeft() { return BottomLeft; }
	inline glm::vec2 GetBottomRight() { return BottomRight; }
	inline glm::vec2 GetTopRight() { return TopRight; }
	inline glm::vec2 GetTopLeft() { return TopLeft; }
	inline float GetWidth() { return width; }
	inline float GetHeight() { return height; }
	virtual ~GameObject();

protected:
	glm::vec2 BottomLeft, BottomRight, TopRight, TopLeft;
	float width, height;

	//glm::vec4 m_Quat; // Quaterion

	unsigned int m_textureID;


	double m_YVelocity;

	float m_TXNumber;
	float m_r, m_g, m_b, m_alpha_channel;


	//bool m_reversedTexture; // horizontal reverse
	


	//for PlayFrames purposes
	//double anim_cursor = 0;
	//int current_frame_indx = 0;
	//int frames_count;
	//float speed = 0.005f;
	//std::vector<glm::vec4> frames;



};