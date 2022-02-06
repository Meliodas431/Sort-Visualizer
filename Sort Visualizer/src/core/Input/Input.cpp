#include "Input.h"
#include "core/Renderer.h"
#include <GLFW/glfw3.h>
#include "UI/Buttons.h"
#include "UI/Menu.h"

glm::vec2 Input::m_MousPosition;
std::unordered_map<uint8_t, bool> Input::m_processed;
bool Input::m_lButtonPressed;
uint32_t Input::m_Repeat;

#include <iostream>
void Input::ProcessInput(const int& button, const int& action, const int& mode) {
	if (button == MouseLeft && action == GLFW_RELEASE) {
		m_processed.extract(MouseLeft);
		m_Repeat = 0;
	}
	else if (button == MouseLeft && action == GLFW_PRESS) {
		for (const auto& [name, button] : Menu::m_Buttons) {
			button->m_State = button->isPressed();
		}
		for (const auto& [name, slider] : Menu::m_Sliders) {
			slider->m_State = slider->isPressed();
		}
		m_Repeat++;
		m_processed[MouseLeft] = true;	
	}		
}

void Input::ProcessInput() {
	if (m_Repeat > 0) {
		for (const auto& [name, slider] : Menu::m_Sliders) {
			slider->m_State = slider->isPressed();
		}
		m_Repeat++;
	}
	else if (m_processed.find(MouseLeft) != m_processed.end()) {
		return;
	}	
	else if (m_lButtonPressed) {
		for (const auto& [name, button] : Menu::m_Buttons) {
			button->m_State = button->isPressed();
		}
		for (const auto& [name, slider] : Menu::m_Sliders) {
			slider->m_State = slider->isPressed();
		}
		m_Repeat++;
		m_processed[MouseLeft] = true;
	}
}

void Input::SetMousePosition(double X, double Y) {
	m_MousPosition.x = X;
	m_MousPosition.y = Renderer::m_Height - Y;
}