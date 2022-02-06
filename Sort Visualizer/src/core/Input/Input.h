#pragma once
#include "glm/glm.hpp"
#include <unordered_map>

using MouseCode = uint8_t;
enum : MouseCode {
	MouseLeft   = 0,
	MouseRight  = 1,
	MouseMiddle = 2,
};

class Input {
private:
	static glm::vec2 m_MousPosition;
	static std::unordered_map<uint8_t, bool> m_processed;
	static bool m_lButtonPressed;
	static uint32_t m_Repeat;
public:
	static void ProcessInput(const int& button, const int& action, const int& mode);
	static void ProcessInput();
	static void SetMousePosition(double X, double Y);
	static glm::vec2 GetMousePosition() { return m_MousPosition; }
};