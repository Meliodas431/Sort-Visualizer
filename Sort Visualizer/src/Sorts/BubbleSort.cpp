#include "Sorts.h"
#include "Visualizer/Visualizer.h"

void Sorts::BubbleSort(std::vector<uint32_t>* data) {
	bool repeat = false;
	uint32_t step = 1;
	uint32_t length = data->size();
	do {	
		for (uint32_t i = 0; i < length-1; i++) {
			repeat = false;		
			for (uint32_t j = 0; j < length - i - 1; j++) {
				State state;
				state.first_value = j;
				state.second_value = j + 1;
				state.step = step++;			
				if (data->at(j) > data->at(j + 1)) {
					std::swap(data->at(j), data->at(j + 1));		
					state.swap = true;						
					repeat = true;
				}	
				else {
					state.swap = false;
				}
				Visualizer::AddState(state);
			}
		}
		State state;
		Visualizer::AddState(state);
	} while (repeat);
}