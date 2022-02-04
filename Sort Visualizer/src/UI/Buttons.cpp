#include "Buttons.h"
#include "core/Renderer.h"
#include "core/Input/Input.h"

Button::Button(std::string_view name, const glm::vec2& Size, const glm::vec2& Position, const glm::vec4& Color) 
	: m_Text(name), m_Size(Size), m_Position(Position), m_Color(Color)
{
	m_State = false;                      
	m_Name = new Text(name);
}

bool Button::containes() {
	glm::vec2 pos = Input::GetMousePosition();
	if (pos.x > m_Position.x && pos.x < m_Position.x + m_Size.x && pos.y >m_Position.y && pos.y < m_Position.y + m_Size.y)
		return true;	
	return false;
}

bool Button::isPressed() {	
	return containes();
}

void Button::DrawButton() {
	Renderer::CreateQuad(m_Size, m_Position, m_Color, 0.0);
	glm::vec2 size = m_Name->GetTextSize();
	m_Name->RenderText(m_Position.x + (m_Size.x - size.x) / 2, m_Position.y + (m_Size.y - size.y) / 2, 1, { 0.0f, 0.0f, 0.0f, 1.0f });
}