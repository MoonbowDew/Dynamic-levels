#pragma once
#include "custom/ObjectBuffer.h"

class VertexBuffer : public ObjectBuffer
{
private:
	unsigned int m_Renderer_ID;
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

	GLuint GetID() const;
};