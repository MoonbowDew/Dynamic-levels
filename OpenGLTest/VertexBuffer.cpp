#include "VertexBuffer.h"
#include "Renderer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
    glGenBuffers(1, &m_Renderer_ID); // create 1 buffer and assign "buffer" id (id 0l)
    glBindBuffer(GL_ARRAY_BUFFER, m_Renderer_ID); // select "buffer" id
    //glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW); // copy data to buffer
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW); // copy data to buffer
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &m_Renderer_ID);
}

void VertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_Renderer_ID); // select "buffer" id
}

void VertexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0); // select "buffer" id
}

GLuint VertexBuffer::GetID() const
{
    return m_Renderer_ID;
}
