#include "Menu.h"
#include "core/Renderer.h"

std::unordered_map<std::string, Button*> Menu::m_Buttons;
glm::vec2 Menu::lastSize;

Menu::Menu() {
	menuState.m_play  = false;
	menuState.m_reset = false;
	menuState.m_type  = Visualizer::Sorts::BUBLE;
}

void Menu::CheckResize() {
	if (lastSize.x != Renderer::m_Width || lastSize.y != Renderer::m_Height) {
		if (m_Buttons.size() > 0) {
			for (auto it = m_Buttons.begin(); it != m_Buttons.end(); it++) {
				delete it->second;
			}
			m_Buttons.clear();
		}
		CreateButtons();
		lastSize.x = Renderer::m_Width;
		lastSize.y = Renderer::m_Height;
	}
}

void Menu::CreateButtons() {
	uint32_t middle = Renderer::m_Width / 2;
	constexpr glm::vec2 size(120.0f, 30.0f);
	constexpr glm::vec4 color(1.0f);
	constexpr float gap = 5.0f;
	m_Buttons["Reset"]  = new Button("Reset" , size, { middle - size.x, 50.0f},                              color);
	m_Buttons["Play"]   = new Button("Play"  , size, { middle + gap, 50.0f },                                color);
	m_Buttons["Bubble"] = new Button("Bubble", size, { middle - (size.x + gap) * 2 - (size.x / 2) , 10.0f }, color);
	m_Buttons["Heap"]   = new Button("Heap"  , size, { middle - (size.x + gap) - (size.x / 2), 10.0f },      color);
	m_Buttons["Radix"]  = new Button("Radix" , size, { middle - (size.x / 2), 10.0f },                       color);	
	m_Buttons["Merge"]  = new Button("Merge" , size, { middle + (size.x / 2) + 5, 10.0f },                   color);
	m_Buttons["Quick"]  = new Button("Quick" , size, { middle + size.x * 1.5f + gap * 2, 10.0f },            color);
}

void Menu::CheckButtons() {
	if (!menuState.m_play) {
		menuState.m_play = m_Buttons["Play"]->m_State;
	}
	menuState.m_reset = m_Buttons["Reset"]->m_State;
	if (menuState.m_reset) {
		menuState.m_play = false;
		m_Buttons["Reset"]->m_State = false;
	}
	else if (m_Buttons["Bubble"]->m_State)
		menuState.m_type = Visualizer::Sorts::BUBLE;
	else if (m_Buttons["Heap"]->m_State)
		menuState.m_type = Visualizer::Sorts::HEAP;
	else if (m_Buttons["Radix"]->m_State)
		menuState.m_type = Visualizer::Sorts::RADIX;
	else if (m_Buttons["Merge"]->m_State)
		menuState.m_type = Visualizer::Sorts::MERGE;
	else if (m_Buttons["Quick"]->m_State)
		menuState.m_type = Visualizer::Sorts::QUICK;
	else
		menuState.m_type = menuState.m_type;
}

void Menu::Draw() {
	CheckResize();
	CheckButtons();

	for (const auto& i : m_Buttons)
		i.second->DrawButton();
}