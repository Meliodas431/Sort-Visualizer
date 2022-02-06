#pragma once
#include "glm/glm.hpp"
#include <string_view>
#include "core/text/Text.h"

class BaseButton {
public:
	std::string_view m_Name;
	bool             m_State;
protected:
	glm::vec2 m_Size;
	glm::vec2 m_Position;
	glm::vec4 m_Color;
	Text*     m_Text;
public:	
	BaseButton() {}
	BaseButton(std::string_view Name, const glm::vec2& Size, const glm::vec2& Position, const glm::vec4& Color) 
		: m_Name(Name), m_Size(Size), m_Position(Position), m_Color(Color) {}
	virtual ~BaseButton() {}
	//static void Init(GLFWwindow* wnd) { window = wnd; }
	virtual bool containes() { return false; }
	virtual bool isPressed() { return false; }
	inline void SetColor(const glm::vec4& color) { m_Color = color; }
	//void ProcessInput();
	virtual void DrawButton() {}
	virtual void ProcessInput() {}
	virtual void OnRender(){}
};

class Button : public BaseButton {
public:
	Button(std::string_view Name, const glm::vec2& Size, const glm::vec2& Position, const glm::vec4& Color);
	bool containes();
	bool isPressed();
	void SetColor(const glm::vec4& color) { m_Color = color; }
	void DrawButton();
}; 

class Slider : public BaseButton {
public:
	static uint32_t m_Current;
private:
	float m_P, m_S, m_Multiplier;
	glm::vec4 m_SliderColor;
	uint32_t m_Min, m_Max, m_Step;
public:
	Slider(std::string_view Name, const glm::vec2& Size, const glm::vec2& Position, const glm::vec4& Color);
	~Slider() {}
	bool containes() override;
	bool isPressed() override;
	void DrawButton() override;
	void SetSlider(const glm::vec2& Size, const glm::vec2& Position, const glm::vec4& Color);
	void SetColor(const glm::vec4& color) { m_SliderColor = color; }
	glm::vec4& GetColor() { return m_Color; }
	void SetSliderPosition();
	void SetRange(const uint32_t& min, const uint32_t& max);
};