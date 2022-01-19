#include "VertexArray.h"
#include "Renderer.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_RendererID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArray::AddBuffer(const ObjectBuffer& vb, int index)
{
	Bind();
	vb.Bind();

		//glEnableVertexAttribArray(index); // enable 0 index for a layout
		//glVertexAttribPointer(index, 2, GL_FLOAT, false,
			//0, NULL); 

}

void VertexArray::Bind() const
{
	glBindVertexArray(m_RendererID);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}
