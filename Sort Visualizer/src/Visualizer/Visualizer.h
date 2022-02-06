#pragma once
#include <vector>
#include <random>
#include <future>
#include "Sorts/Sorts.h"
#include "core/Time.h"

class Array {
public:
	uint32_t m_Size;
private:
	std::vector<uint32_t> m_array;
public:
	Array(const uint32_t& Size)
		: m_Size(200)
	{	
		ResetArray(Size);
	}
	void ResetArray(const uint32_t& Size) {
		m_array.resize(Size, 0);
		m_Size = Size;
		std::random_device rd;
		std::mt19937 n(rd());
		std::uniform_int_distribution<> range(5, 999);

		for (uint32_t i = 0; i < Size; i++) {
			m_array[i] = range(n);
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
	static uint32_t m_Length;
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
	void SetDelay(const uint32_t& delay);
	void Play();
};