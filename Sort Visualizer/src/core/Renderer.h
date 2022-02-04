#pragma once
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Vertex.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

struct Data {
	static const uint32_t MaxQuadCount{ 3000 };
	static const uint32_t MaxVertexCount{ MaxQuadCount * 4 };
	static const uint32_t MaxIndexCount{ MaxQuadCount * 6 };

	uint32_t QuadIndexCount;
	uint32_t QuadCount;
	uint32_t Indeces[MaxIndexCount];

	VertexArray*  m_VA;
	VertexBuffer* m_VB;
	IndexBuffer*  m_IB;
	Texture*      m_Texture;
	Texture*      m_GlyphAtlas;
	Shader*       m_Shader;
	
	Vertex* QuadVertexBufferBase ;
	Vertex* QuadVertexBuffer;

	glm::vec4 localPosition[4];
};

class Renderer {
private:
	static glm::mat4 m_Proj;
public:
	static uint32_t m_Width, m_Height;
private:
	static void StartBatch();
	static void NextBatch();
	static void Flush();
	static void ShutDown();
public:
	static void Init();
	static void WindowResize(uint32_t Width, uint32_t Height);
	static void BeginScene();
	static void EndScene();
	static void Clear();
	static void CreateTexture(const glm::vec2& Size);
	static void CreateQuad(const glm::vec2& Size, const glm::vec2& Position, const glm::vec4& Color, const float& ID);
	static void CreateQuad(const Vertex* vertex);
};