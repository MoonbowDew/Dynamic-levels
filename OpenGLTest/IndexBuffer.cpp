#include "IndexBuffer.h"
#include "Renderer.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
    : m_Count(count)
{
    glGenBuffers(1, &m_Renderer_ID); // create 1 buffer and assign "buffer" id (id 0l)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Renderer_ID); // select "buffer" id
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW); // copy data to buffer
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &m_Renderer_ID);
}

void IndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Renderer_ID); // select "buffer" id
}

void IndexBuffer::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // select "buffer" id
}
