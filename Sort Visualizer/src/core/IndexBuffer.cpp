#include "IndexBuffer.h"
#include "ErrorCheck.h"

IndexBuffer::IndexBuffer()
	:m_RendererID(0), m_Count(0)
{
	GLCall(glGenBuffers(1, &m_RendererID));
}

IndexBuffer::~IndexBuffer() {
	GLCall(glDeleteBuffers(1, &m_RendererID));
}

void IndexBuffer::UpdateIB(const unsigned int* data, unsigned int count) {
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
	m_Count = count;
}

void IndexBuffer::Bind() const {
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}

void IndexBuffer::Unbind() const {
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}