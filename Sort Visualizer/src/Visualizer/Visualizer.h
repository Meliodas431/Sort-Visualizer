#pragma once
#include <vector>
#include <random>
#include <future>
#include "Sorts/Sorts.h"
#include "core/Time.h"

class Array {
private:
	uint32_t m_Size;
	std::vector<uint32_t> m_array;
public:
	Array(const uint32_t& Size) {
		m_array.resize(Size, 0);
		m_Size = Size;
		ResetArray();	
	}
	void ResetArray() {
		std::random_device rd;
		std::mt19937 g(rd());
		std::uniform_int_distribution<> range(5, 999);

		for (int i = 0; i < m_Size; i++) {
			m_array[i] = range(g);
		}
	}
	std::vector<uint32_t>& GetArray() { return m_array; }
}; 

class Visualizer : public Sorts {
private:
	std::vector<uint32_t>* vec;
	static std::mutex m_mutex;
	static std::vector<State> m_states;
	static uint32_t m_statesIndex;
	uint32_t m_index, m_delay;
	bool m_once, m_done;
public:
	enum class Sorts {
		RADIX, BUBLE, HEAP, MERGE, QUICK
	};
public:
	Visualizer(Array& array);
	void CreateStates(const Sorts& sortType);
	void CreateGraph(const uint32_t& index);
	static void AddState(const State& state);
	static State& GetState(const uint32_t& index);
	void Reset();
	void setDelay(const uint32_t& delay);
	void Play();
};