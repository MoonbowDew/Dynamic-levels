#include "Renderer.h"
#include <iostream>

void Renderer::Clear() const
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    shader.Bind();
    va.Bind();
    ib.Bind();
    glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr); 
}

void Renderer::DrawMultiple(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, int count) const
{
    shader.Bind();
    va.Bind();
    ib.Bind();
    glDrawElementsInstanced(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr, count);
}