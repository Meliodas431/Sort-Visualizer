#pragma once

class VertexBuffer {
private:
	unsigned int m_RendererID;
public:
	VertexBuffer();
	~VertexBuffer();
	void UpdateData(const void* data, unsigned int size);
	void Create(const void* data, unsigned int size);
	void Bind() const;
	void Unbind() const;
};