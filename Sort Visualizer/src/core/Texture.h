#pragma once
#include "ErrorCheck.h"
#include "Headers.h"

class Texture {
public:
	std::string m_Type;	
	uint8_t* m_LocalBuffer;
private:
	uint32_t m_RendererID;
	uint32_t m_TextureFormat;
	int m_Width, m_Height, m_BPP;
public:
	Texture();
	~Texture();

	void CreateTexture(const uint32_t& type, const uint32_t& internalFormat, const uint32_t& width, const uint32_t& height,
		const uint32_t& format, const void* buffer);
	void UpdateData(const uint32_t& offset_x, const uint32_t& offset_y, const uint32_t& width, const uint32_t& height,const void* data);
	void Bind(const uint32_t& slot = 0) const;
	void Unbind();

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }
	inline uint32_t GetID() const { return m_RendererID; }
	inline std::string GetType() const { return m_Type; }
};
