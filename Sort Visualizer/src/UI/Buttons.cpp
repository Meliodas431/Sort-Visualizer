#include "Buttons.h"
#include "core/Renderer.h"
#include "core/Input/Input.h"

Button::Button(std::string_view Name, const glm::vec2& Size, const glm::vec2& Position, const glm::vec4& Color) {
	m_Name = Name;
	m_Size = Size;
	m_Position = Position;
	m_Color = Color;
	m_State = false;                      
	m_Text = new Text(Name);
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
	glm::vec2 size = m_Text->GetTextSize();
	m_Text->RenderText(m_Position.x + (m_Size.x - size.x) / 2, m_Position.y + (m_Size.y - size.y) / 2, 1, { 0.0f, 0.0f, 0.0f, 1.0f });
}

uint32_t Slider::m_Current;

Slider::Slider(std::string_view Name, const glm::vec2& Size, const glm::vec2& Position, const glm::vec4& Color)
	: m_Min(10), m_Max(300), m_Step(1)
{
	m_Current  = 200;
	m_Name     = Name;
	m_Text = new Text(Name);
	SetSlider(Size, Position, Color);
}

bool Slider::containes() {
	glm::vec2 pos = Input::GetMousePosition();
	if (pos.x > m_P && pos.x < m_P + m_S && pos.y > m_Position.y && pos.y < m_Position.y + m_Size.y)
		return true;
	return false;
}

bool Slider::isPressed() {
	bool con = containes();
	if (con)
		SetSliderPosition();
	return con;
}

void Slider::DrawButton() {
	Renderer::CreateQuad(m_Size, m_Position, m_Color, 0.0);
	Renderer::CreateQuad({ m_S, m_Size.y }, { m_P , m_Position.y }, m_SliderColor, 0.0);
	glm::vec2 size = m_Text->GetTextSize();
	m_Text->RenderText(m_Position.x + (m_Size.x - size.x) / 2, m_Position.y + (m_Size.y - size.y) / 2, 1, { 0.0f, 0.0f, 0.0f, 1.0f });
}

void Slider::SetSlider(const glm::vec2& Size, const glm::vec2& Position, const glm::vec4& Color) {
	m_Size = Size;
	m_S = Size.x / 6;
	m_P = Size.x - m_S;
	m_Multiplier = m_P / static_cast<float>(m_Max - m_Min);
	m_P = m_Current * m_Multiplier;
	m_P += Position.x;

	m_Position = Position;
	m_Color = Color;	
}

#include <iostream>
void Slider::SetSliderPosition() {
	static float difference;
	static float rPos = m_Position.x + m_Size.x - m_S;
	glm::vec2 pos = Input::GetMousePosition();
	if (!m_State) {	
		difference = pos.x - m_P;
	}
	float newPos = pos.x - difference;
	if (newPos > m_Position.x && newPos < rPos) {
		m_P = newPos;
	}
	else {
		difference = pos.x - m_P;
		m_P = m_P;
	}
	m_Current = static_cast<uint32_t>(m_P - m_Position.x) / m_Multiplier + m_Min;
	std::cout << m_Current << std::endl;
}

void Slider::SetRange(const uint32_t& min, const uint32_t& max) {
	m_Min = min;
	m_Max = max;
}