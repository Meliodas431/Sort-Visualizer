#include "Menu.h"
#include "core/Renderer.h"

std::unordered_map<std::string_view, Button*> Menu::m_Buttons;
std::unordered_map<std::string_view, Slider*> Menu::m_Sliders;
glm::vec2 Menu::lastSize;

Menu::Menu() {
	menuState.play  = false;
	menuState.reset = false;
	menuState.size  = 200;
	menuState.delay = 40;
	menuState.type  = Visualizer::Sorts::BUBLE;
}

void Menu::CheckResize() {
	if (lastSize.x != Renderer::m_Width || lastSize.y != Renderer::m_Height) {
		if (m_Buttons.size() > 0) {
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
	m_Sliders["Size"]   = new Slider("Size",  { 250, 25 }, { 20, 50 }, { 1.0, 1.0, 1.0, 1.0 });
	m_Sliders["Delay"]  = new Slider("Delay", { 250, 25 }, { 20, 10 }, { 1.0, 1.0, 1.0, 1.0 });
	m_Sliders["Delay"]->SetRange(1, 300);
}

void Menu::CheckButtons() {
	if (m_Sliders["Size"]->m_State)
		menuState.size = m_Sliders["Size"]->m_Current;
	if (m_Sliders["Delay"]->m_State)
		menuState.delay = m_Sliders["Size"]->m_Current;
	if (!menuState.play) {
		menuState.play = m_Buttons["Play"]->m_State;
	}
	menuState.reset = m_Buttons["Reset"]->m_State;
	if (menuState.reset) {
		menuState.play = false;
		m_Buttons["Reset"]->m_State = false;
	}
	else if (m_Buttons["Bubble"]->m_State)
		menuState.type = Visualizer::Sorts::BUBLE;
	else if (m_Buttons["Heap"]->m_State)
		menuState.type = Visualizer::Sorts::HEAP;
	else if (m_Buttons["Radix"]->m_State)
		menuState.type = Visualizer::Sorts::RADIX;
	else if (m_Buttons["Merge"]->m_State)
		menuState.type = Visualizer::Sorts::MERGE;
	else if (m_Buttons["Quick"]->m_State)
		menuState.type = Visualizer::Sorts::QUICK;
	else
		menuState.type = menuState.type;

	CheckSelected();
}

void Menu::CheckSelected() {
	for (auto& i : m_Buttons) {
		bool selected = i.second->containes();
		if (selected)
			i.second->SetColor({ 0.3, 0.7, 1.0, 1.0 });
		else
			i.second->SetColor({ 1.0, 1.0, 1.0, 1.0 });
	}
	for (auto& i : m_Sliders) {
		bool selected = i.second->containes();
		if (selected) 
			i.second->SetColor({ 0.3, 0.7, 1.0, 1.0 });
		else {
			glm::vec4 color = { glm::vec3(i.second->GetColor()) - glm::vec3(0.3), 1.0 };
			i.second->SetColor(color);
		}
	}
}

void Menu::Draw() {
	CheckResize();
	CheckButtons();
	
	for (const auto& i : m_Buttons)
		i.second->DrawButton();
	for (const auto& i : m_Sliders)
		i.second->DrawButton();
}