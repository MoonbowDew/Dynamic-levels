#pragma once

#include "VertexBuffer.h"
#include "custom/ObjectBuffer.h"


class VertexArray
{
private:
	unsigned int m_RendererID;

public:
	VertexArray();
	~VertexArray();
	void AddBuffer(const ObjectBuffer& vb, int index);

	void Bind() const;
	void Unbind() const;
};