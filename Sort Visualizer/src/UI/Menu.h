#pragma once
#include "Visualizer/Visualizer.h"
#include "UI/Buttons.h"
#include <memory>
#include <string_view>

struct MenuState {
	bool reset, play;
	uint32_t delay, size;
	Visualizer::Sorts type;
};

class Menu {	
public:
	MenuState menuState;
	static std::unordered_map<std::string_view, Button*> m_Buttons;
	static std::unordered_map<std::string_view, Slider*> m_Sliders;
private:
	static glm::vec2 lastSize;
	void CheckResize();
	void CheckButtons();
	void CheckSelected();
public:
	Menu();
	void CreateButtons();
	void Draw();
};