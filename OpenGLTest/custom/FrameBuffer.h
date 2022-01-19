#pragma once
#include "ObjectBuffer.h"
#include "../stb_image.h"
#include "GameObject.h"
#include <string>
#include <memory>
#include <iostream>

class FrameBuffer : ObjectBuffer
{
private:
	unsigned int m_FrameBuffer_ID;
	//unsigned int m_TextureColorBuffer_ID; //stored in Texture class; useless
	unsigned int m_rbo_ID;
	//unsigned char* m_LocalImageBuffer = nullptr; // stored in Texture class; useless
	GameObject* FBGameObj;
public:
	FrameBuffer(GameObject* gameobj);//const void* data, unsigned int size);
	~FrameBuffer();

	//void BindRenderBuffer() const;

	void Bind() const;
	void Unbind() const;

	void CreateColorAttachmentTexture(const std::string& path);
	//void AttachTexture();
	void CreateRenderBuffer();
	void AttachRenderBuffer();
	void CheckIfComplete();

	inline GameObject* GetFBGameObj() { return FBGameObj; }

};