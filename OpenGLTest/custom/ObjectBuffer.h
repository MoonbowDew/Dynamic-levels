#pragma once
#include <GL/glew.h>

class ObjectBuffer
{
public:
	virtual void Bind() const = 0;
	virtual void Unbind() const = 0;
};