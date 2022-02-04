#pragma once
#include "glm/glm.hpp"
#include <string_view>
#include "core/text/Text.h"

class Button {
public:
	std::string_view m_Text;
	bool             m_State;
private:
	glm::vec2 m_Size;
	glm::vec2 m_Position;
	glm::vec4 m_Color;
	Text* m_Name;
public:
	Button(std::string_view text, const glm::vec2& Size, const glm::vec2& Position, const glm::vec4& Color);
	bool containes();
	bool isPressed();
	void DrawButton();
}; 