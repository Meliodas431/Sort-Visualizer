#include "Renderer.h"
#include "ErrorCheck.h"
#include <iostream>

static Data s_Data;

glm::mat4 Renderer::m_Proj  = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f);
uint32_t Renderer::m_Width  = 1280u;
uint32_t Renderer::m_Height = 720u;

void Renderer::Init() {
    s_Data.localPosition[0] = { 0.0f, 0.0f, 0.0f, 1.0f };
    s_Data.localPosition[1] = { 1.0f, 0.0f, 0.0f, 1.0f };
    s_Data.localPosition[2] = { 1.0f, 1.0f, 0.0f, 1.0f };
    s_Data.localPosition[3] = { 0.0f, 1.0f, 0.0f, 1.0f };

    VertexBufferLayout layout;
    layout.Push<float>(2);
    layout.Push<float>(2);
    layout.Push<float>(1);
    layout.Push<float>(4);

    uint32_t offset = 0;
    for (uint32_t i = 0; i < s_Data.MaxIndexCount; i += 6) {
        s_Data.Indeces[i + 0] = 0 + offset;
        s_Data.Indeces[i + 1] = 1 + offset;
        s_Data.Indeces[i + 2] = 2 + offset;
        s_Data.Indeces[i + 3] = 2 + offset;
        s_Data.Indeces[i + 4] = 3 + offset;
        s_Data.Indeces[i + 5] = 0 + offset;
        offset += 4;
    };
    s_Data.QuadVertexBufferBase = new Vertex[s_Data.MaxVertexCount];
    
    s_Data.m_VB      = new VertexBuffer();
    s_Data.m_VA      = new VertexArray();
    s_Data.m_IB      = new IndexBuffer();
    s_Data.m_Texture = new Texture();
    s_Data.m_Shader  = new Shader();

    s_Data.m_VB->Create(nullptr, layout.GetStride() * s_Data.MaxVertexCount);
    s_Data.m_VA->AddBuffer(*s_Data.m_VB, layout);
    s_Data.m_IB->UpdateIB(s_Data.Indeces, s_Data.MaxIndexCount);
                      
    constexpr uint8_t color = 0xFFFFFFFF;
    s_Data.m_Texture->CreateTexture(GL_TEXTURE_2D, GL_ALPHA8, 1, 1, GL_ALPHA, &color);
    s_Data.m_Texture->Bind(0);

    s_Data.m_Shader->Create("resources/shader/Basic.shader");
    s_Data.m_Shader->Bind();
    glm::mat4 mvp = m_Proj;
    s_Data.m_Shader->SetUniformMat4f("m_MVP", mvp);
    constexpr int id[2] = { 0, 1 };
    s_Data.m_Shader->SetUniform1iv("u_text", 2, id);
}

void Renderer::WindowResize(uint32_t Width, uint32_t Height) {
    glViewport(0, 0, Width, Height);
    m_Proj   = glm::ortho(0.0f, static_cast<float>(Width), 0.0f, static_cast<float>(Height), -1.0f, 1.0f);
    m_Width  = Width;
    m_Height = Height;
    glm::mat4 mvp = m_Proj;
    s_Data.m_Shader->SetUniformMat4f("m_MVP", mvp);
}

void Renderer::CreateQuad(const glm::vec2& Size, const glm::vec2& Position, const glm::vec4& Color, const float& id) {
    if (s_Data.QuadIndexCount >= s_Data.MaxIndexCount)
        NextBatch();

    constexpr uint32_t vertexCount = 4;
    for (uint32_t i = 0; i < vertexCount; i++) {
        s_Data.QuadVertexBuffer->Position  = { (s_Data.localPosition[i].x * Size.x + Position.x), (s_Data.localPosition[i].y * Size.y + Position.y) };
        s_Data.QuadVertexBuffer->TexCoords = s_Data.localPosition[i];
        s_Data.QuadVertexBuffer->TexID     = id;
        s_Data.QuadVertexBuffer->Color     = { Color.r, Color.g, Color.b, Color.a };
        s_Data.QuadVertexBuffer++;
    }
    s_Data.QuadIndexCount += 6;
    s_Data.QuadCount++;
}

void Renderer::CreateQuad(const Vertex* vertecies) {
    if (s_Data.QuadIndexCount >= s_Data.MaxIndexCount)
        NextBatch();

    constexpr uint32_t vertexCount = 4;
    for (uint32_t i = 0; i < vertexCount; i++) {
        s_Data.QuadVertexBuffer->Position  = vertecies->Position;
        s_Data.QuadVertexBuffer->TexCoords = vertecies->TexCoords;
        s_Data.QuadVertexBuffer->TexID     = vertecies->TexID;
        s_Data.QuadVertexBuffer->Color     = vertecies->Color;
        vertecies++;
        s_Data.QuadVertexBuffer++;
    }
    s_Data.QuadIndexCount += 6;
    s_Data.QuadCount++; 
}

void Renderer::Clear() {
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::CreateTexture(const glm::vec2& Size) {
    s_Data.m_Texture->CreateTexture(GL_TEXTURE_2D, GL_ALPHA8, Size.x, Size.y, GL_ALPHA, NULL);
}

void Renderer::StartBatch() {
    s_Data.QuadIndexCount = 0;
    s_Data.QuadVertexBuffer = s_Data.QuadVertexBufferBase; //ptr -> start data
}

void Renderer::NextBatch() {
    Flush();
    StartBatch();
}

void Renderer::Flush() {
    if (s_Data.QuadIndexCount == 0)
        return;

    uint32_t dataSize = (uint32_t)((uint8_t*)s_Data.QuadVertexBuffer - (uint8_t*)s_Data.QuadVertexBufferBase);

    s_Data.m_VB->UpdateData(s_Data.QuadVertexBufferBase, dataSize);
    s_Data.m_IB->UpdateIB(s_Data.Indeces, s_Data.QuadIndexCount);
}

void Renderer::BeginScene() {
    StartBatch();
}

void Renderer::EndScene() {
    Flush();

    s_Data.m_Shader->Bind();
    s_Data.m_VA->Bind();
    s_Data.m_IB->Bind();

    GLCall(glDrawElements(GL_TRIANGLES, s_Data.QuadIndexCount, GL_UNSIGNED_INT, nullptr));
}

void Renderer::ShutDown() {
    delete   s_Data.m_VA;
    delete   s_Data.m_VB;
    delete   s_Data.m_IB;
    delete   s_Data.m_Shader;
    delete[] s_Data.QuadVertexBufferBase;
}