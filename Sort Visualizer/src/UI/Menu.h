#pragma once
#include "Visualizer/Visualizer.h"
#include "UI/Buttons.h"
#include <memory>

struct MenuState {
	bool m_reset;
	bool m_play;
	Visualizer::Sorts m_type;
};

class Menu {	
public:
	MenuState menuState;
	static std::unordered_map<std::string, Button*> m_Buttons;
private:
	static glm::vec2 lastSize;
	void CheckResize();
	void CheckButtons();
public:
	Menu();
	void CreateButtons();
	void Draw();
};