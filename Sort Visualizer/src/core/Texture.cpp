#include "Texture.h"


Texture::Texture()
	: m_RendererID(0), m_TextureFormat(GL_TEXTURE_2D), m_Width(0), m_Height(0), m_BPP(0), m_LocalBuffer(NULL)
{
}

Texture::~Texture() {
	GLCall(glDeleteTextures(1, &m_RendererID));
}

void Texture::CreateTexture(const uint32_t& type, const uint32_t& internalFormat, const uint32_t& width, const uint32_t& height,
	 const uint32_t& format, const void* data)
{
	m_TextureFormat = type;
	GLCall(glGenTextures(1, &m_RendererID));
	GLCall(glBindTexture(m_TextureFormat, m_RendererID));
	GLCall(glTexParameteri(m_TextureFormat, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(m_TextureFormat, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(m_TextureFormat, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(m_TextureFormat, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	GLCall(glTexImage2D(m_TextureFormat, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data));
	GLCall(glBindTexture(m_TextureFormat, 0));
}

void Texture::UpdateData(const uint32_t& offset_x, const uint32_t& offset_y, const uint32_t& width, const uint32_t& height, const void* data) {
	GLCall(glTexSubImage2D(m_TextureFormat, 0, offset_x, offset_y, width, height, GL_ALPHA, GL_UNSIGNED_BYTE, data));
}

void Texture::Bind(const uint32_t& slot) const {
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(m_TextureFormat, m_RendererID));
}

void Texture::Unbind() {
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}