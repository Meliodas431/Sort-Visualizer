#include "Visualizer.h"
#include "core/Renderer.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

std::mutex Visualizer::m_mutex;
std::vector<State> Visualizer::m_states;
uint32_t Visualizer::m_statesIndex;

Visualizer::Visualizer(Array& array)
	: m_index(0), m_delay(20), m_once(false), m_done(false)
{	
	vec = &array.GetArray();
	m_states.reserve(1000);
	Reset();
}

void Visualizer::CreateStates(const Sorts& sortType) {
	if (!m_once) {
		m_statesIndex = 0;
		m_once = true;
		switch (sortType) {
		case Visualizer::Sorts::RADIX:
			RadixSort256(vec);
			break;
		case Visualizer::Sorts::BUBLE:
			BubbleSort(vec);
			break;
		case Visualizer::Sorts::HEAP:
			HeapSort(vec);
			break; 
		case Visualizer::Sorts::MERGE:
			TopDownMergeSort(vec);
			break;
		case Visualizer::Sorts::QUICK:
			QuickSortEntry(vec);
			break;
		default:
			RadixSort256(vec);
			break;
		}
	}
}

void Visualizer::CreateGraph(const uint32_t& index) {
	auto state = GetState(index);
	static uint32_t length = state.rebuilded.size();
	static std::vector<uint32_t> array;
	if (array.size() == 0 || !state.rebuilded.empty())
		array = state.rebuilded;
	static int LastStep = -1;
	bool SameStep = LastStep == state.step;
	if (state.swap && !SameStep) {
		LastStep = state.step;
		std::swap(array[state.first_value], array[state.second_value]);
	}

	constexpr float maxNumber = 999.0f;
	constexpr float gap       = 2.0f;
	constexpr float offset    = 200.0f;
	float step = (static_cast<float>(Renderer::m_Height) - 90.0f) / maxNumber;
	float s = (Renderer::m_Width - offset - (length * gap)) / length ;

	glm::vec2 size(s, 0.0f);
	glm::vec2 position = { offset / 2 - s  , 90.0f};
	glm::vec4 color    = { 0.28f, 0.7f, 1.0f, 1.0f };
	for (uint32_t i = 0; i < length; i++) {
		if (i == state.first_value || i == state.second_value)
			color = { 1.0f, 0.0f, 0.1f, 1.0f };
		else
			color = { 0.28f, 0.7f, 1.0f, 1.0f };		
		size.y = step * array[i];
		position.x += size.x + gap;
		Renderer::CreateQuad(size, position, color, 0.0f);
	}
}

void Visualizer::Play() {	
	if (m_index == m_states.size()-1) {
		m_done = true;
	}	
	CreateGraph(m_index);
	static Timer time;
	if (time.stop() > m_delay && !m_done) {
		m_index++;
		time.reset();
	}	
}

void Visualizer::AddState(const State& s) {
	std::lock_guard<std::mutex> lock(m_mutex);
	m_states.push_back(s);
}

State& Visualizer::GetState(const uint32_t& index) {
	std::lock_guard<std::mutex> lock(m_mutex);
	return m_states.at(index);
}

void Visualizer::Reset() {
	m_states.clear();
	m_states.reserve(1000);
	m_index = 0;
	m_once = false;
	m_done = false;
	State state;
	state.rebuilded = *vec;
	AddState(state);
}

void Visualizer::setDelay(const uint32_t& delay) {
	m_delay = delay;
}