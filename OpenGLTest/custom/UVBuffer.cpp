#include "UVBuffer.h"


UVBuffer::UVBuffer(const void* data, unsigned int size)
{
    glGenBuffers(1, &m_Renderer_ID); // create 1 buffer and assign "buffer" id (id 0l)
    glBindBuffer(GL_ARRAY_BUFFER, m_Renderer_ID); // select "buffer" id
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW); // copy data to buffer
}

UVBuffer::~UVBuffer()
{
    glDeleteBuffers(1, &m_Renderer_ID);
}

void UVBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_Renderer_ID); // select "buffer" id
}

void UVBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0); // select "buffer" id
}
