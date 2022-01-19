#pragma once
#include "ObjectBuffer.h"
class UVBuffer : public ObjectBuffer
{
private:
	unsigned int m_Renderer_ID;
public:
	UVBuffer(const void* data, unsigned int size);
	~UVBuffer();

	void Bind() const;
	void Unbind() const;
};