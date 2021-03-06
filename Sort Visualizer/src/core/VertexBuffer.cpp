#include "VertexBuffer.h"
#include "ErrorCheck.h"

VertexBuffer::VertexBuffer() 
	:m_RendererID(0)
{
	GLCall(glGenBuffers(1, &m_RendererID));
}

VertexBuffer::~VertexBuffer() {
	GLCall(glDeleteBuffers(1, &m_RendererID));
}

void VertexBuffer::UpdateData(const void* data, unsigned int size) {
	GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, size, data));
}

void VertexBuffer::Create(const void* data, unsigned int size) {
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW));
}

void VertexBuffer::Bind() const {
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void VertexBuffer::Unbind() const {
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}