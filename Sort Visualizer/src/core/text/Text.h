#pragma once
#include <ft2build.h>
#include FT_FREETYPE_H

#include "Headers.h"
#include "core/Texture.h"

#include "glm/glm.hpp"


class Text {
private:
	static FT_Library m_Init;
	static FT_Face    m_Face;
	static std::map<GLchar, struct Character> m_Characters;
	static Texture*   m_GlyphAtlas;
	static glm::vec2  m_GlyphAtlasSize;
	glm::vec2 m_TextSize;
	std::string_view m_Text;
public:
	Text(std::string_view text);
	~Text();
	static void Init();
	void RenderText(float x, float y, const float& scale, const glm::vec4& color);
	glm::vec2 GetTextSize();
	void CalculateTextSize();
private:
	static void LoadFont();
	static void LoadChars(const uint32_t& count);
};
