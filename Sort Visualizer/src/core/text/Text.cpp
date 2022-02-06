#include "Text.h"
#include <GL/glew.h>
#include "core/Renderer.h"
#include <functional>
#include "core/Vertex.h"

Texture* Text::m_GlyphAtlas = NULL;
FT_Library Text::m_Init;
FT_Face    Text::m_Face;
std::map<GLchar, struct Character> Text::m_Characters;
glm::vec2 Text::m_GlyphAtlasSize;

struct Character {
    float      Offset;
    glm::ivec2 Size;      // Размеры глифа
    glm::ivec2 Bearing;   // Смещение верхней левой точки глифа  
    float      Layer;
    GLuint     Advance;   // Горизонтальное смещение до начала следующего глифа
};

Text::Text(std::string_view text) 
    :m_Text(text)
{
    CalculateTextSize();
}

Text::~Text() {
    FT_Done_Face(m_Face);   
    FT_Done_FreeType(m_Init); 
}

void Text::Init() {
    LoadFont();
    FT_Set_Pixel_Sizes(m_Face, 0, 20);
    LoadChars(255);
}

void Text::RenderText(float x, float y, const float& scale, const glm::vec4& color) {            
    // Iterate through all characters
    std::string_view::const_iterator c;
    for (c = m_Text.begin(); c != m_Text.end(); c++) {
        Character ch = m_Characters[*c];

        float xpos = x + (ch.Bearing.x * scale);
        float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;

        if (!ch.Size.x || !ch.Size.y)
            continue;
      
        Vertex vertex[4];
        vertex[0].Position = { xpos, ypos + h };
        vertex[0].TexCoords = {ch.Offset, 0};
        vertex[0].Color = color;
        vertex[0].TexID = ch.Layer;
        vertex[1].Position = { xpos + w, ypos + h};
        vertex[1].TexCoords = { ch.Offset + ch.Size.x / m_GlyphAtlasSize.x, 0 };
        vertex[1].Color = color;
        vertex[1].TexID = ch.Layer;
        vertex[2].Position = { xpos + w, ypos };
        vertex[2].TexCoords = { ch.Offset + ch.Size.x / m_GlyphAtlasSize.x, ch.Size.y / m_GlyphAtlasSize.y };
        vertex[2].Color = color;
        vertex[2].TexID = ch.Layer;
        vertex[3].Position = { xpos , ypos };
        vertex[3].TexCoords = { ch.Offset, ch.Size.y / m_GlyphAtlasSize.y };
        vertex[3].Color = color;
        vertex[3].TexID = ch.Layer;

        Renderer::CreateQuad(vertex);
       
        // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64)          
    }
}

glm::vec2 Text::GetTextSize() {
    return m_TextSize;
}

void Text::CalculateTextSize() {
    std::string_view::const_iterator c;
    int bearing = 0;
    for (c = m_Text.begin(); c != m_Text.end(); c++) {
        glm::vec2 GlyphSize = m_Characters[*c].Size;
        bearing = std::max(bearing, m_Characters[*c].Size.y - m_Characters[*c].Bearing.y);
        m_TextSize.x -= m_Characters[*c].Bearing.x;
        m_TextSize.x += m_Characters[*c].Size.x;
        m_TextSize.y = std::max(m_TextSize.y, GlyphSize.y);
    }
    m_TextSize.y -= bearing;
}

void Text::LoadFont() {	
	if (FT_Init_FreeType(&m_Init))
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
	if (FT_New_Face(m_Init, "resources/fonts/AdobeGothicStd-Bold.otf", 0, &m_Face))
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
}

void Text::LoadChars(const uint32_t& count) {
    //load chars to atlas
    uint32_t width = 0, height = 0;    
    for (uint32_t c = 0; c < count; c++) {
        if (FT_Load_Char(m_Face, c, FT_LOAD_RENDER)) {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;           
        }
        if (!m_Face->glyph->bitmap.width || !m_Face->glyph->bitmap.rows)
            continue;
        width += m_Face->glyph->bitmap.width + 1;
        height = std::max(height, m_Face->glyph->bitmap.rows);
    } //calculate size of texture

    m_GlyphAtlas = new Texture();
    m_GlyphAtlas->CreateTexture(GL_TEXTURE_2D, GL_ALPHA8, width, height, GL_ALPHA, NULL);
    m_GlyphAtlas->Bind(1);
    m_GlyphAtlasSize.x = width;
    m_GlyphAtlasSize.y = height;
     
    uint32_t offset = 0;
    for (uint32_t c = 0; c < count; c++) {
        // Load character glyph
        if (FT_Load_Char(m_Face, c, FT_LOAD_RENDER)) {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }

        if (!m_Face->glyph->bitmap.width || !m_Face->glyph->bitmap.rows)
            continue;

        m_GlyphAtlas->UpdateData(offset, 0, m_Face->glyph->bitmap.width, m_Face->glyph->bitmap.rows, m_Face->glyph->bitmap.buffer);
        
        // Now store character for later use
        Character character = {
            static_cast<float>(offset) / static_cast<float>(width),
            {m_Face->glyph->bitmap.width, m_Face->glyph->bitmap.rows},
            {m_Face->glyph->bitmap_left, m_Face->glyph->bitmap_top},
            1,
            m_Face->glyph->advance.x
        };
        m_Characters.insert(std::pair<char, Character>(c, character));  

        offset += m_Face->glyph->bitmap.width + 1;
    }
}