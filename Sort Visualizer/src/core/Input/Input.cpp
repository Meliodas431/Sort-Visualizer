#include "Input.h"
#include "core/Renderer.h"
#include <GLFW/glfw3.h>
#include "UI/Buttons.h"
#include "UI/Menu.h"
glm::vec2 Input::m_MousPosition;
std::unordered_map<uint8_t, bool> Input::m_processed;

void Input::ProcessInput(const int& button, const int& action, const int& mode) {
	if (button == MouseLeft && action == GLFW_RELEASE)
		m_processed.extract(MouseLeft);
	if (m_processed.find(button) != m_processed.end()) {	
		return;
	}
	else if (button == MouseLeft && action == GLFW_PRESS) {
		for (const auto& [name, button] : Menu::m_Buttons) {
			bool a = button->isPressed();
			button->m_State = a;
		}
		m_processed[MouseLeft] = true;
	}	
}

void Input::SetMousePosition(double X, double Y) {
	m_MousPosition.x = X;
	m_MousPosition.y = Renderer::m_Height - Y;
}